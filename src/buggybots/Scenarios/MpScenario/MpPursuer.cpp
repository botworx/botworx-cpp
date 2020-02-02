/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <buggybots/scenarios/mpscenario/MpScenario.h>
#include <buggybots/scenarios/mpscenario/MpPursuer.h>
#include <buggybots/BbMap.h>
//
#include <bwcore/BwKernel.h>
#include <bwcore/_BwKernel.h>
#include <bwmessaging/BwMailSlot.h>

namespace MpScenario {
/////////////////////////
void MpPursuer::weigh() {
	BbMarker* pEnemy = NULL ;
	BbMarker* pTargetEnemy = NULL ;
	BbMarker* pOldTargetEnemy = personality().p_enemy ;
	if(pOldTargetEnemy != NULL)
		return MpMover::weigh() ; //will set relevance to base relevance.

	BbPilot& wanderer = *personality().wanderer ;
	BbMap& map = BbScenario::singleton().getMap() ;
	//
	bool sees = map.testLos(pilot().position(), wanderer.position()) ;
	if(sees)
		pTargetEnemy = &wanderer ;
	personality().p_enemy = pTargetEnemy ;

	if(pTargetEnemy != NULL) {
		_BwKernel::Info evt(brain().model().getName() + " pursuing " + pTargetEnemy->getModel()->getName() + "\n") ;
		BwKernel::singleton::get().getEventSlot()->send(evt) ;
		return MpMover::weigh() ; //will set relevance to base relevance.
	}
	else
		setWeight(0) ;
}
void MpPursuer::onEnable(bool sleeping) {
	p_enemySector = NULL ;
}
void MpPursuer::doStep(BwStepper& stepper)
{
	MpMover::doStep(stepper) ;
	float elapsedTime = stepper.getDeltaTime() ;
	BbPilot* wanderer = personality().wanderer ;
    // when pursuer touches quarry ("wanderer"), reset its position
	const float d = distance (pilot().position(), personality().wanderer->position());
    const float r = pilot().radius() + wanderer->radius();
    //if (d < r) reset ();
	///////////////////////////////////
		    // move forward
    //bwVector3 steeringForce = pilot().forward();
	m_steer = pilot().forward();

	BbMap& map = BbScenario::singleton().getMap() ;
	BbMapSector* pSector = map.findSector(pilot().position()) ;
	BbMapSector* pOldEnemySector = p_enemySector ;
	p_enemySector = map.findSector(wanderer->position()) ;

	if(pSector != p_enemySector && pOldEnemySector != p_enemySector) {
		BbMapPath path = map.findPath(pSector, p_enemySector) ;
		if(!path.empty()) {
			personality().m_path.clear() ;
			for(BbMapPathIter iter = path.begin() ; iter != path.end() ; ++iter) {
				BbMapSector& sector = **iter ;
				personality().m_path.addPoint(sector.getPos()) ;
			}
			personality().m_path.compute(2, false) ;
			//steeringForce = pilot().steerToFollowPath (1, 3, personality().m_path) ;
			m_steer = pilot().steerToFollowPath (1, 3, personality().m_path) ;
		}
	}
	else {
		//const float maxTime = 20; // xxx hard-to-justify value
		const float maxTime = 6 ; // xxx hard-to-justify value
		//steeringForce = pilot().steerForPursuit(*wanderer, maxTime) ;
		if (d > 3)
			m_steer = pilot().steerForPursuit(*wanderer, maxTime) ;
		else {
			//m_steer = pilot().steerForSeek(wanderer->position() + (wanderer->forward() * wanderer->radius())) ;
			m_steer = pilot().steerForSeek(wanderer->position()) ;
	        // xxx maybe this should take into account e's heading? xxx
			//const float timeEstimate = 0.5f * d / wanderer->speed(); //xxx
			//const bwVector3 eFuture = wanderer->predictFuturePosition (timeEstimate);
			//m_steer = pilot().steerForSeek(eFuture) ;
		}
	}

	//steeringForce = setYtoZero (steeringForce) ;
	//pilot().applySteeringForce (steeringForce, elapsedTime);
	// notify proximity database that our position has changed
    //pilot().proximityToken->updateForNewPosition (pilot().position());
	//
	//return MpTask::onPostStep(stepper) ;
}


} //namespace MpScenario