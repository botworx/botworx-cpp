/*BuggyBots - A Botworx VR reference app and AI playground
Copyright (C) 2005  Kurtis Fields. See BuggyBots_License.txt for details.
*/
#include "stdafx.h"

#include <buggybots/bots/crawler/CrawlerFactory.h>
#include <buggybots/bots/crawler/Crawler.h>
#include <buggybots/bots/crawler/CrawlerChassis.h>
#include <buggybots/bots/crawler/CrawlerLeg.h>

#include <bwvr/VrVu.h>
////////////////////////////////////////////////////
namespace Crawler {
//////////////////////////
CrawlerChassis::CrawlerChassis(Crawler *pCrawler) 
	: VrBox(pCrawler), p_crawler(pCrawler) {
	vuInfo().setMeshName("VrBox.mesh") ;
}
void CrawlerChassis::doCreate(const BwPartInfo& info) {
	VrBox::doCreate(info) ;
	setSize(.75,.75,4) ;
	//bodyInfo().setDensity(p_crawler->factory().m_chassisDensity) ;
	bodyInfo().setSolidity(.000001) ;
}
void CrawlerChassis::createGeom() {
	VrBox::createGeom() ;
}
//////////////////////////
}//namespace Crawler
////////////////////////////////////////////////////
