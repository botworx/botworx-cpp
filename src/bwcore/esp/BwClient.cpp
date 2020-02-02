#include "stdafx.h"

#include <bwesp/BwClient.h>
#include <bwesp/BwSession.h>

#include <bwesp/_BwService.h>
using namespace _BwService ;

BwClient::BwClient(BwPart* pOwner) : BwMailer(pOwner) {
	m_hasResponse = false ;
	m_serviceHasClosed = false ;
	p_session = nullptr ;
}
void BwClient::connect(BwSession *pSession, bwHandle hBox) {
	p_session = pSession ;
	m_boxHandle = hBox ;
	//pSession->addClient(this) ;
	p_session->connectClient(this) ;

	for(BwMailSlotMapIter iter = m_slots.begin() ; iter != m_slots.end() ; ++iter) {
		connectSlot(iter->first, iter->second) ;
	}
}
void BwClient::connectSlot(const bwString& name, BwMailSlot* pSlot) {
	p_session->connectSlot(name, this, pSlot) ;
}
BwMailSlot* BwClient::createSlot(const bwString& name) {
	BwMailSlot* pSlot = new BwMailSlot(this, name) ;
	pSlot->create() ;
	addSlot(pSlot) ;
	connectSlot(name, pSlot) ;
	return pSlot ;
}
//TODO:need to disconnect log, ios, etc..
void BwClient::disconnect() {
	for(BwMailSlotMapIter iter = m_slots.begin() ; iter != m_slots.end() ; ++iter) {
		BwMailSlot* pSlot = iter->second ;
		pSlot->disconnect() ;
	}
}
void BwClient::dropConnection() {
	for(BwMailSlotMapIter iter = m_slots.begin() ; iter != m_slots.end() ; ++iter) {
		BwMailSlot* pSlot = iter->second ;
		pSlot->dropConnection() ;
	}
}
void BwClient::onOutput(const BwMessage& msg) {
	bwString out ;
	msg()->findString("Output", out) ;
	std::cout << out ;
}
void BwClient::onLog(const BwMessage& msg) {
}
void BwClient::onResponse(const BwMessage& msg) {
	m_hasResponse = true ;
}
void BwClient::onServiceExit() {
	m_serviceHasClosed = true ;
}
void BwClient::onEvent(const BwMessage& msg) {
	switch(msg.what()) {
		case EVENT_DESTROY :
			onServiceExit() ;
		break ;
	}
}
void BwClient::onIo(const BwMessage& msg) {
}
void BwClient::close() {
	if(m_serviceHasClosed == true)
		return ;
	//else
	p_session->closeService() ;
}
void BwClient::noticeServiceClose() {
	p_session->noticeServiceClose() ;
}
bool BwClient::isClosed() {
	return m_serviceHasClosed ;
}