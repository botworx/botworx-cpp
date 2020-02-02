#include "stdafx.h"

#include <bwapplet/BwAppletClient.h>
#include <bwapplet/BwAppletSession.h>

#include <bwmessaging/BwPostOffice.h>
#include <bwmessaging/BwCmd.h>

#include <bwapplet/_BwApplet.h>
using namespace _BwApplet ;

namespace _BwAppletClient {
class MyMailSlot : public BwMailSlot {
public:
	MyMailSlot(BwAppletClient *pOwner, const bwString& name) : BwMailSlot(pOwner, name) {
		p_client = pOwner ;
	}
	//Data Members
	BwAppletClient *p_client ;
} ;
class AppletOut : public MyMailSlot {
public:
	AppletOut(BwAppletClient *pOwner, const bwString& name) : MyMailSlot(pOwner, name) {
	}
	virtual void dispatch(const BwMessage& msg) {
		switch(msg.what()) {
			case RESPONSE_TEXT :
				p_client->onResponse(msg) ;
				break ;
			case OUTPUT_TEXT :
				p_client->onOutput(msg) ;
			break ;
		}
	}
} ;
class AppletLog : public MyMailSlot {
public:
	AppletLog(BwAppletClient *pOwner, const bwString& name) : MyMailSlot(pOwner, name) {
	}
	virtual void dispatch(const BwMessage& msg) {
		switch(msg.what()) {
			case OUTPUT_TEXT :
				p_client->onLog(msg) ;
			break ;
		}
	}
} ;
class AppletEvents : public MyMailSlot {
public:
	AppletEvents(BwAppletClient *pOwner, const bwString& name) : MyMailSlot(pOwner, name) {
	}
	virtual void dispatch(const BwMessage& msg) {
		p_client->onEvent(msg) ;
	}
} ;
} ; //namespace _BwAppletClient
using namespace _BwAppletClient ;

BwAppletClient::BwAppletClient() : BwPart(nullptr) {
	m_hasResponse = false ;
	m_appletHasExited = false ;

	p_session = nullptr ;

	p_appletOut = new AppletOut(this, "OUT") ;
	p_appletOut->create() ;

	p_appletLog = new AppletLog(this, "LOG") ;
	p_appletLog->create() ;

	p_appletIn = new BwMailSlot(this, "IN") ;
	p_appletIn->create() ;

	p_appletEvents = new AppletEvents(this, "EVENT") ;
	p_appletEvents->create() ;

	/*p_appletIos = new AppletIos(this) ;
	p_appletIos->create() ;*/
}
void BwAppletClient::connect(BwAppletSession *pSession) {
	p_session = pSession ;
	pSession->addClient(this) ;

	p_appletIn->connect(p_session->getMailBox().findSlot("IN")) ;
	p_appletOut->connect(p_session->getMailBox().findSlot("OUT")) ;
	p_appletLog->connect(p_session->getMailBox().findSlot("LOG")) ;
	p_appletEvents->connect(p_session->getMailBox().findSlot("EVENT")) ;
	//p_appletIos->connect(p_session->mailBox().findSlot("IO")) ;
}
//TODO:need to disconnect log, ios, etc..
void BwAppletClient::disconnect() {
	p_appletOut->disconnect() ;
	p_appletIn->disconnect() ;
	p_appletEvents->disconnect() ;
}
void BwAppletClient::dropConnection() {
	p_appletOut->dropConnection() ;
	p_appletIn->dropConnection() ;
	p_appletEvents->dropConnection() ;
}
//void BwAppletClient::doCommand(const bwString& cmdString) {
void BwAppletClient::doCommand(const BwCmd& cmd) {
	if(m_appletHasExited == true)
		return ;
	//else
	BwTextCommand command(cmd.str()) ; //TODO:make this more compatible
	p_appletIn->send(command) ;
}
//void BwAppletClient::doCommandSync(const bwString& cmdString) {
void BwAppletClient::doCommandSync(const BwCmd& cmd) {
	if(m_appletHasExited == true)
		return ;
	//else
	m_hasResponse = false ;
	doCommand(cmd) ;
	while(!m_hasResponse) {
		BwEnvelope env = BwPostOffice::singleton::get().pickupNotify() ;
		env.deliver() ;
	}
}
void BwAppletClient::onOutput(const BwMessage& msg) {
	bwString out ;
	msg()->findString("Output", out) ;
	std::cout << out ;
}
void BwAppletClient::onLog(const BwMessage& msg) {
}
void BwAppletClient::onResponse(const BwMessage& msg) {
	m_hasResponse = true ;
}
void BwAppletClient::on_appletExit() {
	m_appletHasExited = true ;
}
void BwAppletClient::onEvent(const BwMessage& msg) {
	switch(msg.what()) {
		case EVENT_DESTROY :
			on_appletExit() ;
		break ;
	}
}
void BwAppletClient::onIo(const BwMessage& msg) {
}
void BwAppletClient::close() {
	if(m_appletHasExited == true)
		return ;
	//else
	p_session->close_applet() ;
}
void BwAppletClient::notice_appletClose() {
	p_session->notice_appletClose() ;
}
bool BwAppletClient::isClosed() {
	return m_appletHasExited ;
}