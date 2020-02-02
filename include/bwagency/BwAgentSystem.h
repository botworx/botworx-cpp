#ifndef _BwAgentSystem_H
#define _BwAgentSystem_H

#include <bwcore/BwSystem.h>

class BwAgent ;
//class BwAgentContext ;

class BwAgentSystem : public BwSystem {
public:
	BwAgentSystem(BwKit *pKit) ;
	//
	virtual BwAgent* createAgent(agentType type, const bwString& name, BwMessage params, bool enabled = true) = 0 ;
private:
};
typedef std::vector<BwAgentSystem*> BwAgentSystems ;
typedef BwAgentSystems::iterator BwAgentSystemIter ;

#endif //_BwAgentSystem_H
