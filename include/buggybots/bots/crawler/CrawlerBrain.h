/*BuggyBots - A Botworx VR reference app and AI playground
Copyright (C) 2005  Kurtis Fields. See BuggyBots_License.txt for details.
*/
#ifndef _CrawlerBrain_H
#define _CrawlerBrain_H

#include <bwscheduling/BwTimer.h>
//#include <bwcontrol/BwBrain.h>
#include <bwvr/VrBrain.h>

class VrSteering ;

////////////////////////////////////////////////////
namespace Crawler {
//////////////////////////
class Crawler ;
class CrawlerFactory ;
class CrawlerLegFactory ;

//class CrawlerBrain : public BwBrain {
class CrawlerBrain : public VrBrain {
public:
	CrawlerBrain(Crawler *pCrawler) ;
	virtual void doPostEnable(bool sleeping = false) ;
	virtual void createPersonality() ;
	//Steering
	virtual void turnLeft() ;
	virtual void turnRight() ;
	virtual void turnNone() ;
	//Driving
	virtual void moveForward() ;
	virtual void moveReverse() ;
	virtual void moveNone() ;
	virtual void pose(int poseCmd) ;
	//Rolling
	virtual void rollLeft() ;
	virtual void rollRight() ;
	//??
	virtual void fireMissile() ;
	//
	VrBrain* getLegBrain(int index) ;
	/*Data Members*/
public:
	Crawler *p_crawler ;
	CrawlerFactory *p_crawlerFactory ;
	CrawlerLegFactory *p_legFactory ;
	//Firing
	BwLoTimer m_firingTimer ;
	BwLoTimer m_steeringTimer ;
	//Steering
	VrSteering *p_steering ;
	//Driving
	BwLoTimer m_drivingTimer ;
};
class CrawlerDriver : public BwTask {
public:
	CrawlerDriver(CrawlerBrain *pBrain) : BwTask(pBrain) {
		m_name = "DRIVER" ;
		p_crawler = pBrain->p_crawler ;
	}
	//virtual bool doStep(BwStepper& stepper) ;
	virtual void doStep(BwStepper& stepper) ;
	CrawlerBrain& brain() { return *static_cast<CrawlerBrain*>(p_brain) ; }
	//Data
public:
	Crawler *p_crawler ;
};
//
class CrawlerLegSeg ;
class CrawlerLeg ;
class CrawlerLegMotor ;

//class CrawlerLegBrain : public BwBrain {
class CrawlerLegBrain : public VrBrain {
public:
	CrawlerLegBrain(CrawlerLeg *pLeg) ;
	virtual void createPersonality() ;
	virtual void moveForward() ;
	virtual void moveReverse() ;
	virtual void pose(int poseCmd) ;
	//Driving
	/*Data Members*/
public:
	CrawlerLeg *p_leg ;
	int m_poseCmd ;
};
//
class CrawlerLegPoser : public BwTask {
public:
	CrawlerLegPoser(CrawlerLegBrain *pBrain) : BwTask(pBrain) {
		m_name = "POSER" ;
		p_leg = pBrain->p_leg ;
	}
	//virtual bool doStep(BwStepper& stepper) ;
	virtual void doStep(BwStepper& stepper) ;
	void poseSegs(int poseCmd) ;
	//Data
public:
	CrawlerLeg *p_leg ;
	int m_poseCmd ;
};
//////////////////////////
}//namespace Crawler
////////////////////////////////////////////////////
#endif //_CrawlerBrain_H
