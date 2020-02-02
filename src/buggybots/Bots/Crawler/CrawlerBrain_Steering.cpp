/*BuggyBots - A Botworx VR reference app and AI playground
Copyright (C) 2005  Kurtis Fields. See BuggyBots_License.txt for details.
*/
#include "stdafx.h"

#include <buggybots/bots/crawler/CrawlerBrain.h>
#include <buggybots/bots/crawler/Crawler.h>
#include <buggybots/bots/crawler/CrawlerFactory.h>

#include <bwvr/VrSteering.h>
////////////////////////////////////////////////////
namespace Crawler {
//////////////////////////
void CrawlerBrain::turnLeft() {
	if(!m_steeringTimer.checkAlarm()) {
		return ;
	}
	m_steeringTimer.resetAlarm() ;
	p_steering->turnLeft() ;
}
 
void CrawlerBrain::turnRight() {
		if(!m_steeringTimer.checkAlarm()) {
		return ;
	}
	m_steeringTimer.resetAlarm() ;
	p_steering->turnRight() ;
}
void CrawlerBrain::turnNone() {
		if(!m_steeringTimer.checkAlarm()) {
		return ;
	}
	m_steeringTimer.resetAlarm() ;
	p_steering->turnNone() ;
}
//////////////////////////
}//namespace Crawler
////////////////////////////////////////////////////
