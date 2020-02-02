/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <buggybots/scenarios/soccerscenario/SocScenario_common.h>
#include <buggybots/scenarios/soccerscenario/SocScenario.h>
#include <buggybots/scenarios/soccerscenario/SocPersonality.h>
#include <buggybots/scenarios/soccerscenario/SocWanderer.h>
#include <buggybots/scenarios/soccerscenario/SocPursuer.h>
#include <buggybots/scenarios/soccerscenario/SocAvoider.h>
#include <buggybots/scenarios/soccerscenario/SocKicker.h>

namespace SoccerScenario {
///////////
// reset state
void SocPersonality::reset (void)
{
	pilot().setRadius(1) ;
    pilot().setSpeed (0.0f);         // speed along Forward direction.
    pilot().setMaxForce (5);       // steering force is clipped to this magnitude
    pilot().setMaxSpeed (10);       // velocity is clipped to this magnitude
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
}

BwTask* SocPersonality::produceTask(const bwString& name) {
	BbBrain* pBrain = static_cast<BbBrain*>(p_brain) ;
	BwTask *pTask = NULL ;
	BwTaskGroup* pTaskGroup = NULL ;
	//else
	if(name == "WANDERER") {
		pTask = new SocWanderer(pBrain) ;
		pTaskGroup = &m_majorTasks ;
	}
	else
	if(name == "PURSUER") {
		pTask = new SocPursuer(pBrain) ;
		pTaskGroup = &m_majorTasks ;
	}
	else
	if(name == "STATICAVOIDER") {
		pTask = new SocStaticAvoider(pBrain) ;
		pTaskGroup = &m_minorTasks ;
	}
	else
	if(name == "DYNAMICAVOIDER") {
		pTask = new SocDynamicAvoider(pBrain) ;
		pTaskGroup = &m_minorTasks ;
	}
	else
	if(name == "KICKER") {
		pTask = new SocKicker(pBrain) ;
		pTaskGroup = &m_minorTasks ;
	}
	//
	if(pTask != NULL) {
		pTask->setTaskGroup(pTaskGroup) ;
	}
		return pTask ;
}

} //namespace SocScenario {