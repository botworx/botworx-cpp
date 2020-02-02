/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <buggybots/scenarios/soccerscenario/SocScenario_common.h>
#include <buggybots/scenarios/soccerscenario/SocScenario.h>
#include <buggybots/scenarios/soccerscenario/SocPlayer.h>
#include <buggybots/scenarios/soccerscenario/SocTask.h>
//
#include <bwcore/BwKernel.h>
#include <bwmessaging/BwMailSlot.h>
#include <bwvr/VrModel.h>
//
namespace SoccerScenario {
/////////////////////////

class SocPlayerThinker : public SocTask
{
public:
	SocPlayerThinker(BbBrain* pBrain) : SocTask(pBrain) {
		m_seesEnemy = false ;
	}
    // one simulation step
	virtual void doStep(BwStepper& stepper) ;
    //virtual bool onPostStep(BwStepper& stepper) ;
	void setSeesEnemy(bool val) { m_seesEnemy = val ; }
	bool seesEnemy() { return m_seesEnemy ; }
	//Data Members
	bool m_seesEnemy ;
};
void SocPlayerThinker::doStep(BwStepper& stepper) {
	SocTask::doStep(stepper) ;
	bwVector3 ballPos = setYtoOne(personality().m_Ball->position()) ;
	float distHomeToBall = distance (personality().m_home, ballPos);
	if( distHomeToBall < 50) {
		brain().useTask("PURSUER") ;
	}
	else {
		brain().useTask("WANDERER") ;
	}
}
/////////////////////////

BwTask* SocPlayer::produceTask(const bwString& name) {
	BbBrain* pBrain = static_cast<BbBrain*>(p_brain) ;
	BwTask *pTask = NULL ;
	BwTaskGroup* pTaskGroup = NULL ;
	//else
	if(name == "THINKER") {
		pTask = new SocPlayerThinker(pBrain) ;
		pTaskGroup = &m_minorTasks ;
	}
	else
		return SocPersonality::produceTask(name) ;
	//
	if(pTask != NULL) {
		pTask->setTaskGroup(pTaskGroup) ;
	}
	return pTask ;
}

} //namespace SocScenario