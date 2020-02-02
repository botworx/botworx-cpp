/*JrBots - A Botworx VR reference app and AI playground
Copyright (C) 2005  Kurtis Fields. See JrBots_License.txt for details.
*/
#ifndef _JrWheel_H
#define _JrWheel_H

#include <bwvr/VrBall.h>
class VrRod ;

#include <bwvr/VrHinge2.h>
#include <bwvr/VrMech.h>
#include "JrBrain.h"
namespace Jr {

class JrWheelFactory ;
class JrBody ;
class JrWheel ;

class JrWheelMech : public VrJointMech {
public:
	JrWheelMech(JrWheel *pWheel) ;

	virtual void doCreate(const BwPartInfo& info) ;
	virtual void doConfig() ;
	virtual void doPostConfig() ;
	virtual void doPostEnable(bool sleeping = false) ;
	void setWheelPosition() ;
	JrBrain& master() { return *static_cast<JrBrain*>(p_master) ; }
	//
	JrEngine* getEngine() { return p_engine ; }
	//Driving
	virtual void moveForward() ;
	virtual void moveReverse() ;
	virtual void moveNone() ;
	double getPower() { return m_power ; }
	//Steering
	virtual void turnLeft() ;
	virtual void turnRight() ;
	virtual void turnNone() ;
	//Data Members
	JrWheel *p_wheel ;
	VrModel *p_chassis ;
	JrEngine *p_engine ;
	//Driving
	bwReal m_power ;
	bwReal m_powerIncrement ;
	//Steering
	bwReal m_turnPower ;
	bwReal m_turnPowerIncrement ;
} ;

class JrWheel : public VrBall {
public:
	JrWheel(int indice, Jr *pJr) ;
	virtual void doCreate(const BwPartInfo& info) ;
	JrWheelFactory& factory() { return *static_cast<JrWheelFactory*>(p_factory) ; }
	JrWheelMech& brain() { return *static_cast<JrWheelMech*>(p_brain) ; }
	virtual bwString getClassName() { return "Wheel" ; }
	virtual void createBrain() ;
	/*Data Members*/
	Jr *p_jr ;
private:
} ;
}//end namespace BwVr::Bots::Jr
#endif //_JrWheel_H
