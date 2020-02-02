#include "stdafx.h"

#include <bwesp/BwSession.h>
#include <bwesp/BwClient.h>

#include <bwesp/_BwService.h>
using namespace _BwService ;

namespace _BwSession {
	class MyMailSlot : public BwMailSlot {
	public:
		MyMailSlot(BwSession *pOwner, const bwString& name) : BwMailSlot(pOwner, name) {
			p_session = pOwner ;
		}
		//Data Members
		BwSession *p_session ;
	} ;
	class MySvcEvents : public MyMailSlot {
	public:
		MySvcEvents(BwSession *pOwner, const bwString& name) : MyMailSlot(pOwner, name) {
		}
		virtual void dispatch(const BwMessage& msg) {
			p_session->onEvent(msg) ;
		}
	} ;
} ; //namespace _BwSession
using namespace _BwSession ;

BwSession::BwSession(BwService* pSvc) : BwPart(pSvc) {
	p_service = pSvc ;
	m_serviceHasClosed = false ;
	p_outSlot = new MyMailSlot(this, "OUT") ;
	p_outSlot->create() ;
	p_serviceEvents = new MySvcEvents(this, "EVENT") ;
	p_serviceEvents->create() ;
	//
	m_clientCount = 0 ;
}
void BwSession::doCreate(const BwPartInfo& info) {
	BwPart::doCreate(info) ;
	//p_outSlot->connect(p_service->getMailBox().findSlot("IN")) ; //this is confusing...
}
void BwSession::disconnectClients() {
	BwClient *pClient = nullptr ;
	for(BwClientIter iter = m_clients.begin() ; iter != m_clients.end() ; ++iter) {
		pClient = *iter ;
		pClient->disconnect() ;
	}
}
void BwSession::addClient(BwClient *pClient) {
	pClient->setHandle(m_clientCount++) ; //TODO:use handle pool
	m_clients.push_back(pClient) ;
}
void BwSession::removeClient(BwClient *pClient) {
	bwAssert(0) ; //TODO:whole hash map / handle pool thing!!!
	m_clients.erase(find(m_clients.begin(), m_clients.end(), pClient)) ;
}
BwClient* BwSession::findClient(bwHandle clientHandle) {
	BwClient *pClient = m_clients[clientHandle] ; ////TODO:use hashmap ... and handle pool!!!
	return pClient ;
}
void BwSession::closeService() {
	if(m_serviceHasClosed)
		return ;
	m_serviceHasClosed = true ;
	disconnectClients() ;
	BwCommand cmd = BwCommand(COMMAND_CLOSE);
	p_outSlot->send(cmd) ;
}
void BwSession::noticeServiceClose() {
}
