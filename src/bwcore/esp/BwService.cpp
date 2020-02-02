#include "stdafx.h"

#include <bwmessaging/BwMailSlot.h>
#include <bwmessaging/BwAddress.h>

#include <bwesp/BwService.h>
#include <bwesp/BwServer.h>
#include <bwesp/BwServiceProvider.h>
#include <bwesp/BwSession.h>

#include <bwesp/_BwService.h>
using namespace _BwService ;

////////////
BwServer& BwService::getServer() { 
	return getProvider().getServer() ; 
}

BwService::BwService(BwServiceProvider* pProvider) : BwKit(pProvider), p_provider(pProvider), m_mailBox(nullptr) {
	m_mailBox.setOwner(this) ;
	m_sessionCount = 0 ;
	//
	m_isNew = true ;
	m_isClosed = false ;
	//createMailCenter() ;
}
BwService::~BwService(void) {
}
void BwService::doCreate(const BwPartInfo& info) {
	BwKit::doCreate(info) ;
	createMailCenter() ;
	getServer().addService(this) ;
}
BwSession* BwService::createSession() {
	BwSession* pSession = produceSession() ;
	addSession(pSession) ;
	return pSession ;
}
//TODO:a lot of this needs to be made thread safe!!!
void BwService::addSession(BwSession *pSession) {
	//m_sessions.push_front(pSession) ;
	pSession->setHandle(m_sessionCount++) ; //TODO:use handle pool
	m_sessions.push_back(pSession) ; //TODO:maybe use a list
}
BwSession* BwService::find_session(bwHandle sessionHandle) {
	BwSession *pSession = m_sessions[sessionHandle] ; ////TODO:use hashmap ... and handle pool!!!
	return pSession ;
}
void BwService::setFilename(const bwString& filename, bool notify) {
	m_fileName = filename ;
}
void BwService::close() {
	onClose() ;
}
bool BwService::onClose() {
	if(!m_isNew && !m_isClosed) {
		m_isClosed = true ;
	}
	m_isNew = false ;

	return true ;
}
// Since text windows have their own method for saving to/loading from files,
// we override OnSave/OpenSvcument instead of Save/LoadObject
bool BwService::onSave(const bwString& filename) {
    modify(false);
    return true;
}
bool BwService::onNew() {
	return true ;
}
bool BwService::onOpen(const bwString& filename) {
	m_isNew = false ;
    setFilename(filename, true);
    modify(false);
	p_eventSlot->send(BwOpenEvent(filename)) ;
    return true;
}

bool BwService::isModified(void) const {
	return m_isModified ;
}

void BwService::modify(bool val) {
    m_isModified = val ;
}