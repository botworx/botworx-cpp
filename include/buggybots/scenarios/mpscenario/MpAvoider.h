/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _MpAvoider_H
#define _MpAvoider_H

#include "MpTask.h"

namespace MpScenario {

class MpAvoider : public MpTask
{
public:
	MpAvoider(BbBrain* pBrain) : MpTask(pBrain) {}
	//Data Members
	bwVector3 m_avoidance ;
};

class MpStaticAvoider : public MpAvoider
{
public:
	MpStaticAvoider(BbBrain* pBrain) : MpAvoider(pBrain) {
		m_leaking = false ;
	}
    // one simulation step
	virtual void weigh() ;
	virtual void doStep(BwStepper& stepper) ;
	virtual void onEnable(bool sleeping) ;
    virtual bool onPostStep(BwStepper& stepper) ;
	//Data Members
	BwLoTimer m_leakTimer ;
	bool m_leaking ;
};

class MpDynamicAvoider : public MpAvoider
{
public:
	MpDynamicAvoider(BbBrain* pBrain) : MpAvoider(pBrain) {}
    // one simulation step
	virtual void doStep(BwStepper& stepper) ;
    virtual bool onPostStep(BwStepper& stepper) ;
};

} //namespace MpScenario

#endif _MpAvoider_H
