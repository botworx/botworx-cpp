#include "stdafx.h"

#include <bwagency/BwStateClient.h>
#include <bwagency/BwAgentClient.h>
#include <bwagency/BwAgentSystem.h>
#include <bwagency/BwAgentSession.h>

#include <bwmessaging/BwPostOffice.h>
#include <bwmessaging/BwMailCenter.h>
#include <bwmessaging/BwCmd.h>

#include <bwcore/_BwPart.h>
using namespace _BwPart ;

namespace _BwStateClient {
class MyMailSlot : public BwMailSlot {
public:
	MyMailSlot(BwStateClient *pOwner, const bwString& name) : BwMailSlot(pOwner, name) {
		p_client = pOwner ;
	}
	//Data Members
	BwStateClient *p_client ;
} ;
class StateOut : public MyMailSlot {
public:
	StateOut(BwStateClient *pOwner, const bwString& name) : MyMailSlot(pOwner, name) {
	}
	virtual void dispatch(const BwMessage& msg) {
		switch(msg.what()) {
			case RESPONSE_TEXT :
				p_client->onResponse(msg) ;
				break ;
			//case OUTPUT_TEXT :
			default:
				p_client->onOutput(msg) ;
			//break ;
		}
	}
} ;
class StateLog : public MyMailSlot {
public:
	StateLog(BwStateClient *pOwner, const bwString& name) : MyMailSlot(pOwner, name) {
	}
	virtual void dispatch(const BwMessage& msg) {
		switch(msg.what()) {
			case OUTPUT_TEXT :
				p_client->onLog(msg) ;
			break ;
		}
	}
} ;
class StateEvents : public MyMailSlot {
public:
	StateEvents(BwStateClient *pOwner, const bwString& name) : MyMailSlot(pOwner, name) {
	}
	virtual void dispatch(const BwMessage& msg) {
		p_client->onEvent(msg) ;
	}
} ;
class StateIos : public MyMailSlot {
public:
	StateIos(BwStateClient *pOwner, const bwString& name) : MyMailSlot(pOwner, name) {
	}
	virtual void dispatch(const BwMessage& msg) {
		p_client->onIo(msg) ;
	}
} ;
} ; //namespace _BwStateClient
using namespace _BwStateClient ;

BwStateClient::BwStateClient(bwHandle handle) : BwPart(NULL) {
	setHandle(handle) ;

	m_hasResponse = false ;
	m_stateHasExited = false ;

	p_agentClient = NULL ;

	p_stateOut = new StateOut(this, "OUT") ;
	p_stateOut->create() ;

	p_stateLog = new StateLog(this, "LOG") ;
	p_stateLog->create() ;

	p_stateIn = new BwMailSlot(this, "IN") ;
	p_stateIn->create() ;

	p_stateEvents = new StateEvents(this, "EVENT") ;
	p_stateEvents->create() ;
}
void BwStateClient::connect(BwAgentClient *pAgentClient) {
	p_agentClient = pAgentClient ;
	pAgentClient->addStateClient(m_name, this) ;

	BwMailCenter& mailCenter = p_agentClient->getMailCenter() ;
	BwMailBox& box = *mailCenter.findBox(m_handle) ;
	p_stateIn->connect(box.findSlot("IN")) ;
	p_stateOut->connect(box.findSlot("OUT")) ;
	p_stateLog->connect(box.findSlot("LOG")) ;
	p_stateEvents->connect(box.findSlot("EVENT")) ;
}
//f6:fixme:need to disconnect log, ios, etc..
void BwStateClient::disconnect() {
	p_stateOut->disconnect() ;
	p_stateIn->disconnect() ;
	p_stateEvents->disconnect() ;
}
void BwStateClient::dropConnection() {
	p_stateOut->dropConnection() ;
	p_stateIn->dropConnection() ;
	p_stateEvents->dropConnection() ;
}
void BwStateClient::doCommand(const BwCmd& cmd) {
	if(m_stateHasExited == true)
		return ;
	//else
	BwTextCommand command(cmd.str()) ; //f6:fixme:make this more compatible
	p_stateIn->send(command) ;
}
void BwStateClient::doCommandSync(const BwCmd& cmd) {
	if(m_stateHasExited == true)
		return ;
	//else
	m_hasResponse = false ;
	doCommand(cmd) ;
	while(!m_hasResponse) {
		BwEnvelope env = BwPostOffice::singleton::get().pickupNotify() ;
		env.deliver() ;
	}
}
void BwStateClient::onOutput(const BwMessage& msg) {
	bwString out ;
	msg()->findString("Output", out) ;
	std::cout << out ;
}
void BwStateClient::onLog(const BwMessage& msg) {
}
void BwStateClient::onResponse(const BwMessage& msg) {
	m_hasResponse = true ;
}
void BwStateClient::onStateExit() {
	m_stateHasExited = true ;
}
void BwStateClient::onEvent(const BwMessage& msg) {
	switch(msg.what()) {
		case EVENT_DESTROY :
			onStateExit() ;
		break ;
	}
}
void BwStateClient::onIo(const BwMessage& msg) {
}
void BwStateClient::createState(stateType type, const bwString& name, BwMessage params, bool enabled) {
	bwAssert(0) ;
	/*setName(name) ;
	BwAgentClient *pAgentClient = createSession(type, name, params, enabled) ;
	pAgentClient->createState() ;
	connect(pAgentClient) ;*/
}
void BwStateClient::createAsyncState(stateType type, const bwString& name, BwMessage params, bool enabled) {
	bwAssert(0) ;
	/*setName(name) ;
	BwAgentClient *pAgentClient = createSession(type, name, params, enabled) ;
	pAgentClient->createAsyncState() ;
	connect(pAgentClient) ;*/
}
void BwStateClient::close() {
	if(m_stateHasExited == true)
		return ;
	//else
	//p_agentClient->close_state() ;
}
void BwStateClient::noticeStateExit() {
	bwAssert(0) ;
	//p_agentClient->noticeStateExit() ;
}
void BwStateClient::destroyState() {
	bwAssert(0) ;
	//p_agentClient->destroyState() ;
}
bool BwStateClient::isClosed() {
	return m_stateHasExited ;
}
