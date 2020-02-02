#include "stdafx.h"

#include <bwmessaging/BwIo.h>
#include <bwmessaging/BwIoSlot.h>

BwIo::BwIo(BwIo *pParent, const bwString& name, ioType type) 
	: BwPart(pParent), p_parent(pParent), m_type(type) {
	setName(name) ;
	m_path = makePath() ;
	if(pParent != nullptr) {
		setSlot(pParent->getSlot()) ;
		p_slot->send(BwIoSlot::IoAddedEvent(m_path)) ;
	}
	//else ... IoSlot set it for us.
	m_needsUpdate = false ;
	m_childNeedsUpdate = false ;
}
void BwIo::notify(BwMessage evt) {
	if(m_ios.empty())
		return ;
	//else
	for(BwIoMapIter iter = m_ios.begin() ; iter != m_ios.end() ; ++iter) {
		(*iter).second->notify(evt) ;
	}
}
void BwIo::update() {
	if(m_needsUpdate == true) {
		onUpdate() ;
		m_needsUpdate = false ;
	}
	if(m_ios.empty())
		return ;
	//else
	if(!m_childNeedsUpdate)
		return ;
	//else
	for(BwIoMapIter iter = m_ios.begin() ; iter != m_ios.end() ; ++iter) {
		(*iter).second->update() ;
	}
	m_childNeedsUpdate = false ;
}
void BwIo::signalChildNeedsUpdate() {
	m_childNeedsUpdate = true ;
	if(p_parent != nullptr)
		p_parent->signalChildNeedsUpdate() ;
}
void BwIo::invalidate() {
	m_needsUpdate = true ;
	if(p_parent != nullptr)
		p_parent->signalChildNeedsUpdate() ;
}
bwPath BwIo::makePath() {
	if(p_parent == nullptr)
		return bwPath("/") ;
	//else
	return p_parent->getPath() /= m_name ;
}
BwIo* BwIo::createTopicIo(const bwString& name) {
	BwIo *pIo = p_slot->createIo(this, name, IO_TOPIC) ;
	m_ios[name] = pIo ;
	return pIo ;
}
BwIo* BwIo::createAttrIo(const bwString& name) {
	BwIo *pIo = p_slot->createIo(this, name, IO_ATTR) ;
	m_ios[name] = pIo ;
	return pIo ;
}
BwIo* BwIo::createValueIo(const bwString& name) {
	BwIo *pIo = p_slot->createIo(this, name, IO_VALUE) ;
	m_ios[name] = pIo ;
	return pIo ;
}
BwIo* BwIo::findSubIo(const bwString& name) {
	return m_ios[name] ;
}
BwIo* BwIo::findOrCreateSubIo(const bwString& name, const bwPath& leafPath) {
	BwIo *pIo = findSubIo(name) ;
	if(pIo != nullptr)
		return pIo ;

	/*if(leafPath == "")
		pIo = createAttrIo(name) ;
	else*/
		pIo = createTopicIo(name) ;
	return pIo ;
}
BwIo* BwIo::findOrCreateIo(const bwPath& path) {
	BwIo *pIo = nullptr ;

	if(!path.has_branch_path() && m_name == path.leaf())
		return this ;
	//else
	bwPath leafPath ;
	for(bwPath::iterator iter = ++path.begin() ; iter != path.end() ; ++iter) {
		leafPath /= *iter ;
	}
	pIo = findOrCreateSubIo((*path.begin()).string(), leafPath) ;
	//kind of a crappy way to return the last half of the path...
	if(leafPath == "")
		return pIo ;
	//else
	return pIo->findOrCreateIo(leafPath) ;
}
BwIo* BwIo::findIo(const bwPath& path) {
	BwIo *pIo = nullptr ;

	if(!path.has_branch_path() && m_name == path.leaf())
		return this ;
	//else
	pIo = findSubIo((*path.begin()).string()) ;
	//kind of a crappy way to return the last half of the path...
	bwPath leafPath ;
	for(bwPath::iterator iter = ++path.begin() ; iter != path.end() ; ++iter) {
		leafPath /= *iter ;
	}
	if(leafPath == "")
		return pIo ;
	//else
	return pIo->findIo(leafPath) ;
}
///////////
#define _CVTBUFSIZE (309+40)
bwString BwIo::Value::toString() {
	bwString out ;
	char buffer[_CVTBUFSIZE] ;
	switch(what()) {
		case Value::VAL_STRING : {
			out += string_val ;
		}
		break ;
		case Value::VAL_INT : {
			//_ltoa(m_v.int_val, buffer, 10) ;
			snprintf(buffer, _CVTBUFSIZE, "%d", m_v.int_val);
			out += buffer ;
		}
		break ;
		case Value::VAL_FLOAT : {
			// _gcvt( m_v.float_val, 12, buffer );
			snprintf(buffer, _CVTBUFSIZE, "%f", m_v.float_val);
			out += buffer ;
		}
		break ;
	}
	return out ;
}
void BwIo::print(int indent) {
	bwString out ;
	for(int i = 0 ; i < indent ; ++i)
		out += "\t" ;
	out += m_name + " : " ;
	out += "\n" ;
	//
	std::cout << out ;
}
void BwIo::printIos(int indent) {
	for(BwIoMapIter iter = m_ios.begin() ; iter != m_ios.end() ; ++iter) {
		(*iter).second->printTree(indent) ;
	}
}
void BwIo::printTree(int indent) {
	print(indent) ;
	++indent ;
	printIos(indent) ;
}