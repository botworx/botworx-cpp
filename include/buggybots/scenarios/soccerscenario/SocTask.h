#ifndef _SocTask_H
#define _SocTask_H

#include <buggybots/BbPilotTask.h>

#include "SocPersonality.h"

namespace SoccerScenario {

class SocTask : public BbPilotTask {
public:
	SocTask(BbBrain* pBrain) : BbPilotTask(pBrain) {}
	SocPersonality& personality() { return *static_cast<SocPersonality*>(getPersonality()) ; }
	//Data Members
} ;

} //namespace SocScenario {

#endif //_SocTask_H