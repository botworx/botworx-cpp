/*BuggyBots - A Botworx VR reference app and AI playground
Copyright (C) 2005  Kurtis Fields. See BuggyBots_License.txt for details.
*/
#include "stdafx.h"

#include <buggybots/bots/crawler/Crawler.h>
#include <buggybots/bots/crawler/CrawlerLegMotor.h>
#include <buggybots/bots/crawler/CrawlerLeg.h>
////////////////////////////////////////////////////
namespace Crawler {
//////////////////////////
CrawlerLegMotor::CrawlerLegMotor(BwPart *pOwner) : VrMotor(pOwner, NULL, 1) {
}
void CrawlerLegMotor::setPower(bwReal power) {
	m_power = power ;
	setVelocity(m_power) ;
	setForceMax(10) ;
}
//////////////////////////
}//namespace Crawler
////////////////////////////////////////////////////
