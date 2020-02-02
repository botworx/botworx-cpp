/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _MpBounder_H
#define _MpBounder_H

#include "MpMover.h"

class BbMapSector ;

namespace MpScenario {

class MpBounder : public MpMover
{
public:
	MpBounder(BbBrain* pBrain) : MpMover(pBrain) { 
	}
	virtual void weigh() ;
	virtual void onEnable(bool sleeping) ;
    //virtual bool onPostStep (BwStepper& stepper) ;
	virtual void doStep(BwStepper& stepper) ;
	//Data Members
	//bwPoint3 m_fleePoint ;
	bwVector3 m_flee ;
};

} //namespace MpScenario

#endif _MpBounder_H

