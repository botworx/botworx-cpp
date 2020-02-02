/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _SocPursuer_H
#define _SocPursuer_H

#include "SocTask.h"

class BbMapSector ;

namespace SoccerScenario {

class SocPursuer : public SocTask
{
public:
	SocPursuer(BbBrain* pBrain) : SocTask(pBrain) { p_enemySector = NULL ; }
    //virtual bool onPostStep (BwStepper& stepper) ;
	virtual void doStep(BwStepper& stepper) ;
	//Data Members
	BbMapSector* p_enemySector ;
};

} //namespace SocScenario

#endif _SocPursuer_H
