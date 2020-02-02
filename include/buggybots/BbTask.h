#ifndef _BbTask_H
#define _BbTask_H

#include <bwcontrol/BwTask.h>
#include "BbBrain.h"

class BbTask : public BwTask {
public:
	BbTask(BbBrain* pBrain) : BwTask(pBrain) {}
	BbBrain& brain() { return *static_cast<BbBrain*>(getBrain()) ; }
	//BbPilot& pilot() { return brain().pilot() ; }
	BbSteer::BbMarker& marker() { return brain().marker() ; }
	//Data Members
} ;

#endif //_BbTask_H
