#ifndef _CrawlerLegMotor_H
#define _CrawlerLegMotor_H

#include <bwscheduling/BwTimer.h>
#include <bwvr/VrMech.h>
#include <bwvr/VrMotor.h>
////////////////////////////////////////////////////
namespace Crawler {
//////////////////////////
/*class CrawlerLegMech: public VrMech {
public:
	CrawlerLegMech(CrawlerLegSeg *pLegSeg) ;
	CrawlerLegSeg *p_legSeg ;
};*/
//////////////////////////
class CrawlerLegMotor : public VrMotor {
public:
	CrawlerLegMotor(BwPart *pOwner) ;
	void setPower(bwReal power) ;
};
/////////////
class CrawlerLegSegMech ;

class CrawlerLegMotorBrain : public VrMotorMech {
public:
	CrawlerLegMotorBrain(CrawlerLegSegMech *pOwner) ;
	virtual void createPersonality() ;
	virtual void moveForward() ;
	virtual void moveReverse() ;
	virtual void moveNone() ;
	/*Data Members*/
public:
	BwLoTimer m_drivingTimer ;
	bwReal m_power ;
};
//////////////
class CrawlerLegMotorPoser : public BwTask {
public:
	CrawlerLegMotorPoser(CrawlerLegMotorBrain *pBrain) : BwTask(pBrain) {
		//m_vpID = (taskID)CrawlerLegMotorBrain::VP_POSER ;
		m_name = "POSER" ;
		p_motor = pBrain->getMotor() ;
	}
	//TODO:note:since tasks are reusable config should reset any pertinent variables!!!
	void config(bwReal angle) {
		m_angle = angle ;
		m_power = 1 ;
		//TODO:tasks should be monitored not the brains?
		//p_brain->m_isBusy = true ;
		setStatus(TASK_BUSY) ;
	}
	//virtual bool doStep(BwStepper& stepper) ;
	virtual void doStep(BwStepper& stepper) ;
	CrawlerLegMotorBrain& brain() { return *static_cast<CrawlerLegMotorBrain*>(p_brain) ; }
	//Data
public:
	VrMotor *p_motor ;
	bwReal m_angle ; //angle to hold to
	bwReal m_power ; //power / torque to apply
};

//////////////////////////
}//namespace Crawler
////////////////////////////////////////////////////

#endif //_CrawlerLegMotor_H
