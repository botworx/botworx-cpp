#include "stdafx.h"

#include <bwagency/BwMiaAgent.h>
#include <bwagency/BwMiaAgentSystem.h>

#include <bwmia/MiaAgent.h>

#include <bwcore/_BwPart.h>
using namespace _BwPart ;

///////////////
namespace _BwMiaAgent {
class MyMailSlot : public BwMailSlot {
public:
	MyMailSlot(BwMiaAgent *pOwner, const bwString& name) : BwMailSlot(pOwner, name) {
		p_agent = pOwner ;
	}
	//Data Members
	BwMiaAgent *p_agent ;
} ;
///////////////
class InnerIn : public MyMailSlot {
public:
	InnerIn(BwMiaAgent *pOwner, const bwString& name) : MyMailSlot(pOwner, name) {
	}
	virtual void dispatch(const BwMessage& msg) {
		bwWhat what = msg.what() ;
		switch(what) {
			case COMMAND_CLOSE :
				p_agent->close() ;
				break ;
		}
	}
} ;
} ; //namespace _BwMiaAgent
///////////////
using namespace _BwMiaAgent ;

BwMiaAgent::BwMiaAgent(BwAgency *pAgency) : BwAgent(pAgency) {
	//f6:fixme:need to sort out this multiple agents per thread mess ... AgentCoOp???
	/*p_inner = static_cast<MiaAgent*>(MiaAgent::produce()) ;
	p_inner->setIoMode(MiaAgent::IO_MESSAGING) ;
	p_inner->createEnabled() ;*/
}
void BwMiaAgent::close() {
	p_inner->close() ;
	destroyPart(p_inner) ;
	BwAgent::close() ;
}
void BwMiaAgent::doCreate(const BwPartInfo& info) {
	BwAgent::doCreate(info) ;

	p_inner = static_cast<MiaAgent*>(MiaAgent::produce()) ;
	p_inner->setName(m_name) ;
	p_inner->setIoMode(MiaAgent::IO_MESSAGING) ;
	p_inner->createEnabled() ;

	p_inSlot = p_inner->getMailBox().findSlot("IN") ;
	m_mailBox.addSlot(p_inSlot) ;
	p_outSlot = p_inner->getMailBox().findSlot("OUT") ;
	m_mailBox.addSlot(p_outSlot) ;
	p_logSlot = p_inner->getMailBox().findSlot("LOG") ;
	m_mailBox.addSlot(p_logSlot) ;
	p_eventSlot = p_inner->getMailBox().findSlot("EVENT") ;
	m_mailBox.addSlot(p_eventSlot) ;
	//
	p_innerIn = new InnerIn(this, "IN") ;
	p_innerIn->create() ;
	//f6:fixme:danger? maybe implement connect and disconnect methods.
	p_innerIn->connect(p_inSlot) ;
}
//Notices & Events
//
BwMailCenter& BwMiaAgent::getMailCenter() {
	return p_inner->getMailCenter() ; 
}