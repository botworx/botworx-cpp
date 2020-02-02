#ifndef _MpTask_H
#define _MpTask_H

#include <buggybots/BbPilotTask.h>
#include "MpPersonality.h"

namespace MpScenario {

class MpTask : public BbPilotTask {
public:
	MpTask(BbBrain* pBrain) : BbPilotTask(pBrain) {}
	MpPersonality& personality() { return *static_cast<MpPersonality*>(getPersonality()) ; }
	//Data Members
} ;

} //namespace MpScenario {

#endif //_MpTask_H
