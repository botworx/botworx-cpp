/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _SocWanderer_H
#define _SocWanderer_H

#include "SocTask.h"

namespace SoccerScenario {

class SocWanderer : public SocTask
{
public:
	SocWanderer(BbBrain* pBrain) : SocTask(pBrain) {}
    // one simulation step
	virtual void doStep(BwStepper& stepper) ;
    virtual bool onPostStep(BwStepper& stepper) ;
};

} //namespace SocScenario

#endif _SocWanderer_H
