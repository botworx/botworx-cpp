/*BuggyBots - A Botworx VR reference app and AI playground
Copyright (C) 2005  Kurtis Fields. See BuggyBots_License.txt for details.
*/
#ifndef _CrawlerLeg_H
#define _CrawlerLeg_H

#include <bwvr/VrDynamicAssembly.h>
#include <bwvr/VrModelFactory.h>
#include <bwvr/VrHinge.h>

class VrRod ;

////////////////////////////////////////////////////
namespace Crawler {
//////////////////////////
class CrawlerChassis ;
class CrawlerLegMotor ;

class CrawlerLeg ;
//
//CrawlerLegFactory
//
class CrawlerLegFactory : public VrModelFactory {
public:
	CrawlerLegFactory(BwKit *pKit) : VrModelFactory(pKit) {
		setName("Crawler::CrawlerLeg") ;
	}
	virtual VrModel* rent(int indice, VrGroup *pGroup) ;
	//Singleton support
public:
	struct singleton_alloc {
		static CrawlerLegFactory* alloc() ;
	} ;
	typedef BwAutoSingletonT<CrawlerLegFactory, singleton_alloc> singleton ;
	singleton m_singleton ;
};
//
//CrawlerLeg
//
class CrawlerLeg : public VrDynamicAssembly {
public:
	CrawlerLeg(int indice, Crawler *pCrawler) ;
	virtual void doCreate(const BwPartInfo& info) ;
	virtual void createBrain() ;
	void createSegs() ;
	//Data
	const static int SEG_TTL = 2 ;
	const static int MOTOR_TTL = 3 ;
	Crawler *p_crawler ;
	CrawlerLegSeg *p_legSegs[SEG_TTL] ;
	CrawlerLegMotor *p_motors[MOTOR_TTL] ;
	//
};
//
//CrawlerLegPose
//
class CrawlerLegPose {
public:
	void setAngle(int index, bwReal angle) { m_angles[index] = angle ; }
	bwReal m_angles[CrawlerLeg::SEG_TTL] ;
} ;
//////////////////////////
}//namespace Crawler
////////////////////////////////////////////////////
#endif //_CrawlerLeg_H