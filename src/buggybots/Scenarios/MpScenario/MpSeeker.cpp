/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <buggybots/scenarios/mpscenario/MpScenario.h>
#include <buggybots/scenarios/mpscenario/MpSeeker.h>
#include <buggybots/BbMap.h>
//
#include <bwcore/BwKernel.h>
#include <bwcore/_BwKernel.h>
#include <bwmessaging/BwMailSlot.h>

namespace MpScenario {
/////////////////////////
void MpSeeker::weigh() {
	BbMap& map = BbScenario::singleton().getMap() ;
	//
	BbMarker* pItem = NULL ;
	BbMarker* pTargetItem = NULL ;
	BbMarker* pOldTargetItem = personality().p_item ;
	if(pOldTargetItem != NULL)
		return MpMover::weigh() ; //will set relevance to base relevance.
	AVGroup& items = personality().items() ;
	items.clear();
	pilot().proximityToken->findNeighbors (pilot().position(), 10, items) ;
	for(AVIterator iter = items.begin() ; iter != items.end() ; ++iter) {
		BbMarker& marker = static_cast<BbMarker&>(**iter) ;
		if(marker.getCatId() == CAT_ITEM) {
			pItem = &marker ;			
			bool sees = map.testLos(pilot().position(), pItem->position()) ;
			if(sees) {
				pTargetItem = pItem ;
				break ;
			}
		}
	}
	personality().p_item = pTargetItem ;
	//
	if(pTargetItem != NULL) {
		_BwKernel::Info evt(brain().model().getName() + " seeking " + pTargetItem->getModel()->getName() + "\n") ;
		BwKernel::singleton::get().getEventSlot()->send(evt) ;
		return MpMover::weigh() ; //will set relevance to base relevance.
	}
	else
		setWeight(0) ;
}
void MpSeeker::onEnable(bool sleeping) {
	p_itemSector = NULL ;
}
void MpSeeker::doStep(BwStepper& stepper)
{
	MpMover::doStep(stepper) ;
	BbMarker* pItem = personality().p_item ;
	if(pItem == NULL)
		return ;
	//else
	float elapsedTime = stepper.getDeltaTime() ;
    // when pursuer touches quarry ("wanderer"), reset its position
	const float d = distance (pilot().position(), pItem->position());
    const float r = pilot().radius() + pItem->radius();
	if (d < r) {
		VrModel* pModel = pItem->getModel() ;
		if(pModel->isSleeping())
			pModel->wake() ;
		pModel->die() ;
		personality().p_item = NULL ;
		pItem->destroy() ;
		//personality().useTask("WANDERER") ;
		return ;
	}
	///////////////////////////////////
		    // move forward
    //bwVector3 steeringForce = pilot().forward();
	m_steer = pilot().forward();

	BbMap& map = BbScenario::singleton().getMap() ;
	BbMapSector* pSector = map.findSector(pilot().position()) ;
	BbMapSector* pOldItemSector = p_itemSector ;
	p_itemSector = map.findSector(pItem->position()) ;

	if(pSector != p_itemSector && pOldItemSector != p_itemSector) {
		BbMapPath path = map.findPath(pSector, p_itemSector) ;
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
		//steeringForce = pilot().steerForPursuit(*pItem, maxTime) ;
		//steeringForce = pilot().steerForSeek(pItem->position()) ;
		m_steer = pilot().steerForSeek(pItem->position()) ;
	}

	//steeringForce = setYtoZero (steeringForce) ;
	//pilot().applySteeringForce (steeringForce, elapsedTime);
	// notify proximity database that our position has changed
    //pilot().proximityToken->updateForNewPosition (pilot().position());
	//
	//return MpTask::onPostStep(stepper) ;
}

} //namespace MpScenario