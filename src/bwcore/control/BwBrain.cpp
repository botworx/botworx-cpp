/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <bwcontrol/BwBrain.h>
#include <bwcore/BwStage.h>
//
#include <bwcontrol/BwPersonality.h>

BwBrain::BwBrain(BwActor* pActor) : BwTask(pActor) {
	p_stage = &m_taskStage ; 	
	m_taskStage.setOwner(this) ; 
	m_taskStage.create() ;
	//
	m_slaveStage.setOwner(this) ; 
	m_slaveStage.setIsEnsemble(true) ;
	m_slaveStage.create() ;
	//
	setIsStageDriven(false) ; //manually stepped by BwActor.
	m_isSlave = false ;
}
void BwBrain::doConfig() {
	if(p_personality == nullptr) //gives us a chance to specify custom personality after creation, before configuration.
		createPersonality() ;
	BwActor::doConfig() ;
	m_slaveStage.doConfig() ;
}
void BwBrain::doPostConfig() {
	BwActor::doPostConfig() ;
	m_slaveStage.doPostConfig() ;
}
void BwBrain::doEnable(bool sleeping) {
	BwActor::doEnable(sleeping) ;
	m_slaveStage.doEnable(sleeping) ;
}
void BwBrain::doPostEnable(bool sleeping) {
	BwActor::doPostEnable(sleeping) ;
	m_slaveStage.doPostEnable(sleeping) ;
}
void BwBrain::doDisable(bool sleeping) {
	BwActor::doDisable(sleeping) ;
	m_slaveStage.doDisable(sleeping) ;
}
void BwBrain::doPostDisable(bool sleeping) {
	BwActor::doPostDisable(sleeping) ;
	m_slaveStage.doPostDisable(sleeping) ;
}
void BwBrain::doStep(BwStepper& stepper) {
	BwTask::doStep(stepper) ;
	m_slaveStage.doStep(stepper) ;
}
void BwBrain::doPostStep(BwStepper& stepper) {
	BwTask::doPostStep(stepper) ;
	m_slaveStage.doPostStep(stepper) ;
}
BwTask* BwBrain::useTask(const bwString& name) {
	return p_personality->useTask(name) ;
}
void BwBrain::addSlave(BwBrain *pBrain) {
	pBrain->setIsStageDriven(true) ;
	pBrain->setIsSlave(true) ;
	m_slaveStage.addActor(pBrain) ;
	pBrain->setMaster(this) ;
}
void BwBrain::removeSlave(BwBrain *pBrain) {
	m_slaveStage.removeActor(pBrain) ;
}
void BwBrain::setMaster(BwBrain *pBrain) { 
	p_master = pBrain ;
}
void BwBrain::schedule() {
	if(isSlave()) {
		BwStage& stage = p_master->m_slaveStage ;
		stage.scheduleActor(this) ;
		return ;
	}
	//else
	BwActor::schedule() ;
}
bool BwBrain::processMessage(const BwMessage& msg) {
	return true ;
}