#ifndef _BwMiaAgentSystem_H
#define _BwMiaAgentSystem_H

#include <bwagency/BwAgentSystem.h>

class BwAgent ;
class BwAgentContext ;

class BwMiaAgentSystem : public BwAgentSystem {
public:
	BwMiaAgentSystem(BwKit *pKit) ;
	BwAgent* createAgent(agentType type, const bwString& name, BwMessage params, bool enabled = true) ;
};

#endif //_BwMiaAgentSystem_H
