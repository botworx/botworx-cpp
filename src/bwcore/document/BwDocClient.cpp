#include "stdafx.h"

#include <bwdocument/BwDocClient.h>
#include <bwdocument/BwDocSession.h>

#include <bwmessaging/BwPostOffice.h>
#include <bwmessaging/BwCmd.h>

#include <bwdocument/_BwDocument.h>
using namespace _BwDocument ;

namespace _BwDocClient {
class MyMailSlot : public BwMailSlot {
public:
	MyMailSlot(BwDocClient *pOwner, const bwString& name) : BwMailSlot(pOwner, name) {
		p_client = pOwner ;
	}
	//Data Members
	BwDocClient *p_client ;
} ;
class DocOut : public MyMailSlot {
public:
	DocOut(BwDocClient *pOwner, const bwString& name) : MyMailSlot(pOwner, name) {
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
class DocLog : public MyMailSlot {
public:
	DocLog(BwDocClient *pOwner, const bwString& name) : MyMailSlot(pOwner, name) {
	}
	virtual void dispatch(const BwMessage& msg) {
		switch(msg.what()) {
			case OUTPUT_TEXT :
				p_client->onLog(msg) ;
			break ;
		}
	}
} ;
class DocEvents : public MyMailSlot {
public:
	DocEvents(BwDocClient *pOwner, const bwString& name) : MyMailSlot(pOwner, name) {
	}
	virtual void dispatch(const BwMessage& msg) {
		p_client->onEvent(msg) ;
	}
} ;
} ; //namespace _BwDocClient
using namespace _BwDocClient ;

BwDocClient::BwDocClient() : BwPart(nullptr) {
	m_hasResponse = false ;
	m_documentHasExited = false ;

	p_session = nullptr ;

	p_documentOut = new DocOut(this, "OUT") ;
	p_documentOut->create() ;

	p_documentLog = new DocLog(this, "LOG") ;
	p_documentLog->create() ;

	p_documentIn = new BwMailSlot(this, "IN") ;
	p_documentIn->create() ;

	p_documentEvents = new DocEvents(this, "EVENT") ;
	p_documentEvents->create() ;
}
void BwDocClient::connect(BwDocSession *pSession) {
	p_session = pSession ;
	pSession->addClient(this) ;

	p_documentIn->connect(p_session->getMailBox().findSlot("IN")) ;
	p_documentOut->connect(p_session->getMailBox().findSlot("OUT")) ;
	p_documentLog->connect(p_session->getMailBox().findSlot("LOG")) ;
	p_documentEvents->connect(p_session->getMailBox().findSlot("EVENT")) ;
}
//TODO: disconnect all
void BwDocClient::disconnect() {
	p_documentOut->disconnect() ;
	p_documentIn->disconnect() ;
	p_documentEvents->disconnect() ;
}
void BwDocClient::dropConnection() {
	p_documentOut->dropConnection() ;
	p_documentIn->dropConnection() ;
	p_documentEvents->dropConnection() ;
}
void BwDocClient::doCommand(const BwCmd& cmd) {
	if(m_documentHasExited == true)
		return ;
	//else
	BwTextCommand command(cmd.str()) ; //TODO:make this more compatible
	p_documentIn->send(command) ;
}
void BwDocClient::doCommandSync(const BwCmd& cmd) {
	if(m_documentHasExited == true)
		return ;
	//else
	m_hasResponse = false ;
	doCommand(cmd) ;
	while(!m_hasResponse) {
		BwEnvelope env = BwPostOffice::singleton::get().pickupNotify() ;
		env.deliver() ;
	}
}
void BwDocClient::onOutput(const BwMessage& msg) {
	bwString out ;
	msg()->findString("Output", out) ;
	std::cout << out ;
}
void BwDocClient::onLog(const BwMessage& msg) {
}
void BwDocClient::onResponse(const BwMessage& msg) {
	m_hasResponse = true ;
}
void BwDocClient::onDocumentExit() {
	m_documentHasExited = true ;
}
void BwDocClient::onEvent(const BwMessage& msg) {
	switch(msg.what()) {
		case EVENT_DESTROY :
			onDocumentExit() ;
		break ;
	}
}
void BwDocClient::onIo(const BwMessage& msg) {
}
void BwDocClient::close() {
	if(m_documentHasExited == true)
		return ;
	//else
	p_session->closeDocument() ;
}
void BwDocClient::noticeDocumentClose() {
	p_session->noticeDocumentClose() ;
}
bool BwDocClient::isClosed() {
	return m_documentHasExited ;
}