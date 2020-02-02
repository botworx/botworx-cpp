#ifndef _BbPilotTask_H
#define _BbPilotTask_H

#include "BbTask.h"
#include "BbPilotBrain.h"

class BbPilotTask : public BbTask {
public:
	BbPilotTask(BbBrain* pBrain) : BbTask(pBrain) {}
	BbPilotBrain& brain() { return *static_cast<BbPilotBrain*>(getBrain()) ; }
	BbSteer::BbPilot& pilot() { return brain().pilot() ; }
	//Data Members
} ;

#endif //_BbPilotTask_H
