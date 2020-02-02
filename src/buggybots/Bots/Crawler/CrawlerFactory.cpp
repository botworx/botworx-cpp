/*BuggyBots - A Botworx VR reference app and AI playground
Copyright (C) 2005  Kurtis Fields. See BuggyBots_License.txt for details.
*/
#include "stdafx.h"

#include <buggybots/bots/crawler/CrawlerFactory.h>
#include <buggybots/bots/crawler/Crawler.h>
////////////////////////////////////////////////////
namespace Crawler {
//////////////////////////
CrawlerFactory::CrawlerFactory(BwKit *pKit) : VrModelFactory(pKit) {
	setName("Crawler") ;
	m_chassisDensity = .5 ;
	m_chassisPos[0] = 0 ;
	m_chassisPos[1] = 0 ;
	m_chassisPos[2] = 0 ;
}
VrModel* CrawlerFactory::produce(VrGroup *pGroup, bwPartStyle style) {
	Crawler* pCrawler = new Crawler(pGroup) ;
	pCrawler->setFactory(this) ;
	pCrawler->create(style) ;
	return pCrawler ;
}
Crawler* CrawlerFactory::rentCrawler(VrGroup *pGroup) {
	return static_cast<Crawler*>(produce(pGroup)) ;
}

} //namespace Crawler

//TODO:?:weird ... can't be done within namespace ...???
using namespace Crawler ;
//Singleton support
template<> CrawlerFactory::singleton::pointer CrawlerFactory::singleton::g_singleton = 0 ;
//
CrawlerFactory* CrawlerFactory::singleton_alloc::alloc() { 
	CrawlerFactory* pPart = new CrawlerFactory(NULL) ;
	pPart->create() ;
	return pPart ;
}

