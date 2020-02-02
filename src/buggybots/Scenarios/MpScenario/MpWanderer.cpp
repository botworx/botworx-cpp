/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <buggybots/scenarios/mpscenario/MpScenario.h>
#include <buggybots/scenarios/mpscenario/MpWanderer.h>

namespace MpScenario {
/////////////////////////
void MpWanderer::doStep(BwStepper& stepper)
{
	MpMover::doStep(stepper) ;
	//if(personality().isAvoiding()) return MpTask::onPostStep(stepper) ;
	//else
	float elapsedTime = stepper.getDeltaTime() ;
	///////////////////////////////////
		    // move forward
    //bwVector3 steeringForce = pilot().forward();
	m_steer = pilot().forward();
	//bwVector3 steeringForce ;
	//steeringForce += pilot().steerForWander (elapsedTime) * 3.0f ;
	m_steer += pilot().steerForWander (elapsedTime) * bwReal(3.0f) ;

	//steeringForce = setYtoZero (steeringForce);
	//pilot().applySteeringForce (steeringForce, elapsedTime);

	// notify proximity database that our position has changed
    //pilot().proximityToken->updateForNewPosition (pilot().position());
	//
}

} //namespace MpScenario