/*JrBots - A Botworx VR reference app and AI playground
Copyright (C) 2005  Kurtis Fields. See JrBots_License.txt for details.
*/
#ifndef _JrBrain_H
#define _JrBrain_H

#include <bwscheduling/BwTimer.h>
//#include <bwvr/VrMech.h>
#include <bwvr/VrBrain.h>
#include "Jr.h"

class VrSteering ;

namespace Jr {

class Jr ;
class JrEngine ;
class JrFactory ;
class JrWheelFactory ;
class JrChassis ;
class JrWheelMech ;

class JrBrain : public VrBrain {
public:
	JrBrain(Jr *pJr) ;
	virtual void doCreate(const BwPartInfo& info) ;
	virtual void moveForward() ;
	virtual void moveReverse() ;
	virtual void moveNone() ;
	//Steering
	virtual void turnLeft() ;
	virtual void turnRight() ;
	virtual void turnNone() ;
	//Driving
	double getPower() { return m_power ; }
	//Rolling
	virtual void rollLeft() ;
	virtual void rollRight() ;

	virtual void fireMissile() ;
	virtual void fireLaser() ;
	//
	VrSteering* getSteering() { return p_steering ; }
	//Data Members
public:
	JrChassis *p_chassis ;
	Jr *p_jr ;
	JrFactory *p_jrFactory ;
	JrWheelFactory *p_wheelFactory ;
	//Firing
	BwLoTimer m_firingTimer ;
	BwLoTimer m_drivingTimer ;
	BwLoTimer m_steeringTimer ;
	//Steering
	VrSteering *p_steering ;
	//Driving
	bwReal m_power ;
	bwReal m_powerIncrement ;
	//
	JrWheelMech *p_wheelMech[Jr::WHEEL_TTL] ;
};
}//end namespace BwVr::Bots::Jr
#endif //_JrBrain_H