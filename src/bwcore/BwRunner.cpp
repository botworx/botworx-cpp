/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <bwcore/BwRunner.h>
#include <bwcore/BwStage.h>
#include <bwapplet/BwApplet.h>

#include <bwscheduling/BwTimer.h>

BwRunner::BwRunner(BwRunner* pOwner) : BwActor(pOwner) {

	p_stage = &m_stage ;
	m_stage.setOwner(this) ;
	m_stage.create() ;

	m_runnerType = RUNNER_SIMPLE ;
	m_isRunning = false ;
	m_isFinished = false ;
	//
	p_thread = nullptr ;
}
BwRunner::~BwRunner() {
	delete p_thread ;
}
void BwRunner::stop() {
	m_isRunning = false ;
	onStop() ;
}
void BwRunner::go() {
	onGo() ;
	m_isRunning = true ;

	switch(m_runnerType) {
		case RUNNER_SIMPLE :
			goSimple() ;
			break ;
		case RUNNER_SYNC :
			goSync() ;
			break ;
		case RUNNER_ASYNC :
			goAsync() ;
			break ;
	}
}
void BwRunner::goSimple() {
	if(m_isFirstGo == true) {
		m_isFirstGo = false ;
	}
	run() ;
}
void BwRunner::goSync() {
	if(m_isFirstGo == true) {
		m_isFirstGo = false ;
		p_thread = 	new boost::thread(thread_fn(this)) ;
	}
}
void BwRunner::goAsync() {
	if(m_isFirstGo == true) {
		m_isFirstGo = false ;
		p_thread = 	new boost::thread(thread_fn(this)) ;
	}
}
void BwRunner::run() {
	while (m_isRunning == true && !isFinished())
	{
		doStep() ;
		doPostStep() ;
	}
}
void BwRunner::doStep(BwStepper& stepper) {
		switch(m_runnerType) {
			case RUNNER_SIMPLE :
				stepSimple() ;
				break ;
			case RUNNER_SYNC :
				stepSync() ;
				break ;
			case RUNNER_ASYNC :
				stepAsync() ;
				break ;
		}
}
void BwRunner::stepSimple() {
	doStep() ;
}
void BwRunner::stepAsync() {
	doStep();
	//m_stepBegin.wait(m_stepBeginLock) ;
}
void BwRunner::stepSync() {
	//m_stepBegin.wait(m_stepBeginLock);
	doStep();
	//m_stepEnd.notify_all() ;
}
//
/*void BwRunner::signalStep() {
	m_stepEnd.notify_all();
	m_stepBegin.notify_all() ;
	if(!m_isCoRunner)
		m_stepEnd.wait(m_stepEndLock);
	else
		doStep() ;
}*/
void BwRunner::doStep() {
	m_time = m_stepTimer.getRealTime() ;
	m_elapsedTime = m_stepTimer.getRealElapsed() ;
	m_stepper.setCurrentTime(m_time) ;
	m_stepper.setDeltaTime(m_elapsedTime) ;

	BwActor::doStep(m_stepper) ;
}
void BwRunner::doPostStep() {
	m_stepper.setCurrentTime(m_time) ;
	m_stepper.setDeltaTime(m_elapsedTime) ;
	BwActor::doPostStep(m_stepper) ;
}
