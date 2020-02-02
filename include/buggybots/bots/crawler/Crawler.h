/*BuggyBots - A Botworx VR reference app and AI playground
Copyright (C) 2005  Kurtis Fields. See BuggyBots_License.txt for details.
*/
#ifndef _Crawler_H
#define _Crawler_H

#include <bwvr/VrDynamicAssembly.h>
#include "CrawlerFactory.h"

class VrSteering ;
////////////////////////////////////////////////////
namespace Crawler {
//////////////////////////
enum {
		LEG_RL = 0,
		LEG_RR,
		LEG_FL,
		LEG_FR,
		LEG_TTL
} ;

class CrawlerBrain ;
class CrawlerChassis ;
class CrawlerLeg ;
class CrawlerLegSeg ;
class CrawlerEye ;

class Crawler : public VrDynamicAssembly
{
public:
	Crawler(VrGroup *pGroup) ;
	virtual void doCreate(const BwPartInfo& info) ;
	virtual bool onCreate(const BwPartInfo& info) ;
	virtual void createBrain() ;
	virtual ~Crawler();

	virtual bwString getClassName() { return "Crawler" ; }
	CrawlerFactory& factory() { return *static_cast<CrawlerFactory*>(p_factory) ; }
	VrSteering* getSteering() { return p_steering ; }
	virtual void fireMissile() ;

	CrawlerLeg *p_leg[LEG_TTL] ;
public:
	void rollLeft(bwReal degree) ;
	void rollRight(bwReal degree) ;

	void flip(bwReal fx, bwReal fy, bwReal fz, bwReal px, bwReal py, bwReal pz) ;

	virtual void setPos(const bwPoint3& p);
	void setLegPosition(CrawlerLegSeg *pLeg) ;

	VrSteering *p_steering ;
};
//////////////////////////
}//namespace Crawler
////////////////////////////////////////////////////
#endif