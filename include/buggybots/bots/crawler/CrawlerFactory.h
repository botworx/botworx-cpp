/*BuggyBots - A Botworx VR reference app and AI playground
Copyright (C) 2005  Kurtis Fields. See BuggyBots_License.txt for details.
*/
#ifndef _CrawlerFactory_H
#define _CrawlerFactory_H

#include <bwvr/VrModelFactory.h>

class VrGroup ;
////////////////////////////////////////////////////
namespace Crawler {
//////////////////////////
class Crawler ;
//
//CrawlerFactory
//
class CrawlerFactory : public VrModelFactory {
public:
	CrawlerFactory(BwKit *pKit) ;
	virtual VrModel* produce(VrGroup *pGroup, bwPartStyle style = PS_DEFAULT) ;
	Crawler* rentCrawler(VrGroup *pGroup) ;
	//
	bwVector3 m_chassisPos ;
	bwReal m_chassisDensity ;
	//Singleton support
public:
	struct singleton_alloc {
		static CrawlerFactory* alloc() ;
	} ;
	typedef BwAutoSingletonT<CrawlerFactory, singleton_alloc> singleton ;
	singleton m_singleton ;
} ;

}//namespace Crawler

#endif //_CrawlerFactory_H
