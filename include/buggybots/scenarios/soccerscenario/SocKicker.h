/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _SocKicker_H
#define _SocKicker_H

#include "SocTask.h"

namespace SoccerScenario {

class SocKicker : public SocTask
{
public:
	SocKicker(BbBrain* pBrain) : SocTask(pBrain) {}
    // one simulation step
    //virtual bool onPostStep(BwStepper& stepper) ;
	virtual void doStep(BwStepper& stepper) ;
};

} //namespace SocScenario

#endif _SocKicker_H
