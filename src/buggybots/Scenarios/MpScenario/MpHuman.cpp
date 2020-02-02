/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <buggybots/scenarios/mpscenario/MpScenario.h>
#include <buggybots/scenarios/mpscenario/MpHuman.h>
#include <buggybots/scenarios/mpscenario/MpTask.h>
//
#include <bwcore/BwKernel.h>
#include <bwmessaging/BwMailSlot.h>
//
namespace MpScenario {
using namespace BbSteer ;
/////////////////////////

class MpHumanThinker : public MpTask
{
public:
	MpHumanThinker(BbBrain* pBrain) : MpTask(pBrain) {
	}
    // one simulation step
	virtual void doStep(BwStepper& stepper) ;
	//Data Members
};
void MpHumanThinker::doStep(BwStepper& stepper) {
	MpTask::doStep(stepper) ;
	BwTask* pTask = personality().m_majorTasks.findMrp() ;
	if(!pTask->isActive())
		personality().useTask(pTask) ;
}
/////////////////////////

BwTask* MpHuman::produceTask(const bwString& name) {
	BbBrain* pBrain = static_cast<BbBrain*>(p_brain) ;
	BwTask *pTask = NULL ;
	BwTaskGroup* pTaskGroup = NULL ;
	//else
	if(name == "THINKER") {
		pTask = new MpHumanThinker(pBrain) ;
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