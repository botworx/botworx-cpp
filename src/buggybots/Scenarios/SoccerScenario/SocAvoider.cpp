/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <buggybots/scenarios/soccerscenario/SocScenario_common.h>
#include <buggybots/scenarios/soccerscenario/SocScenario.h>
#include <buggybots/scenarios/soccerscenario/SocAvoider.h>

namespace SoccerScenario {
/////////////////////////
void SocStaticAvoider::doStep(BwStepper& stepper) {
	SocAvoider::doStep(stepper) ;
	if ( !pilot().obstacles().empty() ) {
		m_avoidance = pilot().steerToAvoidObstacles (personality().m_minTimeToCollision, pilot().obstacles());
    }
    // if obstacle avoidance is needed, do it
	bool avoid = m_avoidance != bwVector3() ;
	personality().setIsStaticAvoiding(avoid) ;
	if(!avoid)
		return ;
	//else
	float elapsedTime = stepper.getDeltaTime() ;
	///////////////////////////////////
    // move forward
    bwVector3 steeringForce = pilot().forward();
	steeringForce += m_avoidance ;
	steeringForce = setYtoZero (steeringForce);
	pilot().applySteeringForce (steeringForce, elapsedTime);
}
bool SocStaticAvoider::onPostStep (BwStepper& stepper)
{
	if(!personality().isStaticAvoiding())
		return SocTask::onPostStep(stepper) ;
	//else
	// notify proximity database that our position has changed
    pilot().proximityToken->updateForNewPosition (pilot().position());
	//
	return SocTask::onPostStep(stepper) ;
}
void SocDynamicAvoider::doStep(BwStepper& stepper) {
	SocAvoider::doStep(stepper) ;
	const float caLeadTime = 2 ;
    // find all neighbors within maxRadius using proximity database
    // (radius is largest distance between vehicles traveling head-on
    // where a collision is possible within caLeadTime seconds.)
    const float maxRadius = caLeadTime * pilot().maxSpeed() * 2;
    personality().neighbors.clear();
    pilot().proximityToken->findNeighbors (pilot().position(), maxRadius, personality().neighbors);

	m_avoidance = pilot().steerToAvoidNeighbors (caLeadTime, personality().neighbors) * bwReal(10) ;
	bool avoid = m_avoidance != bwVector3() ;
	personality().setIsDynamicAvoiding(avoid) ;
	if(!avoid)
		return ;
	//else
	float elapsedTime = stepper.getDeltaTime() ;
	bwVector3 steeringForce = pilot().forward();
	steeringForce += m_avoidance ;
	steeringForce = setYtoZero (steeringForce);
	pilot().applySteeringForce (steeringForce, elapsedTime);
}
bool SocDynamicAvoider::onPostStep (BwStepper& stepper)
{
	if(personality().isStaticAvoiding())
		return SocTask::onPostStep(stepper) ;
	if(!personality().isDynamicAvoiding())
		return SocTask::onPostStep(stepper) ;
	//else
	// notify proximity database that our position has changed
    pilot().proximityToken->updateForNewPosition (pilot().position());

	return SocTask::onPostStep(stepper) ;
}

} //namespace SoccerScenario