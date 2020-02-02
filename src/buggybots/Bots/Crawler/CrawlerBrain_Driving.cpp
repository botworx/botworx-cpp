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

////////////////////////////////////////////////////
namespace Crawler {
//////////////////////////
void CrawlerBrain::moveForward() {
	if(!m_drivingTimer.checkAlarm()) {
		return ;
	}
	m_drivingTimer.resetAlarm() ;

	for(int i = 0 ; i < 4 ; ++i) {
		VrBrain *pBrain = static_cast<VrBrain*>(p_crawler->p_leg[i]->getBrain()) ;
		pBrain->moveForward() ;
	}
}
void CrawlerBrain::moveReverse() {
	if(!m_drivingTimer.checkAlarm()) {
		return ;
	}
	m_drivingTimer.resetAlarm() ;
}
void CrawlerBrain::moveNone() {
	if(!m_drivingTimer.checkAlarm()) {
		return ;
	}
	m_drivingTimer.resetAlarm() ;
	for(int i = 0 ; i < 4 ; ++i) {
		for(int j = 0 ; j < 3 ; ++j) {
			VrBrain *pBrain = static_cast<VrBrain*>(p_crawler->p_leg[i]->p_legSegs[j]->getBrain()) ;
			pBrain->moveNone() ;
		}
	}
}
void CrawlerBrain::pose(int poseCmd) {
	switch(poseCmd) {
		case 0 : 
			getLegBrain(LEG_RL)->pose(6) ;
			getLegBrain(LEG_RR)->pose(2) ;
			getLegBrain(LEG_FL)->pose(0) ;
			getLegBrain(LEG_FR)->pose(4) ;
			break ;
		case 2 :
			getLegBrain(LEG_RL)->pose(0) ;
			getLegBrain(LEG_RR)->pose(2) ;
			getLegBrain(LEG_FL)->pose(4) ;
			getLegBrain(LEG_FR)->pose(2) ;
			break ;
		case 4 : 
			getLegBrain(LEG_RL)->pose(2) ;
			getLegBrain(LEG_RR)->pose(6) ;
			getLegBrain(LEG_FL)->pose(2) ;
			getLegBrain(LEG_FR)->pose(4) ;
			break ;
		case 6 : 
			getLegBrain(LEG_RL)->pose(2) ;
			getLegBrain(LEG_RR)->pose(0) ;
			getLegBrain(LEG_FL)->pose(0) ;
			getLegBrain(LEG_FR)->pose(2) ;
			break ;
		case 8 : 
			getLegBrain(LEG_RL)->pose(0) ;
			getLegBrain(LEG_RR)->pose(0) ;
			getLegBrain(LEG_FL)->pose(2) ;
			getLegBrain(LEG_FR)->pose(2) ;
			break ;
		case 9 : 
			getLegBrain(LEG_RL)->pose(6) ;
			getLegBrain(LEG_RR)->pose(6) ;
			getLegBrain(LEG_FL)->pose(4) ;
			getLegBrain(LEG_FR)->pose(4) ;
			break ;
	}
}
//////////////////////////
}//namespace Crawler
////////////////////////////////////////////////////
