#include "stdafx.h"

#include <bwagency/BwAgentClient.h>
#include <bwagency/BwAgency.h>
#include <bwagency/BwAgentSystem.h>
#include <bwagency/BwAgentSession.h>

#include <bwmessaging/BwPostOffice.h>
#include <bwmessaging/BwCmd.h>

#include <bwesp/BwCluster.h>
#include <bwesp/BwLocalServer.h>
#include <bwesp/BwRemoteServer.h>
#include <bwesp/BwRemoteServiceProvider.h>
#include <bwesp/BwService.h>

//
#include <bwcore/_BwPart.h>
using namespace _BwPart ;

namespace _BwAgentClient {
class MyMailSlot : public BwMailSlot {
public:
	MyMailSlot(BwAgentClient *pOwner, const bwString& name) : BwMailSlot(pOwner, name) {
		p_client = pOwner ;
	}
	//Data Members
	BwAgentClient *p_client ;
} ;
class AgentOut : public MyMailSlot {
public:
	AgentOut(BwAgentClient *pOwner, const bwString& name) : MyMailSlot(pOwner, name) {
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
class AgentLog : public MyMailSlot {
public:
	AgentLog(BwAgentClient *pOwner, const bwString& name) : MyMailSlot(pOwner, name) {
	}
	virtual void dispatch(const BwMessage& msg) {
		switch(msg.what()) {
			case OUTPUT_TEXT :
				p_client->onLog(msg) ;
			break ;
		}
	}
} ;
class AgentEvents : public MyMailSlot {
public:
	AgentEvents(BwAgentClient *pOwner, const bwString& name) : MyMailSlot(pOwner, name) {
	}
	virtual void dispatch(const BwMessage& msg) {
		p_client->onEvent(msg) ;
	}
} ;
class AgentIos : public MyMailSlot {
public:
	AgentIos(BwAgentClient *pOwner, const bwString& name) : MyMailSlot(pOwner, name) {
	}
	virtual void dispatch(const BwMessage& msg) {
		p_client->onIo(msg) ;
	}
} ;
} ; //namespace _BwAgentClient
using namespace _BwAgentClient ;

BwAgentClient::BwAgentClient() : BwClient(NULL) {
	m_hasResponse = false ;
	//m_agentHasExited = false ;

	p_session = NULL ;

	p_agentOut = new AgentOut(this, "OUT") ;
	p_agentOut->create() ;
	addSlot(p_agentOut) ; //f6:fixme:if slots are restricted to mailbox owners only... could build this into slot.

	p_agentLog = new AgentLog(this, "LOG") ;
	p_agentLog->create() ;
	addSlot(p_agentLog) ;

	p_agentIn = new BwMailSlot(this, "IN") ;
	p_agentIn->create() ;
	addSlot(p_agentIn) ;

	p_agentEvents = new AgentEvents(this, "EVENT") ;
	p_agentEvents->create() ;
	addSlot(p_agentEvents) ;
}
BwMailCenter& BwAgentClient::getMailCenter() { 
	return p_session->getMailCenter() ; 
}
//f6:fixme:need to disconnect log, ios, etc..
void BwAgentClient::disconnect() {
	p_agentOut->disconnect() ;
	p_agentIn->disconnect() ;
	p_agentEvents->disconnect() ;
}
void BwAgentClient::dropConnection() {
	p_agentOut->dropConnection() ;
	p_agentIn->dropConnection() ;
	p_agentEvents->dropConnection() ;
}
void BwAgentClient::doCommand(const BwCmd& cmd) {
	if(m_agentHasExited == true)
		return ;
	//else
	BwTextCommand command(cmd.str()) ; //f6:fixme:make this more compatible
	p_agentIn->send(command) ;
}
void BwAgentClient::doCommandSync(const BwCmd& cmd) {
	if(m_agentHasExited == true)
		return ;
	//else
	m_hasResponse = false ;
	doCommand(cmd) ;
	while(!m_hasResponse) {
		BwEnvelope env = BwPostOffice::singleton::get().pickupNotify() ;
		env.deliver() ;
	}
}
void BwAgentClient::onOutput(const BwMessage& msg) {
	bwString out ;
	msg()->findString("Output", out) ;
	std::cout << out ;
}
void BwAgentClient::onLog(const BwMessage& msg) {
}
void BwAgentClient::onResponse(const BwMessage& msg) {
	m_hasResponse = true ;
}
void BwAgentClient::onAgentClose() {
	m_agentHasExited = true ;
}
void BwAgentClient::onEvent(const BwMessage& msg) {
	switch(msg.what()) {
		case EVENT_DESTROY :
			onAgentClose() ;
		break ;
	}
}
void BwAgentClient::onIo(const BwMessage& msg) {
}
void BwAgentClient::createAgent(agentType type, const bwString& name, BwMessage params, bool async, bool enabled) {
	setName(name) ;
	BwAgent* pAgent = BwLocalAgency::singleton::get().createAgent(type, name, params, async, enabled) ;
	BwAgentSession* pSession = dynamic_cast<BwAgentSession*>(pAgent->createSession()) ;
	connect(pSession) ;
}
void BwAgentClient::createRemoteAgent(agentType type, const bwString& name, BwMessage params, bool async, bool enabled) {
	BwRemoteServer* pRemoteServer = new BwRemoteServer(BwLocalServer::singleton::getPtr(), BwAddress("localhost", "9665")) ;
	pRemoteServer->create() ;
	pRemoteServer->enable() ; //f6:fixme:where does this go?
	BwServiceProvider* pProvider = new BwRemoteServiceProvider(pRemoteServer, "AGENCY") ;
	pProvider->create() ;
	pRemoteServer->addServiceProvider(pProvider) ;

	BwRemoteCluster::singleton::get().addServer(pRemoteServer) ;
	//
	BwServiceRequest request("AGENCY", name, async, enabled) ;
	BwService* pService = BwRemoteCluster::singleton::get().createService(request) ;	

	BwSession* pSession = pService->createSession() ;

	connect(pSession) ;
}
void BwAgentClient::close() {
	if(m_agentHasExited == true)
		return ;
	//else
	//p_session->closeAgent() ;
	p_session->closeService() ;
}
bool BwAgentClient::isClosed() {
	return m_agentHasExited ;
}