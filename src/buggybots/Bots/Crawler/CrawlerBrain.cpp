/*BuggyBots - A Botworx VR reference app and AI playground
Copyright (C) 2005  Kurtis Fields. See BuggyBots_License.txt for details.
*/
#include "stdafx.h"

#include <buggybots/bots/crawler/CrawlerBrain.h>
#include <buggybots/bots/crawler/Crawler.h>
#include <buggybots/bots/crawler/CrawlerFactory.h>
#include <buggybots/bots/crawler/CrawlerLeg.h>
#include <buggybots/bots/crawler/CrawlerLegSeg.h>
//
#include <bwcontrol/BwPersonality.h>
#include <bwcontrol/BwTaskGroup.h>
////////////////////////////////////////////////////
namespace Crawler {
//////////////////////////
class CrawlerPersonality : public BwPersonality {
public:
	CrawlerPersonality(CrawlerBrain* pBrain) : BwPersonality(pBrain) {
		m_taskGroup.setIsMutex(true) ;
	}
	virtual BwTask* produceTask(const bwString& name) ;
	//Data Members
	BwTaskGroup m_taskGroup ;
};
//////////////////////////
CrawlerBrain::CrawlerBrain(Crawler *pCrawler) 
	: VrBrain(pCrawler),
		m_firingTimer(std::chrono::seconds(1)),
		m_steeringTimer(std::chrono::milliseconds(16)),
		m_drivingTimer(std::chrono::seconds(1)) {
	p_crawler = pCrawler ;
	p_crawlerFactory = CrawlerFactory::singleton::getPtr() ;
	p_steering = p_crawler->getSteering() ;
	p_legFactory = CrawlerLegFactory::singleton::getPtr() ;
}
void CrawlerBrain::createPersonality() {
	p_personality = new CrawlerPersonality(this) ;
}
void CrawlerBrain::doPostEnable(bool sleeping) {
	p_personality->useTask("DRIVER") ;
	getLegBrain(LEG_RL)->pose(6) ;
	getLegBrain(LEG_RR)->pose(2) ;
	getLegBrain(LEG_FL)->pose(0) ;
	getLegBrain(LEG_FR)->pose(4) ;
}
void CrawlerBrain::fireMissile() {
	if(m_firingTimer.checkAlarm()) {
		p_crawler->fireMissile() ;
		m_firingTimer.resetAlarm() ;
	}
}
void CrawlerBrain::rollLeft() {
	p_crawler->rollLeft(bwRealTraits::PiDiv180) ;
}
void CrawlerBrain::rollRight() {
	p_crawler->rollRight(bwRealTraits::PiDiv180) ;
}
BwTask* CrawlerPersonality::produceTask(const bwString& name) {
	CrawlerBrain* pBrain = static_cast<CrawlerBrain*>(p_brain) ;
	BwTask *pTask = NULL ;
	if(name == "DRIVER") {
		pTask = new CrawlerDriver(pBrain) ;
		pTask->setTaskGroup(&m_taskGroup) ;
	}
	return pTask ;
}
VrBrain* CrawlerBrain::getLegBrain(int index) {
	return static_cast<VrBrain*>(p_crawler->p_leg[index]->getBrain()) ;
}
//////////////////////////
}//namespace Crawler
////////////////////////////////////////////////////
