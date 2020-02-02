#include "stdafx.h"

#include <bwagency/BwAgentSession.h>
#include <bwagency/BwAgency.h>
#include <bwagency/BwAgentClient.h>

#include <bwmessaging/BwMailCenter.h>

#include <bwcore/_BwPart.h>
using namespace _BwPart ;

//f6:fixme:session appears to be an extension of AgentClient itself ... not up to it right now.
namespace _BwAgentSession {
	class MyMailSlot : public BwMailSlot {
	public:
		MyMailSlot(BwAgentSession *pOwner, const bwString& name) : BwMailSlot(pOwner, name) {
			p_session = pOwner ;
		}
		//Data Members
		BwAgentSession *p_session ;
	} ;
	class MyAgentEvents : public MyMailSlot {
	public:
		MyAgentEvents(BwAgentSession *pOwner, const bwString& name) : MyMailSlot(pOwner, name) {
		}
		virtual void dispatch(const BwMessage& msg) {
			p_session->onEvent(msg) ;
		}
	} ;
} ; //namespace _BwAgentSession
using namespace _BwAgentSession ;

BwAgentSession::BwAgentSession(BwAgent* pAgent) : BwSession(pAgent) {
	p_agent = pAgent ;
	m_agentHasExited = false ;
	p_outSlot = new MyMailSlot(this, "OUT") ;
	p_outSlot->create() ;
	p_agentEvents = new MyAgentEvents(this, "EVENT") ;
	p_agentEvents->create() ;
}
//f6:fixme:local/remote mixin?
void BwAgentSession::connectSlot(const bwString& name, BwClient* pClient, BwMailSlot* pSlot) {
	BwMailCenter& mailCenter = p_service->getMailCenter() ;
	BwMailBox* pBox = mailCenter.findBox(pClient->getBoxHandle()) ;
	pSlot->connect(pBox->findSlot(name)) ;
}
void BwAgentSession::connectClient(BwClient* pClient) {
	addClient(pClient) ;
}
void BwAgentSession::closeService() {
	if(m_agentHasExited)
		return ;
	m_agentHasExited = true ;
	disconnectClients() ;
	BwCommand cmd = BwCommand(COMMAND_CLOSE);
	p_outSlot->send(cmd) ;
	BwLocalAgency::singleton::get().closeAgent(p_agent) ;
}
//
void BwAgentSession::onEvent(const BwMessage& msg) {
	switch(msg.what()) {
		case EVENT_DESTROY :
			onAgentClose() ;
		break ;
	}
}
void BwAgentSession::onAgentClose() {
	m_agentHasExited = true ;
}
