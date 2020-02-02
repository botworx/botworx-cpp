/*BuggyBots - A Botworx VR reference app and AI playground
Copyright (C) 2005  Kurtis Fields. See BuggyBots_License.txt for details.
*/
#ifndef _MoonBuggy_H
#define _MoonBuggy_H

#include <bwvr/VrDynamicAssembly.h>
#include "MoonBuggyFactory.h"

class BbMissileLauncher ;
class BbLaserGun ;
class VrSteering ;

#include <bwvr/VrMech.h>

namespace MoonBuggy {
class Buggy ;
class BuggyFactory ;
class BuggyBrain ;
class BuggyEngine ;
class BuggyChassis ;
class BuggyBody ;
class BuggyWheel ;

class Buggy : public VrDynamicAssembly
{
public:
	Buggy(VrGroup *pGroup) ;
	virtual void doCreate(const BwPartInfo& info) ;
	virtual void createBrain() ;
	virtual ~Buggy();

	BuggyFactory& factory() { return *static_cast<BuggyFactory*>(p_factory) ; }
	virtual bwString getClassName() { return "MoonBuggy::Buggy" ; }

	BbMissileLauncher* getMissiles() { return p_missiles ; }

	virtual void fireMissile() ;
	virtual void fireLaser() ;

	BuggyWheel* getWheelAt(int index) { return p_wheel[index] ; }
	enum {
		WHEEL_RL = 0,
		WHEEL_RR,
		WHEEL_FL,
		WHEEL_FR,
		WHEEL_TTL
	} ;
private:
	BuggyWheel *p_wheel[WHEEL_TTL] ;
	BbMissileLauncher *p_missiles ;
	BbLaserGun *p_lasers ;
public:
	virtual void rollLeft(bwReal degree) ;
	virtual void rollRight(bwReal degree) ;

	void flip(bwReal fx, bwReal fy, bwReal fz, bwReal px, bwReal py, bwReal pz) ;
};
} //end namespace BwVr::Bots::MoonBuggy
#endif

