/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <buggybots/scenarios/mpscenario/MpScenario.h>
#include <buggybots/scenarios/mpscenario/MpDroid.h>
#include <buggybots/scenarios/mpscenario/MpTask.h>
//
#include <bwcore/BwKernel.h>
#include <bwmessaging/BwMailSlot.h>
//
namespace MpScenario {
/////////////////////////

class MpDroidThinker : public MpTask
{
public:
	MpDroidThinker(BbBrain* pBrain) : MpTask(pBrain) {
		//m_seesEnemy = false ;
	}
	virtual void doStep(BwStepper& stepper) ;
};
void MpDroidThinker::doStep(BwStepper& stepper) {
	MpTask::doStep(stepper) ;
	BwTask* pTask = personality().m_majorTasks.findMrp() ;
	if(!pTask->isActive())
		personality().useTask(pTask) ;
}
/////////////////////////

BwTask* MpDroid::produceTask(const bwString& name) {
	BbBrain* pBrain = static_cast<BbBrain*>(p_brain) ;
	BwTask *pTask = NULL ;
	BwTaskGroup* pTaskGroup = NULL ;
	//else
	if(name == "THINKER") {
		pTask = new MpDroidThinker(pBrain) ;
		pTaskGroup = &m_minorTasks ;
	}
	else
		return MpPersonality::produceTask(name) ;
	//
	if(pTask != NULL) {
		pTask->setTaskGroup(pTaskGroup) ;
	}
	return pTask ;
}

} //namespace MpScenario