/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <buggybots/scenarios/mpscenario/MpScenario.h>
#include <buggybots/scenarios/mpscenario/MpMover.h>

namespace MpScenario {
/////////////////////////
void MpMover::doStep(BwStepper& stepper) {
	MpTask::doStep(stepper) ;
	avoidStatic() ;
	avoidDynamic() ;
	//
	float elapsedTime = stepper.getDeltaTime() ;
	///////////////////////////////////
	if(m_avoidance != bwVector3())
		m_steer = limitMaxDeviationAngle (m_steer, 0.707f, m_avoidance);
	////
	m_steer = setYtoZero (m_steer);
	pilot().applySteeringForce (m_steer, elapsedTime);
}
bool MpMover::onPostStep (BwStepper& stepper)
{

	// notify proximity database that our position has changed
    pilot().proximityToken->updateForNewPosition (pilot().position());
	//
	return MpTask::onPostStep(stepper) ;
}
void MpMover::avoidStatic() {
	//if ( !pilot().obstacles().empty() )
	if ( !pilot().m_particles.empty() )
    {
		//m_avoidance = pilot().steerToAvoidObstacles (personality().m_minTimeToCollision, pilot().obstacles());
		m_avoidance = pilot().steerToAvoidParticles(personality().m_minTimeToCollision, pilot().m_particles);
    }
	else
		m_avoidance = bwVector3() ;
    // if obstacle avoidance is needed, do it
	personality().setIsStaticAvoiding(m_avoidance != bwVector3()) ;
}
void MpMover::avoidDynamic() {
    // find all neighbors within maxRadius using proximity database
    // (radius is largest distance between vehicles traveling head-on
    // where a collision is possible within caLeadTime seconds.)
	const float caLeadTime = 2 ;
    const float maxRadius = caLeadTime * pilot().maxSpeed() * 2;
    /*personality().neighbors().clear();
    pilot().proximityToken->findNeighbors (pilot().position(), maxRadius, personality().neighbors());*/
	AVGroup& proximity = personality().proximity() ;
	proximity.clear();
	AVGroup& neighbors = personality().neighbors() ;
	neighbors.clear();
	pilot().proximityToken->findNeighbors (pilot().position(), 10, proximity) ;
	for(AVIterator iter = proximity.begin() ; iter != proximity.end() ; ++iter) {
		BbMarker& marker = static_cast<BbMarker&>(**iter) ;
		if(&marker == &pilot())
			continue ;
		if(marker.getCatId() == CAT_PLAYER) {
			neighbors.push_back(&marker) ;
		}
	}


	bwVector3 avoid = pilot().steerToAvoidNeighbors (caLeadTime, personality().neighbors()) * bwReal(10) ;

	if(avoid != bwVector3()) {
		if(m_avoidance != bwVector3())
			m_avoidance = limitMaxDeviationAngle (avoid, 0.707f, m_avoidance);
		else
			m_avoidance = avoid ;
	}
}

} //namespace MpScenario