/*BikeBots - A Botworx VR reference app and AI playground
Copyright (C) 2005  Kurtis Fields. See BikeBots_License.txt for details.
*/
#ifndef _BikeBrain_H
#define _BikeBrain_H

//#include <bwvr/VrMech.h>
#include <bwvr/VrBrain.h>
#include <bwscheduling/BwTimer.h>

class VrSteering ;

namespace Bike {

class Bike ;
class BikeMech ;
class BikeEngine ;
class BikeFactory ;
class BikeWheelFactory ;
class BikeChassis ;
class BikePrimary ;

class BikeBrain : public VrBrain {
public:
	BikeBrain(Bike *pBike) ;
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
	BikeEngine* getEngine() { return p_engine ; }
	//Data Members
public:
	BikeChassis *p_chassis ;
	BikePrimary *p_primary ;
	Bike *p_bike ;
	BikeMech *p_bikeMech ;
	BikeFactory *p_bikeFactory ;
	BikeWheelFactory *p_wheelFactory ;
	//Firing
	BwLoTimer m_firingTimer ;
	BwLoTimer m_drivingTimer ;
	BwLoTimer m_steeringTimer ;
	//Steering
	VrSteering *p_steering ;
	BikeEngine *p_engine ;
	//Driving
	bwReal m_power ;
	bwReal m_powerIncrement ;
};
}//end namespace BwVr::Bots::Bike
#endif //_BikeBrain_H