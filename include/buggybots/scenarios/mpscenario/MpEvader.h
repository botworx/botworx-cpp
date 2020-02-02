/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _MpEvader_H
#define _MpEvader_H

#include "MpMover.h"

class BbMapSector ;

namespace MpScenario {

class MpEvader : public MpMover
{
public:
	MpEvader(BbBrain* pBrain) : MpMover(pBrain) { 
	}
	virtual void weigh() ;
	virtual void onEnable(bool sleeping) ;
    //virtual bool onPostStep (BwStepper& stepper) ;
	virtual void doStep(BwStepper& stepper) ;
	//
	//Data Members
};

} //namespace MpScenario

#endif _MpEvader_H
