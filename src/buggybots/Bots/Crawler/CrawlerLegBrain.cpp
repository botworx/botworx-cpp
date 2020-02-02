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
#include <bwcontrol/BwPersonality.h>
#include <bwcontrol/BwTaskGroup.h>

////////////////////////////////////////////////////
namespace Crawler {
//////////////////////////
class CrawlerLegPersonality : public BwPersonality {
public:
	CrawlerLegPersonality(CrawlerLegBrain* pBrain) : BwPersonality(pBrain) {
		m_taskGroup.setIsMutex(true) ;
	}
	virtual BwTask* produceTask(const bwString& name) ;
	//Data Members
	BwTaskGroup m_taskGroup ;
};
//////////////////////////
CrawlerLegBrain::CrawlerLegBrain(CrawlerLeg *pLeg) : VrBrain(pLeg) {
	p_leg = pLeg ;
	m_poseCmd = 0 ;
}
void CrawlerLegBrain::createPersonality() {
	p_personality = new CrawlerLegPersonality(this) ;
}
void CrawlerLegBrain::moveForward() {
	m_poseCmd = m_poseCmd + 2 ;
	if(m_poseCmd > 6)
		m_poseCmd = 0 ;
	pose(m_poseCmd) ;
}
void CrawlerLegBrain::moveReverse() {
	m_poseCmd = m_poseCmd - 2 ;
	if(m_poseCmd < 0)
		m_poseCmd = 6 ;
	pose(m_poseCmd) ;
}
void CrawlerLegBrain::pose(int poseCmd) {
	m_poseCmd = poseCmd ;
	if(poseCmd > 8)
		poseCmd = 8 - poseCmd ;
	CrawlerLegPoser* pPoser = static_cast<CrawlerLegPoser*>(p_personality->useTask("POSER")) ;
	pPoser->m_poseCmd = poseCmd ;
}
BwTask* CrawlerLegPersonality::produceTask(const bwString& name) {
	CrawlerLegBrain* pBrain = static_cast<CrawlerLegBrain*>(p_brain) ;
	BwTask *pTask = NULL ;
	if(name == "POSER") {
		pTask = new CrawlerLegPoser(pBrain) ;
		pTask->setTaskGroup(&m_taskGroup) ;
	}
	return pTask ;
}
void CrawlerLegPoser::doStep(BwStepper& stepper) {
	BwTask::doStep(stepper) ;
	switch(m_status) {
		case PLAN_START :
		case TASK_START :
			clearDependencies() ;
			poseSegs(m_poseCmd) ;
			setStatus(TASK_BUSY) ;
			break ;
		case TASK_BUSY : 
			if(testDependencies(TASK_SUCCESS))
				setStatus(TASK_SUCCESS) ;
			break ;
		case TASK_SUCCESS :
			setStatus(PLAN_START) ;
	}
}
void CrawlerLegPoser::poseSegs(int poseCmd) {

	CrawlerLegMotorBrain *pLegMotorBrain1 = 
		static_cast<CrawlerLegMotorBrain*>(p_leg->p_legSegs[0]->brain().p_mech_1) ;
	CrawlerLegMotorBrain *pLegMotorBrain2 = 
		static_cast<CrawlerLegMotorBrain*>(p_leg->p_legSegs[0]->brain().p_mech_2) ;
	CrawlerLegMotorBrain *pLegMotorBrain3 = 
		static_cast<CrawlerLegMotorBrain*>(p_leg->p_legSegs[1]->brain().p_mech_1) ;

	CrawlerLegMotorPoser *pPoser1 = 
		static_cast<CrawlerLegMotorPoser*>
		(pLegMotorBrain1->getPersonality()->useTask("POSER")) ;
	CrawlerLegMotorPoser *pPoser2 = 
		static_cast<CrawlerLegMotorPoser*>
		(pLegMotorBrain2->getPersonality()->useTask("POSER")) ;
	CrawlerLegMotorPoser *pPoser3 = 
		static_cast<CrawlerLegMotorPoser*>
		(pLegMotorBrain3->getPersonality()->useTask("POSER")) ;

	switch(poseCmd) {
		case 0 :
			pPoser1->config(-bwRealTraits::PiDiv6) ;
			pPoser2->config(bwRealTraits::PiDiv6) ;
			pPoser3->config(bwRealTraits::PiDiv2 - bwRealTraits::PiDiv6) ;
			break ;
		case 2 :
			pPoser1->config(-bwRealTraits::PiDiv6) ;
			pPoser2->config(-bwRealTraits::PiDiv6) ;
			pPoser3->config(bwRealTraits::PiDiv2 - bwRealTraits::PiDiv6) ;
			break ;
		case 4 :
			pPoser1->config(bwRealTraits::PiDiv4) ;
			pPoser2->config(-bwRealTraits::PiDiv6) ;
			pPoser3->config(bwRealTraits::PiDiv4) ;
			break ;
		case 6 :
			pPoser1->config(bwRealTraits::PiDiv4) ;
			pPoser2->config(bwRealTraits::PiDiv6) ;
			pPoser3->config(bwRealTraits::PiDiv4) ;
			break ;
	}
}
//////////////////////////
}//namespace Crawler
////////////////////////////////////////////////////
