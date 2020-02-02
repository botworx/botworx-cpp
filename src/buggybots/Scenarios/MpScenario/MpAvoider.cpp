/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <buggybots/scenarios/mpscenario/MpScenario.h>
#include <buggybots/scenarios/mpscenario/MpAvoider.h>
//
#include <bwcore/BwKernel.h>
#include <bwcore/_BwKernel.h>
#include <bwmessaging/BwMailSlot.h>

namespace MpScenario {
/////////////////////////
typedef std::vector<SphericalObstacle> SphericalObstacles ;

typedef SphericalObstacles::iterator SphericalObstacleIter ;

void MpStaticAvoider::weigh() {
	if ( pilot().obstacles().empty() ) {
		m_weight = 0 ;
		return ;
	}
	//else
	SphericalObstacles& spheres = pilot()._spheres ;
	float distSum = 0 ;
	for(SphericalObstacleIter iter = spheres.begin() ; iter != spheres.end() ; ++iter) {
		SphericalObstacle& sphere = *iter ;
		distSum += distance(pilot().position(), sphere.center) ;
	}
	float avgDist = distSum / spheres.size() ;
	//m_weight = (15 - avgDist) * 2 ;
	//m_weight = (10 - avgDist) ;
	m_weight = 10 ;
    // probability that a lower priority behavior will be given a
    // chance to "drive" even if a higher priority behavior might
    // otherwise be triggered.
    const float leakThrough = 0.1f;
	//const float leakThrough = 1 / avgDist ;

	/*if(m_leakTimer.checkAlarm()) {
		if(avgDist > 2) {
			if(!m_leaking)
				m_leaking = true ;
			else
				m_leaking = false ;
		}
		else
			m_leaking = false ;
		m_leakTimer.resetAlarm() ;
	}
	if (m_leaking)
		m_weight = 0 ;
	else
		m_weight = 10 ;*/
}
void MpStaticAvoider::onEnable(bool sleeping) {
	m_leaking = false ;
	_BwKernel::Info evt(brain().model().getName() + " avoiding " + "xxx" + "\n") ;
	BwKernel::singleton::get().getEventSlot()->send(evt) ;
}
void MpStaticAvoider::doStep(BwStepper& stepper) {
	MpAvoider::doStep(stepper) ;
	if ( !pilot().obstacles().empty() )
    {
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

	//steeringForce += m_avoidance ;
	steeringForce = m_avoidance ;
	steeringForce = setYtoZero (steeringForce);
	pilot().applySteeringForce (steeringForce, elapsedTime);
}
bool MpStaticAvoider::onPostStep(BwStepper& stepper)
{
	//if(!personality().isStaticAvoiding()) return MpTask::onPostStep(stepper) ;
	//else
	// notify proximity database that our position has changed
    pilot().proximityToken->updateForNewPosition (pilot().position());
	//
	return MpTask::onPostStep(stepper) ;
}
void MpDynamicAvoider::doStep(BwStepper& stepper) {
	MpAvoider::doStep(stepper) ;
	const float caLeadTime = 2 ;
    // find all neighbors within maxRadius using proximity database
    // (radius is largest distance between vehicles traveling head-on
    // where a collision is possible within caLeadTime seconds.)
    const float maxRadius = caLeadTime * pilot().maxSpeed() * 2;
    personality().neighbors().clear();
    pilot().proximityToken->findNeighbors (pilot().position(), maxRadius, personality().neighbors());

    //if (leakThrough < frandom01())
	m_avoidance = pilot().steerToAvoidNeighbors (caLeadTime, personality().neighbors()) * bwReal(10.0) ;
	bool avoid = m_avoidance != bwVector3() ;
	personality().setIsDynamicAvoiding(avoid) ;
	//
	if(!avoid)
		return ;
	//else
	float elapsedTime = stepper.getDeltaTime() ;
	bwVector3 steeringForce = pilot().forward();
	steeringForce += m_avoidance ;
	steeringForce = setYtoZero (steeringForce);
	pilot().applySteeringForce (steeringForce, elapsedTime);
}
bool MpDynamicAvoider::onPostStep (BwStepper& stepper)
{
	if(personality().isStaticAvoiding())
		return MpTask::onPostStep(stepper) ;
	if(!personality().isDynamicAvoiding())
		return MpTask::onPostStep(stepper) ;

	// notify proximity database that our position has changed
    pilot().proximityToken->updateForNewPosition (pilot().position());

	return MpTask::onPostStep(stepper) ;
}

} //namespace MpScenario