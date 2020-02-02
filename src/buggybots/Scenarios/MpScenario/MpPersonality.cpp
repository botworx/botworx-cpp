/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <buggybots/scenarios/mpscenario/MpScenario.h>
#include <buggybots/scenarios/mpscenario/MpPersonality.h>
#include <buggybots/scenarios/mpscenario/MpWanderer.h>
#include <buggybots/scenarios/mpscenario/MpPursuer.h>
#include <buggybots/scenarios/mpscenario/MpAvoider.h>
#include <buggybots/scenarios/mpscenario/MpSeeker.h>
#include <buggybots/scenarios/mpscenario/MpEvader.h>
#include <buggybots/scenarios/mpscenario/MpBounder.h>

namespace MpScenario {
///////////
// reset state
void MpPersonality::reset (void)
{
    //BbPilot::reset (); // reset the vehicle 
	pilot().setRadius(2) ;
    pilot().setSpeed (0.0f);         // speed along Forward direction.
    pilot().setMaxForce (5.0);       // steering force is clipped to this magnitude
    pilot().setMaxSpeed (5.0);       // velocity is clipped to this magnitude
    // Place me on my part of the field, looking at oponnents goal
    if(m_MyID < 9)
        {
        if(b_ImTeamA)
            pilot().setPosition(playerPosition[m_MyID]);
        else
			pilot().setPosition(bwVector3(-playerPosition[m_MyID][0], playerPosition[m_MyID][1], playerPosition[m_MyID][2]));
        }
    m_home = pilot().position();
    // notify proximity database that our position has changed
    pilot().proximityToken->updateForNewPosition (m_home);
	//
	m_minTimeToCollision = 12 ;
	//
	p_item = NULL ;
	p_enemy = NULL ;
}
BwTask* MpPersonality::produceTask(const bwString& name) {
	BbBrain* pBrain = static_cast<BbBrain*>(p_brain) ;
	BwTask *pTask = NULL ;
	BwTaskGroup* pTaskGroup = NULL ;
	//else
	if(name == "WANDERER") {
		pTask = new MpWanderer(pBrain) ;
		pTask->setBaseWeight(1) ;
		pTaskGroup = &m_majorTasks ;
	}
	else
	if(name == "SEEKER") {
		pTask = new MpSeeker(pBrain) ;
		pTask->setBaseWeight(5) ;
		pTaskGroup = &m_majorTasks ;
	}
	else
	if(name == "EVADER") {
		pTask = new MpEvader(pBrain) ;
		pTask->setBaseWeight(7) ;
		pTaskGroup = &m_majorTasks ;
	}
	else
	if(name == "BOUNDER") {
		pTask = new MpBounder(pBrain) ;
		pTask->setBaseWeight(10) ;
		pTaskGroup = &m_majorTasks ;
	}
	else
	if(name == "PURSUER") {
		pTask = new MpPursuer(pBrain) ;
		pTask->setBaseWeight(5) ;
		pTaskGroup = &m_majorTasks ;
	}
	else
	if(name == "STATICAVOIDER") {
		pTask = new MpStaticAvoider(pBrain) ;
		pTask->setBaseWeight(2) ;
		//pTaskGroup = &m_minorTasks ;
		pTaskGroup = &m_majorTasks ;
	}
	else
	if(name == "DYNAMICAVOIDER") {
		pTask = new MpDynamicAvoider(pBrain) ;
		pTaskGroup = &m_minorTasks ;
	}
	//
	if(pTask != NULL) {
		pTask->setTaskGroup(pTaskGroup) ;
	}
		return pTask ;
}

} //namespace MpScenario {