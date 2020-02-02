/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _MpPursuer_H
#define _MpPursuer_H

#include "MpMover.h"

class BbMapSector ;

namespace MpScenario {

class MpPursuer : public MpMover
{
public:
	MpPursuer(BbBrain* pBrain) : MpMover(pBrain) { 
		p_enemySector = NULL ; 
	}
	virtual void weigh() ;
	virtual void onEnable(bool sleeping) ;
    //virtual bool onPostStep (BwStepper& stepper) ;
	virtual void doStep(BwStepper& stepper) ;
	//
	//Data Members
	BbMapSector* p_enemySector ;
};

} //namespace MpScenario

#endif _MpPursuer_H
