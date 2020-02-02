#include "stdafx.h"

#include <bwagency/BwAgent.h>
#include <bwagency/BwAgency.h>
#include <bwagency/BwAgentSession.h>

BwAgent::BwAgent(BwAgency *pAgency) : BwService(pAgency) {
}
void BwAgent::doCreate(const BwPartInfo& info) {
	BwService::doCreate(info) ;
	BwLocalAgency::singleton::get().addAgent(this) ; //f6:fixme:???!!!
}
BwSession* BwAgent::produceSession() { 
	BwAgentSession* pSession = new BwAgentSession(this) ;
	pSession->create() ;
	//pSession->connect(this) ; //f6:fixme???
	return pSession ;
}
bool BwAgent::onClose() {
	BwLocalAgency::singleton::get().onAgentClose(this) ;
	return true ;
}
//f6:maybe move into BwService?
void BwAgent::doCommand(const BwCmd& cmd) {
}