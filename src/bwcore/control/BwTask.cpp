/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <bwcontrol/BwTask.h>
#include <bwcontrol/BwBrain.h>
//
#include <bwcontrol/BwPersonality.h>

BwTask::BwTask(BwBrain *pBrain) : BwActor(pBrain) {
	p_brain = pBrain ;
	init() ;
}
BwTask::BwTask(BwActor* pOwner) : BwActor(pOwner) {
	p_brain = nullptr ;
	init() ;
}
void BwTask::init() {
	m_status = PLAN_START ;
	//
	m_hasPlan = false ;
	p_script = nullptr ;
	//
	p_personality = nullptr ;
	p_taskGroup = nullptr ;
	//
	m_baseWeight = 0 ;
	m_weight = 0 ;
}

BwTask::~BwTask() {
	//I'm thinking use the die method here
	//p_brain->removeTask(this) ;
}
void BwTask::doCreate(const BwPartInfo& info) {
	BwActor::doCreate(info) ;
	if(p_taskGroup != nullptr)
		p_taskGroup->addTask(this) ;
}
bool BwTask::testDependencies(taskState status) {
	bool success = true ;
	BwTask *pTask = nullptr ;
	for(BwTaskIter iter = m_dependencies.begin() ; iter != m_dependencies.end() ; ++iter) {
		pTask = *iter ;
		success = success & pTask->testStatus(status) ;
		if(!success)
			break ;
	}
	return success ;
}
void BwTask::doStep(BwStepper& stepper) {
	BwActor::doStep(stepper) ;
	think() ;
}
void BwTask::weigh() {
	m_weight = m_baseWeight ;
}