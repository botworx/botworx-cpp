/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <bwcore/BwActor.h>
#include <bwcore/BwFactory.h>

#include <bwcore/BwStage.h>
#include <bwcontrol/BwBrain.h>

BwActor::BwActor(BwActor *pParent) : BwPart(pParent) {
	p_brain = nullptr ;
	p_stage = nullptr ;
	m_isStageDriven = true ;
	m_isStageDriver = true ;
	m_isAutoSleeper = false ;
	m_isMigrating = false ;
	m_state = DISABLED ;
}
BwActor::~BwActor() {
	if(getBrain() != nullptr)
		destroyPart(getBrain()) ;
}
void BwActor::doCreate(const BwPartInfo& info){
	BwPart::doCreate(info) ;
}
bool BwActor::onCreate(const BwPartInfo& info) {
	createBrain() ;
	return BwPart::onCreate(info) ;
}
void BwActor::doConfig() {
	if(getStage() != nullptr)
		getStage()->doConfig() ;
	if(getBrain() != nullptr)			//I think ... this way all sub parts are ready before brain call...
		getBrain()->doConfig() ;
	BwPart::doConfig() ;
}
void BwActor::doPostConfig() {
	if(getStage() != nullptr)
		getStage()->doPostConfig() ;
	if(getBrain() != nullptr)
		getBrain()->doPostConfig() ;
	BwPart::doPostConfig() ;
}
void BwActor::doEnable(bool sleeping) {
	if(!sleeping && isActive())
		//return ;
		return BwPart::doEnable(sleeping) ; //not sleeping

	setState(WAKING) ;
	//
	if(getStage() != nullptr) {
		getStage()->doEnable(sleeping) ;
	}
	if(getBrain() != nullptr)
		getBrain()->doEnable(sleeping) ;

	if(isDozing())
		sleeping = true ;

	if(!sleeping) {
			schedule() ;
	}
	else
		setState(SLEEPING) ;

	return BwPart::doEnable(sleeping) ;
}
void BwActor::doPostEnable(bool sleeping) {
	if(getStage() != nullptr)
		getStage()->doPostEnable(sleeping) ;
	if(getBrain() != nullptr)
		getBrain()->doPostEnable(sleeping) ;

	if(!isSleeping())
		setState(ACTING) ;

	BwPart::doPostEnable(sleeping) ;
}
void BwActor::doDisable(bool sleeping) {
	if(getStage() != nullptr)
		getStage()->doDisable(sleeping) ;
	if(getBrain() != nullptr)
		getBrain()->doDisable(sleeping) ;

	if(sleeping)
		setState(SLEEPING) ;
	else
		setState(DISABLED) ;

	BwPart::doDisable(sleeping) ;
}
void BwActor::doPostDisable(bool sleeping) {
	if(getStage() != nullptr)
		getStage()->doPostDisable(sleeping) ;
	if(getBrain() != nullptr)
		getBrain()->doPostDisable(sleeping) ;

	BwPart::doPostDisable(sleeping) ;
}
void BwActor::doStep(BwStepper& stepper) {
	bwAssert(m_isInitialised) ;
	//TODO:later:reenable these tests!!!
	//bwAssert(m_isConfigured) ;
	//bwAssert(m_isEnabled) ;
	if(p_brain != nullptr)
		p_brain->invokeStep(stepper) ;
	if(p_stage != nullptr && m_isStageDriver) {
		if(!p_stage->invokeStep(stepper))
			if(p_stage->isHalted())
				halt() ;
	}
}
bool BwActor::onStep(BwStepper& stepper) {
	if(!isHalted() && !isMigrating())
		return true ;
	else
		return false ;
}
void BwActor::doPostStep(BwStepper& stepper) {
	if(p_brain != nullptr)
		p_brain->invokePostStep(stepper) ;
	if(p_stage != nullptr && m_isStageDriver) {
		if(!p_stage->invokePostStep(stepper))
			if(p_stage->isHalted())
				halt() ;
	}
}
bool BwActor::onPostStep(BwStepper& stepper) {
	if(!isDozing() && !isHalted() && isAlive())
		return true ;
	else
		return false ;
}
bool BwActor::_doze() {
	setState(DOZING) ;
	return false ;
}
bool BwActor::doze() {
	return _doze() ;
}
void BwActor::sleep() {
	if(isSleeping())
		return ;
	disable(true) ;
}
void BwActor::wake() {
	if(!isSleeping() || isWaking())
		return ;
	enable() ;
}
void BwActor::schedule() {
	if(p_owner != nullptr) {
		BwStage *pStage = owner().getStage() ;
		if(m_isStageDriven && pStage != nullptr)
			pStage->scheduleActor(this) ;
	}
}
void BwActor::setIsAutoSleeper(bool val) {
	m_isAutoSleeper = val ;
}
