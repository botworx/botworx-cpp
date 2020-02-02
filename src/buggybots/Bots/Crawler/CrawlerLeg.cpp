/*BuggyBots - A Botworx VR reference app and AI playground
Copyright (C) 2005  Kurtis Fields. See BuggyBots_License.txt for details.
*/
#include "stdafx.h"

#include <buggybots/bots/crawler/Crawler.h>
#include <buggybots/bots/crawler/CrawlerBrain.h>
#include <buggybots/bots/crawler/CrawlerChassis.h>
#include <buggybots/bots/crawler/CrawlerLeg.h>
#include <buggybots/bots/crawler/CrawlerLegSeg.h>
#include <buggybots/bots/crawler/CrawlerLegMotor.h>

////////////////////////////////////////////////////
namespace Crawler {
//////////////////////////
CrawlerLeg::CrawlerLeg(int indice, Crawler *pCrawler) 
	: VrDynamicAssembly(pCrawler) {
	m_indice = indice ;
	p_crawler = pCrawler ;	
}
void CrawlerLeg::doCreate(const BwPartInfo& info) {
	VrDynamicAssembly::doCreate(info) ;
	createSegs() ;
}
void CrawlerLeg::createBrain() {
	p_brain = new CrawlerLegBrain(this) ;
	p_brain->create() ;
}
void CrawlerLeg::createSegs() {
	CrawlerLegSeg *pSeg = NULL ;
	VrModel *pLeader = NULL ;

	VrModel *pChassis = p_crawler->getMain() ;
	for(int i = 0 ; i < SEG_TTL ; ++i) {
		switch(i) {
			case 0 :
				pSeg = CrawlerLegSeg1Factory::singleton::get().createLegSeg(this, m_indice) ;
				break ;
			case 1 :
				pSeg = CrawlerLegSeg2Factory::singleton::get().createLegSeg(this, m_indice) ;
				break ;
		}
		p_legSegs[i] = pSeg ;

		if(pLeader == NULL)
			pLeader = pChassis ;
		else
			pLeader = p_legSegs[i-1] ;

		pSeg->attachTo(pLeader) ;
	}
}
VrModel* CrawlerLegFactory::rent(int indice, VrGroup *pGroup) {
	CrawlerLeg *pLeg = new CrawlerLeg(indice, static_cast<Crawler*>(pGroup)) ;
	pLeg->setFactory(this) ;
	pLeg->create() ;
	return pLeg ;
}

} //namespace Crawler

//TODO:?:weird ... can't be done within namespace ...???
using namespace Crawler ;
//Singleton support
template<> CrawlerLegFactory::singleton::pointer CrawlerLegFactory::singleton::g_singleton = 0 ;
//
CrawlerLegFactory* CrawlerLegFactory::singleton_alloc::alloc() { 
	CrawlerLegFactory* pPart = new CrawlerLegFactory(NULL) ;
	pPart->create() ;
	return pPart ;
}

