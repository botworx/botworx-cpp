/*BikeBots - A Botworx VR reference app and AI playground
Copyright (C) 2005  Kurtis Fields. See BikeBots_License.txt for details.
*/
#ifndef _Bike_H
#define _Bike_H

#include <bwvr/VrDynamicAssembly.h>
#include "BikeFactory.h"

class BbMissileLauncher ;
class BbLaserGun ;
class VrSteering ;

#include <bwvr/VrMech.h>

namespace Bike {
class Bike ;
class BikeFactory ;
class BikeBrain ;
class BikeEngine ;
class BikeChassis ;
class BikePrimary ;
class BikeWheel ;

class Bike : public VrDynamicAssembly
{
public:
	Bike(VrGroup *pGroup) ;
	virtual void doCreate(const BwPartInfo& info) ;
	virtual void createBrain() ;
	virtual ~Bike();

	BikeFactory& factory() { return *static_cast<BikeFactory*>(p_factory) ; }
	virtual bwString getClassName() { return "Bike::Bike" ; }

	BbMissileLauncher* getMissiles() { return p_missiles ; }

	virtual void fireMissile() ;
	virtual void fireLaser() ;

	BikeWheel* getWheelAt(int index) { return p_wheel[index] ; }
	enum {
		WHEEL_REAR = 0,
		WHEEL_FRONT,
		WHEEL_TTL
	} ;
	BikeChassis* getChassis() { return p_chassis ; }
private:
	BikeChassis* p_chassis ;
	BikeWheel *p_wheel[WHEEL_TTL] ;
	BbMissileLauncher *p_missiles ;
	BbLaserGun *p_lasers ;
public:
	void rollLeft(bwReal degree) ;
	void rollRight(bwReal degree) ;

	void flip(bwReal fx, bwReal fy, bwReal fz, bwReal px, bwReal py, bwReal pz) ;
};
} //end namespace BwVr::Bots::Bike
#endif

