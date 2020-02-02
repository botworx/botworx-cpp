/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <bwmessaging/BwPostOffice.h>
#include <bwmessaging/BwMessengerBase.h>

BwPostOffice::BwPostOffice() : BwPart(nullptr) {
	p_call = nullptr ;
}
void BwPostOffice::holdMessage(const BwMessage& msg, BwMessengerBase *pRecipient) {
	boost::mutex::scoped_lock lock(m_dispatchMutex) ;
	if(m_mail.empty()) {
		if(p_call != nullptr)
			p_call->exec() ;
	}
	m_mail.push(BwEnvelope(msg, pRecipient)) ;
	m_holding.notify_all() ;
}
BwEnvelope BwPostOffice::pickup() {
	boost::mutex::scoped_lock lock(m_dispatchMutex) ;
	if(m_mail.empty())
		return BwEnvelope() ;
	//else
	BwEnvelope env = m_mail.front() ;
	m_mail.pop() ;
	return env ;
}
BwEnvelope BwPostOffice::pickupNotify() {
	boost::mutex::scoped_lock lock(m_holdingMutex) ;
	if(m_mail.empty())
		m_holding.wait(lock) ;
	return pickup() ;
}
void BwPostOffice::release() {
	m_holding.notify_all() ;
}
void BwPostOffice::deliver() {
	boost::mutex::scoped_lock lock(m_dispatchMutex) ;
	while(!m_mail.empty()) {
		BwEnvelope env = m_mail.front() ;
		m_mail.pop() ;
		env.deliver() ;
	}
}
void BwPostOffice::deliver_notify() {
	boost::mutex::scoped_lock lock(m_holdingMutex) ;
	if(m_mail.empty())
		m_holding.wait(lock) ;
	deliver() ;
}
////////
void BwEnvelope::deliver() {
	p_recipient->receive(m_msg) ;
}
/*Singleton Support*/
void cleanup(BwPostOffice *pPo) {
	if(pPo == nullptr)
		return ;
	pPo->disable(false) ;
	delete pPo ;
}
BwPostOffice* BwPostOffice::singleton_alloc::alloc() { 
	BwPostOffice* pPo = new BwPostOffice() ;
	pPo->create() ;
	return pPo ;
}
template<> BwPostOffice::singleton::pointer BwPostOffice::singleton::g_singleton(cleanup) ;
