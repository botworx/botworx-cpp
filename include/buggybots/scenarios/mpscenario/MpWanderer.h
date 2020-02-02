/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _MpWanderer_H
#define _MpWanderer_H

#include "MpMover.h"

namespace MpScenario {

class MpWanderer : public MpMover
{
public:
	MpWanderer(BbBrain* pBrain) : MpMover(pBrain) {}
    // one simulation step
    //virtual bool onPostStep(BwStepper& stepper) ;
	virtual void doStep(BwStepper& stepper) ;
};

} //namespace MpScenario

#endif _MpWanderer_H
