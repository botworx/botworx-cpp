/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <buggybots/scenarios/soccerscenario/SocScenario_common.h>
#include <buggybots/scenarios/soccerscenario/SocScenario.h>
#include <buggybots/scenarios/soccerscenario/SocWanderer.h>

namespace SoccerScenario {
/////////////////////////
void SocWanderer::doStep(BwStepper& stepper) 
{
	SocTask::doStep(stepper) ;
	if(personality().isAvoiding())
		return ;
	//else
	float elapsedTime = stepper.getDeltaTime() ;
	///////////////////////////////////
		    // move forward
    bwVector3 steeringForce = pilot().forward();

    bwVector3 seekTarget = pilot().xxxsteerForSeek(personality().m_home);
    bwVector3 seekHome = pilot().xxxsteerForSeek(personality().m_home);
	steeringForce = seekTarget+seekHome ;

	steeringForce = setYtoZero (steeringForce);
	pilot().applySteeringForce (steeringForce, elapsedTime);
}
bool SocWanderer::onPostStep (BwStepper& stepper)
{
	if(personality().isAvoiding())
		return SocTask::onPostStep(stepper) ;
	//else
	// notify proximity database that our position has changed
    pilot().proximityToken->updateForNewPosition (pilot().position());
	//
	return SocTask::onPostStep(stepper) ;
}

} //namespace SoccerScenario