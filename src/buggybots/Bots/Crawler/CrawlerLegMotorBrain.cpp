/*BuggyBots - A Botworx VR reference app and AI playground
Copyright (C) 2005  Kurtis Fields. See BuggyBots_License.txt for details.
*/
#include "stdafx.h"

#include <buggybots/bots/crawler/CrawlerBrain.h>
#include <buggybots/bots/crawler/Crawler.h>
#include <buggybots/bots/crawler/CrawlerChassis.h>
#include <buggybots/bots/crawler/CrawlerFactory.h>
#include <buggybots/bots/crawler/CrawlerLegMotor.h>
#include <buggybots/bots/crawler/CrawlerLeg.h>
#include <buggybots/bots/crawler/CrawlerLegSeg.h>
//
#include <bwvr/VrPhysics.h>
#include <bwvr/VrSteering.h>
#include <bwvr/VrBody.h>
//
#include <bwcontrol/BwPersonality.h>
#include <bwcontrol/BwTaskGroup.h>
////////////////////////////////////////////////////
namespace Crawler {
class CrawlerLegMotorPersonality : public BwPersonality {
public:
	CrawlerLegMotorPersonality(CrawlerLegMotorBrain* pBrain) : BwPersonality(pBrain) {
		m_taskGroup.setIsMutex(true) ;
	}
	virtual BwTask* produceTask(const bwString& name) ;
	//Data Members
	BwTaskGroup m_taskGroup ;
};

//////////////////////////
CrawlerLegMotorBrain::CrawlerLegMotorBrain(CrawlerLegSegMech *pOwner) : VrMotorMech(pOwner) {
	m_power = 0 ;
}
void CrawlerLegMotorBrain::createPersonality() {
	p_personality = new CrawlerLegMotorPersonality(this) ;
}
BwTask* CrawlerLegMotorPersonality::produceTask(const bwString& name) {
	CrawlerLegMotorBrain* pBrain = static_cast<CrawlerLegMotorBrain*>(p_brain) ;
	BwTask *pTask = NULL ;

	if(name == "POSER") {
		pTask = new CrawlerLegMotorPoser(pBrain) ;
		pTask->setTaskGroup(&m_taskGroup) ;
	}
	return pTask ;
}
void CrawlerLegMotorBrain::moveForward() {
	p_motor->setPower(m_power) ;
}
void CrawlerLegMotorBrain::moveReverse() {
	p_motor->setPower(-m_power) ;
}
void CrawlerLegMotorBrain::moveNone() {
	m_power = 0 ;
}
void CrawlerLegMotorPoser::doStep(BwStepper& stepper) {
	BwTask::doStep(stepper) ;
	bwDT invDt = VrPhysics::singleton::get().getInvDt() ;
	switch(m_status) {
		case PLAN_START :
		case TASK_START :
			setStatus(TASK_BUSY) ;
			break ;
		case TASK_BUSY : 
			break ;
		case TASK_SUCCESS :
			setStatus(PLAN_START) ;
	}
	//TODO:can't this be simplified to p_motor->getAngle()?
	bwReal rodAngle = p_motor->getRod()->getAngle() ; 
	//bwReal mass1 = p_legSeg->getJoint()->getModel1()->getBody()->getMass()->mass ;
	//bwReal mass2 = p_legSeg->getJoint()->getModel2()->getBody()->getMass()->mass ;
	//bwReal mass = mass1 + mass2 ;
	bwReal difference = 0 ;
	bwReal powerScale = .1f ;
	//bwReal powerScale = 1 ;

	//if(rodAngle >= ( m_angle - bwRealTraits::PiDiv6) && rodAngle <= ( m_angle + bwRealTraits::PiDiv6)) {
	//	setStatus(TASK_SUCCESS) ;
	//else
	//	setStatus(TASK_BUSY) ;
	//if(rodAngle >= ( m_angle - makeRadian(15) ) && rodAngle <= ( m_angle + makeRadian(15))) {
	//	setStatus(TASK_SUCCESS) ;
	//else {
	//	setStatus(TASK_BUSY) ;
	setStatus(TASK_SUCCESS) ;

	if(rodAngle > m_angle) {
		difference = rodAngle - m_angle ;
		m_power = m_power + (difference * powerScale * invDt) ;

		brain().m_power = m_power ;
		brain().moveReverse() ;
	}
	else {
		difference = m_angle - rodAngle ;
		m_power = m_power + (difference * powerScale * invDt) ;

		brain().m_power = m_power ;
		brain().moveForward() ;
	}
}
//////////////////////////
}//namespace Crawler
////////////////////////////////////////////////////