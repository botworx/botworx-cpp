/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <buggybots/scenarios/mpscenario/MpScenario.h>
#include <buggybots/scenarios/mpscenario/MpEvader.h>
#include <buggybots/BbMap.h>
//
#include <bwcore/BwKernel.h>
#include <bwcore/_BwKernel.h>
#include <bwmessaging/BwMailSlot.h>

namespace MpScenario {
/////////////////////////
void MpEvader::weigh() {
	BbMap& map = BbScenario::singleton().getMap() ;
	AVGroup& neighbors = personality().neighbors() ;
	neighbors.clear();
	AVGroup& pursuers = personality().pursuers() ;
	pursuers.clear();
	pilot().proximityToken->findNeighbors (pilot().position(), 10, neighbors) ;
	for(AVIterator iter = neighbors.begin() ; iter != neighbors.end() ; ++iter) {
		BbMarker& marker = static_cast<BbMarker&>(**iter) ;
		if(&marker == &pilot())
			continue ;
		if(marker.getCatId() == CAT_PLAYER) {
			bool sees = map.testLos(pilot().position(), marker.position()) ;
			if(sees) {
				pursuers.push_back(&marker) ;
			}
		}
	}

	if(!pursuers.empty()) {
		return MpMover::weigh() ; //will set relevance to base relevance.
	}
	else
		setWeight(0) ;
}
void MpEvader::onEnable(bool sleeping) {
	_BwKernel::Info evt(brain().model().getName() + " evading " + "xxx" + "\n") ;
	BwKernel::singleton::get().getEventSlot()->send(evt) ;
}
void MpEvader::doStep(BwStepper& stepper)
{
	MpMover::doStep(stepper) ;
	bwReal elapsedTime = stepper.getDeltaTime() ;
    //bwVector3 steeringForce ;
	m_steer = bwVector3() ;
	AVGroup& pursuers = personality().pursuers() ;
    for (AVIterator iter = pursuers.begin() ; iter != pursuers.end() ; ++iter)
    {
        const BbMarker& e = static_cast<BbMarker&>(**iter) ;
        const bwVector3 eOffset = e.position() - pilot().position();
        const bwReal eDistance = length(eOffset) ;

        // xxx maybe this should take into account e's heading? xxx
        const bwReal timeEstimate = 0.5f * eDistance / e.speed(); //xxx
        const bwVector3 eFuture = e.predictFuturePosition (timeEstimate);

        // annotation
        //annotationXZCircle (e.radius(), eFuture, evadeColor, 20);

        // steering to flee from eFuture (enemy's future position)
        const bwVector3 flee = pilot().xxxsteerForFlee (eFuture);

        const bwReal eForwardDistance = dot(pilot().forward(),eOffset);
        const bwReal behindThreshold = pilot().radius() * -2;

        const bwReal distanceWeight = 4 / eDistance;
        const bwReal forwardWeight = ((eForwardDistance > behindThreshold) ?
                                     1.0f : 0.5f);

        //const bwVector3 adjustedFlee = flee * distanceWeight * forwardWeight;
		const bwVector3 adjustedFlee = flee ;

        //steeringForce += adjustedFlee;
		m_steer += adjustedFlee;
    }

	//steeringForce = setYtoZero (steeringForce) ;
	//pilot().applySteeringForce (steeringForce, elapsedTime);
	// notify proximity database that our position has changed
    //pilot().proximityToken->updateForNewPosition (pilot().position());
}

} //namespace MpScenario