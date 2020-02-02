/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _MpMover_H
#define _MpMover_H

#include "MpTask.h"

namespace MpScenario {

class MpMover : public MpTask
{
public:
	MpMover(BbBrain* pBrain) : MpTask(pBrain) {}
    // one simulation step
	virtual void doStep(BwStepper& stepper) ;
    virtual bool onPostStep(BwStepper& stepper) ;
	//
	virtual void avoidStatic() ;
	virtual void avoidDynamic() ;
	//Data Members
	bwVector3 m_steer ;
	bwVector3 m_avoidance ;
};

} //namespace MpScenario

#endif _MpMover_H
