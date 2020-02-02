/*BuggyBots - A Botworx VR reference app and AI playground
Copyright (C) 2005  Kurtis Fields. See BuggyBots_License.txt for details.
*/
#ifndef _MoonBuggyBrain_H
#define _MoonBuggyBrain_H

#include <bwscheduling/BwTimer.h>
#include <bwvr/VrBrain.h>

class VrSteering ;

namespace MoonBuggy {

class Buggy ;
class BuggyMech ;
class BuggyEngine ;
class BuggyFactory ;
class BuggyWheelFactory ;
class BuggyChassis ;

class BuggyBrain : public VrBrain {
public:
	BuggyBrain(Buggy *pBuggy) ;
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
	BuggyEngine* getEngine() { return p_engine ; }
	//Data Members
public:
	BuggyChassis *p_chassis ;
	Buggy *p_buggy ;
	BuggyMech *p_buggyMech ;
	BuggyFactory *p_buggyFactory ;
	BuggyWheelFactory *p_wheelFactory ;
	//Firing
	BwLoTimer m_firingTimer ;
	BwLoTimer m_drivingTimer ;
	BwLoTimer m_steeringTimer ;
	//Steering
	VrSteering *p_steering ;
	BuggyEngine *p_engine ;
	//Driving
	bwReal m_power ;
	bwReal m_powerIncrement ;
};
}//end namespace BwVr::Bots::MoonBuggy
#endif //_MoonBuggyBrain_H