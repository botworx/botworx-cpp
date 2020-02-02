/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _MpSeeker_H
#define _MpSeeker_H

#include "MpMover.h"

class BbMapSector ;

namespace MpScenario {

class MpSeeker : public MpMover
{
public:
	MpSeeker(BbBrain* pBrain) : MpMover(pBrain) { p_itemSector = NULL ; }
	virtual void weigh() ;
	virtual void onEnable(bool sleeping) ;
    //virtual bool onPostStep (BwStepper& stepper) ;
	virtual void doStep(BwStepper& stepper) ;
	//Data Members
	BbMapSector* p_itemSector ;
};

} //namespace MpScenario

#endif _MpSeeker_H
