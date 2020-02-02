/*BuggyBots - A Botworx VR reference app and AI playground
Copyright (C) 2005  Kurtis Fields. See BuggyBots_License.txt for details.
*/
#ifndef _CrawlerChassis_H
#define _CrawlerChassis_H

#include <bwvr/VrBox.h>

////////////////////////////////////////////////////
namespace Crawler {
//////////////////////////
class CrawlerFactory ;

class CrawlerChassis : public VrBox {
public:
	CrawlerChassis(Crawler* pCrawler) ;
	virtual void doCreate(const BwPartInfo& info) ;
	virtual bwString getClassName() { return "Chassis" ; }
	virtual void createGeom() ;
	/*Data Members*/
	Crawler* p_crawler ;
} ;
//////////////////////////
}//namespace Crawler
////////////////////////////////////////////////////
#endif //_CrawlerChassis_H
