#include "stdafx.h"

#include <bwapplet/BwAppletSession.h>
#include <bwapplet/BwAppletClient.h>

#include <bwapplet/_BwApplet.h>
using namespace _BwApplet ;

namespace _BwAppletSession {
	class MyMailSlot : public BwMailSlot {
	public:
		MyMailSlot(BwAppletSession *pOwner, const bwString& name) : BwMailSlot(pOwner, name) {
			p_session = pOwner ;
		}
		//Data Members
		BwAppletSession *p_session ;
	} ;
	class MyDocEvents : public MyMailSlot {
	public:
		MyDocEvents(BwAppletSession *pOwner, const bwString& name) : MyMailSlot(pOwner, name) {
		}
		virtual void dispatch(const BwMessage& msg) {
			p_session->onEvent(msg) ;
		}
	} ;
} ; //namespace _BwAppletSession
using namespace _BwAppletSession ;

BwAppletSession::BwAppletSession() : BwPart(nullptr) {
	p_applet = nullptr ;
	m_appletHasExited = false ;
	p_outSlot = new MyMailSlot(this, "OUT") ;
	p_outSlot->create() ;
	p_appletEvents = new MyDocEvents(this, "EVENT") ;
	p_appletEvents->create() ;
}
BwApplet* BwAppletSession::create_applet() {
	p_applet = produce() ;
	p_applet->createEnabled() ;
	connect() ;
	return p_applet ;
}
BwApplet* BwAppletSession::produce() {
	return new BwApplet() ;
}
void BwAppletSession::connect() {
	p_outSlot->connect(p_applet->getMailBox().findSlot("IN")) ; //this is confusing...
}
void BwAppletSession::disconnectClients() {
	BwAppletClient *pClient = nullptr ;
	for(BwAppletClientIter iter = m_clients.begin() ; iter != m_clients.end() ; ++iter) {
		pClient = *iter ;
		pClient->disconnect() ;
	}
}
void BwAppletSession::addClient(BwAppletClient *pClient) {
	m_clients.push_front(pClient) ;
}
void BwAppletSession::removeClient(BwAppletClient *pClient) {
	m_clients.erase(find(m_clients.begin(), m_clients.end(), pClient)) ;
}
//
void BwAppletSession::onEvent(const BwMessage& msg) {
	/*switch(msg.what()) {
		case msg::Event::EVENT_DESTROY :
			on_appletExit() ;
		break ;
	}*/
}
void BwAppletSession::close_applet() {
	if(m_appletHasExited)
		return ;
	m_appletHasExited = true ;
	disconnectClients() ;
	BwCommand cmd = BwCommand(COMMAND_CLOSE);
	p_outSlot->send(cmd) ;
}
void BwAppletSession::notice_appletClose() {
}
