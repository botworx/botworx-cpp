/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <bwmessaging/BwMailSlot.h>
#include <bwmessaging/BwLocalMessenger.h>
#include <bwmessaging/BwPoMessenger.h>
#include <bwmessaging/BwAddress.h>
#include <bwmessaging/BwPostOffice.h>

BwMailSlot::BwMailSlot(BwPart *pOwner, const bwString& name) : BwMessengerBase(pOwner) {
	setName(name) ;
	init() ;
}
BwMailSlot::BwMailSlot(const bwString& name) : BwMessengerBase(nullptr) {
	setName(name) ;
	init() ;
}
BwMailSlot::BwMailSlot() : BwMessengerBase(nullptr) {
	init() ;
}
BwMailSlot::~BwMailSlot() {
	destroyPart(p_messenger) ;
}
void BwMailSlot::doCreate(const BwPartInfo& info) {
	BwMessengerBase::doCreate(info) ;
	p_po = &BwPostOffice::singleton::get() ;
}
void BwMailSlot::connect(BwMailSlot *pSlot) {
	setMessenger(pSlot->accept(this)) ;
	p_messenger->connect(pSlot) ;
}
BwMessenger* BwMailSlot::accept(BwMailSlot *pSlot) {
	if(getPo() == pSlot->getPo())
		return new BwLocalMessenger(pSlot) ;
	else
		return new BwPoMessenger(pSlot) ;
}
void BwMailSlot::disconnect() {
	p_messenger->disconnect() ;
}
void BwMailSlot::dropConnection() {
	delete p_messenger ;
	p_messenger = nullptr ;
}
void BwMailSlot::setMessenger(BwMessenger *pMessenger) {
	p_messenger = pMessenger ;
	pMessenger->setDownLink(this) ;
}
void BwMailSlot::receive(const BwMessage& msg, bool selfReflective){
	//boost::mutex::scoped_lock lock(m_dispatchMutex) ;
	//in some instances such as chat we don't want to receive the message sent through this.
	if(isSelfReflective())
		dispatch(msg) ;
	else
		if(msg.getSender() != this)
			dispatch(msg) ;

	removeOldSubscribers() ; //have to stick this somewhere ... a consequence of receivers unsubscribing during reception

	boost::mutex::scoped_lock lock(m_dispatchMutex) ;
	if(m_subs.empty())
		return ;
	//else
	BwMessenger *pMessenger = nullptr ;
	for(BwMessengerIter iter = m_subs.begin();
		iter != m_subs.end(); ++iter)	{
		pMessenger = *iter ;
		pMessenger->receive(msg) ;
	}
}
void BwMailSlot::send(const BwMessage& msg) {
	//TODO:This caused problems for boost 1.35
	//boost::mutex::scoped_lock lock(m_dispatchMutex) ;
	if(msg.getSender() == nullptr)
		msg.setSender(this) ;
	if(p_messenger != nullptr)
		p_messenger->send(msg) ;

	receive(msg, true) ; //this is to implement reflection ...
}
void BwMailSlot::addSubscriber(BwMessenger *pMessenger) {
	boost::mutex::scoped_lock lock(m_dispatchMutex) ;
	m_subs.push_back(pMessenger) ;
}
void BwMailSlot::removeSubscriber(BwMessenger *pMessenger) {
	boost::mutex::scoped_lock lock(m_dispatchMutex) ;
	m_oldSubs.push_front(pMessenger) ;
}
//I had to add this because if receivers need to disconnect on event... it corrupted the subscriber list.
void BwMailSlot::removeOldSubscribers() {
	if(m_oldSubs.empty())
		return ;
	for(BwMessengerIter iter = m_oldSubs.begin();
		iter != m_oldSubs.end(); ++iter)	{
		m_subs.erase(std::find(m_subs.begin(),m_subs.end(),*iter)) ;
	}
	m_oldSubs.clear() ;
}
