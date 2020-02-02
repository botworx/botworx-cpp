/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"
#include <bwmessaging/BwIoSlot.h>

BwIoSlot::BwIoSlot(BwPart *pOwner, const bwString& name) : BwMailSlot(pOwner, name) {
}
void BwIoSlot::doCreate(const BwPartInfo& info) {
	BwMailSlot::doCreate(info) ;
	p_root = createIo(nullptr, "/", BwIo::IO_TOPIC) ;
	p_root->setSlot(this) ;
}
BwIo* BwIoSlot::findOrCreateIo(const bwPath& path) {
	BwIo *pNode = p_root->findOrCreateIo(path) ;
	return pNode ;
}
BwIo* BwIoSlot::findIo(const bwPath& path) {
	BwIo *pNode = p_root->findIo(path) ;
	return pNode ;
}
BwIo* BwIoSlot::createIo(BwIo *pParent, const bwString& name,BwIo::ioType type) {
	BwIo *pNode = new BwIo(pParent, name, type) ;
	pNode->create() ;
	return pNode ;
}
void BwIoSlot::update() { 
	p_root->update() ; 
}
void BwIoSlot::notify(BwMessage evt) {
	if(p_root != nullptr)
		p_root->notify(evt) ;
}
////
void BwIoSlot::printTree() {
	p_root->printTree() ; 
}
/////////
BwIoSlot::IoAddedEvent::IoAddedEvent(const bwPath& path) 
: Event(EVENT_TOPIC_ADDED) {
	m_data->addString("Path", path.string()) ;
}