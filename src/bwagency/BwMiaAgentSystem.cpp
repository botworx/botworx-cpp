#include "stdafx.h"

#include <bwagency/BwMiaAgentSystem.h>
#include <bwagency/BwMiaAgent.h>
//
#include <bwagency/BwAgency.h>

BwMiaAgentSystem::BwMiaAgentSystem(BwKit *pKit) : BwAgentSystem(pKit) {
}
BwAgent* BwMiaAgentSystem::createAgent(agentType type, const bwString& name, BwMessage params, bool enabled) {
	if(type != AGENT_MIA_DEFAULT)
		return NULL ;
	//BwMiaAgent* pAgent = new BwMiaAgent() ;
	BwMiaAgent* pAgent = new BwMiaAgent(static_cast<BwAgency*>(p_owner)) ;
	pAgent->setName(name) ;
	pAgent->setParams(params) ;
	if(enabled)
		pAgent->createEnabled() ;
	else
		pAgent->create() ;
	return pAgent ;
}