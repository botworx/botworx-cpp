/*BuggyBots - A Botworx VR reference app and AI playground
Copyright (C) 2005  Kurtis Fields. See BuggyBots_License.txt for details.
*/
#ifndef _MoonBuggyWheel_H
#define _MoonBuggyWheel_H

#include <bwvr/VrBall.h>
//#include <bwvr/VrCylinder.h>
class VrRod ;

#include <bwvr/VrHinge2.h>
#include <bwvr/VrMech.h>
#include "MoonBuggyBrain.h"
namespace MoonBuggy {

class BuggyWheelFactory ;
class BuggyBody ;
class BuggyWheel ;
class BuggyMech ;

class BuggyWheelMech : public VrJointMech {
public:
	BuggyWheelMech(BuggyWheel *pWheel) ;

	virtual void doCreate(const BwPartInfo& info) ;
	virtual void doConfig() ;
	virtual void doEnable(bool sleeping = false) ;
	virtual void doPostEnable(bool sleeping = false) ;
	void setWheelPosition() ;
	BuggyBrain& master() { return *static_cast<BuggyBrain*>(p_master) ; }
	//Data Members
	BuggyWheel *p_wheel ;
	VrModel *p_chassis ;
} ;

class BuggyWheel : public VrBall {
//class BuggyWheel : public VrCylinder {
public:
	BuggyWheel(int indice, Buggy *pBuggy) ;
	virtual void doCreate(const BwPartInfo& info) ;
	BuggyWheelFactory& factory() { return *static_cast<BuggyWheelFactory*>(p_factory) ; }
	BuggyWheelMech& brain() { return *static_cast<BuggyWheelMech*>(p_brain) ; }
	virtual bwString getClassName() { return "Wheel" ; }
	//Data Members
	Buggy *p_buggy ;
private:
} ;
}//end namespace BwVr::Bots::MoonBuggy
#endif //_MoonBuggyWheel_H
