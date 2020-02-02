#include "stdafx.h"

#include <bwdocument/BwDocSession.h>
#include <bwdocument/BwDocClient.h>

#include <bwdocument/_BwDocument.h>
using namespace _BwDocument ;

namespace _BwDocSession {
	class MyMailSlot : public BwMailSlot {
	public:
		MyMailSlot(BwDocSession *pOwner, const bwString& name) : BwMailSlot(pOwner, name) {
			p_session = pOwner ;
		}
		//Data Members
		BwDocSession *p_session ;
	} ;
	class MyDocEvents : public MyMailSlot {
	public:
		MyDocEvents(BwDocSession *pOwner, const bwString& name) : MyMailSlot(pOwner, name) {
		}
		virtual void dispatch(const BwMessage& msg) {
			p_session->onEvent(msg) ;
		}
	} ;
} ; //namespace _BwDocSession
using namespace _BwDocSession ;

//BwDocSession::BwDocSession(documentType type, const bwString& name, BwMessage params, bool enabled) : BwPart(nullptr) {
BwDocSession::BwDocSession() : BwPart(nullptr) {
	p_document = nullptr ;
	m_documentHasExited = false ;
	p_outSlot = new MyMailSlot(this, "OUT") ;
	p_outSlot->create() ;
	p_documentEvents = new MyDocEvents(this, "EVENT") ;
	p_documentEvents->create() ;
}
BwDocument* BwDocSession::createDocument() {
	p_document = produce() ;
	p_document->createEnabled() ;
	connect() ;
	return p_document ;
}
BwDocument* BwDocSession::produce() {
	return new BwDocument() ;
}
void BwDocSession::connect() {
	p_outSlot->connect(p_document->getMailBox().findSlot("IN")) ; //this is confusing...
}
void BwDocSession::disconnectClients() {
	BwDocClient *pClient = nullptr ;
	for(BwDocClientIter iter = m_clients.begin() ; iter != m_clients.end() ; ++iter) {
		pClient = *iter ;
		pClient->disconnect() ;
	}
}
void BwDocSession::addClient(BwDocClient *pClient) {
	m_clients.push_front(pClient) ;
}
void BwDocSession::removeClient(BwDocClient *pClient) {
	m_clients.erase(find(m_clients.begin(), m_clients.end(), pClient)) ;
}
//
void BwDocSession::onEvent(const BwMessage& msg) {
	/*switch(msg.what()) {
		case msg::Event::EVENT_DESTROY :
			onDocumentExit() ;
		break ;
	}*/
}
void BwDocSession::closeDocument() {
	if(m_documentHasExited)
		return ;
	m_documentHasExited = true ;
	disconnectClients() ;
	BwCommand cmd = BwCommand(COMMAND_CLOSE);
	p_outSlot->send(cmd) ;
}
void BwDocSession::noticeDocumentClose() {
}
