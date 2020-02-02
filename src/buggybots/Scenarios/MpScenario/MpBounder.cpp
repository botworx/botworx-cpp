/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <buggybots/scenarios/mpscenario/MpScenario.h>
#include <buggybots/scenarios/mpscenario/MpBounder.h>
#include <buggybots/BbMap.h>
//
#include <bwcore/BwKernel.h>
#include <bwcore/_BwKernel.h>
#include <bwmessaging/BwMailSlot.h>

namespace MpScenario {
/////////////////////////
void MpBounder::weigh() {
	BbMap& map = BbScenario::singleton().getMap() ;
	//TODO:need to track current sector somewhere higher up.
	if(map.findSector(pilot().position()) == NULL) {
		return MpMover::weigh() ; //will set relevance to base relevance.
	}
	else
		setWeight(0) ;
}
void MpBounder::onEnable(bool sleeping) {
	//m_fleePoint = pilot().position() ;
	m_flee = -pilot().forward() ;
	_BwKernel::Info evt(brain().model().getName() + " inbounding " + "xxx" + "\n") ;
	BwKernel::singleton::get().getEventSlot()->send(evt) ;
}
void MpBounder::doStep(BwStepper& stepper)
{
	MpMover::doStep(stepper) ;
	float elapsedTime = stepper.getDeltaTime() ;
    //bwVector3 steeringForce ;
	m_steer = bwVector3() ;

    //const bwVector3 eOffset = e.position() - pilot().position();
    //const float eDistance = length(eOffset) ;

    // xxx maybe this should take into account e's heading? xxx
    //const float timeEstimate = 0.5f * eDistance / e.speed(); //xxx const bwVector3 eFuture = e.predictFuturePosition (timeEstimate);
	const bwVector3 eFuture = pilot().predictFuturePosition (1);
    // annotation
    //annotationXZCircle (e.radius(), eFuture, evadeColor, 20);

    // steering to flee from eFuture (enemy's future position)
    //const bwVector3 flee = pilot().xxxsteerForFlee (eFuture);
	//const bwVector3 flee = pilot().xxxsteerForFlee (m_fleePoint);
	const bwVector3 flee = m_flee ;

    //const float eForwardDistance = dot(pilot().forward(),eOffset);
    //const float behindThreshold = pilot().radius() * -2;
    //const float distanceWeight = 4 / eDistance;
    //const float forwardWeight = ((eForwardDistance > behindThreshold) ? 1.0f : 0.5f);
    //const bwVector3 adjustedFlee = flee * distanceWeight * forwardWeight;
	//const bwVector3 adjustedFlee = flee ;

	//m_steer += adjustedFlee;
	m_steer = flee ;
	//
	m_avoidance = bwVector3() ; //need to override avoidance!
}

} //namespace MpScenario