/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _SocAvoider_H
#define _SocAvoider_H

#include "SocTask.h"

namespace SoccerScenario {

class SocAvoider : public SocTask
{
public:
	SocAvoider(BbBrain* pBrain) : SocTask(pBrain) {}
	//Data Members
	bwVector3 m_avoidance ;
};

class SocStaticAvoider : public SocAvoider
{
public:
	SocStaticAvoider(BbBrain* pBrain) : SocAvoider(pBrain) {}
    // one simulation step
	virtual void doStep(BwStepper& stepper) ;
    virtual bool onPostStep(BwStepper& stepper) ;
};

class SocDynamicAvoider : public SocAvoider
{
public:
	SocDynamicAvoider(BbBrain* pBrain) : SocAvoider(pBrain) {}
    // one simulation step
	virtual void doStep(BwStepper& stepper) ;
    virtual bool onPostStep(BwStepper& stepper) ;
};

} //namespace SocScenario

#endif _SocAvoider_H
