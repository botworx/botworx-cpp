/*BikeBots - A Botworx VR reference app and AI playground
Copyright (C) 2005  Kurtis Fields. See BikeBots_License.txt for details.
*/
#include "stdafx.h"

#include <buggybots/bots/bike/BikeFactory.h>
#include <buggybots/bots/bike/Bike.h>
#include <buggybots/bots/bike/BikeEngine.h>
#include <buggybots/bots/bike/BikeBrain.h>
#include <buggybots/bots/bike/BikeChassis.h>
#include <buggybots/bots/bike/BikePrimary.h>
#include <buggybots/bots/bike/BikeWheel.h>

#include <buggybots/BbMissileLauncher.h>
#include <buggybots/BbLaserGun.h>
#include <buggybots/BbLaser.h>

#include <bwvr/VrMotor.h>
#include <bwvr/VrSteering.h>
#include <bwvr/VrJoint.h>
#include <bwvr/VrBody.h>

namespace Bike {
/////////
Bike::Bike(VrGroup *pGroup) : VrDynamicAssembly(pGroup) {
	setIsEntity(true) ;
	setTestInternal(false) ;
	setIsAutoSleeper(false) ;
	p_missiles = NULL ;
	p_lasers = NULL ;
	for(int i = 0; i < WHEEL_TTL ; ++i) {
		p_wheel[i] = NULL ; 
	}
}
Bike::~Bike(){
}
void Bike::doCreate(const BwPartInfo& info) {
	VrDynamicAssembly::doCreate(info) ;
	BikeChassis *pChassis = new BikeChassis(this) ;
	p_chassis = pChassis ;
	pChassis->create() ;

	setMain(pChassis) ;

	p_missiles = new BbMissileLauncher(pChassis) ;
	p_missiles->create() ;
	p_missiles->setRelPos(.5, .25, 0) ;
	p_missiles->setSize(.25, .25, 1) ;

	p_lasers = new BbLaserGun(pChassis) ;
	p_lasers->create() ;
	p_lasers->setRelPos(-.5, .25, 0) ;
	p_lasers->setSize(.25, .25, 1) ;

	BikeWheelFactory& wheelFactory = BikeWheelFactory::singleton::get() ;

	BikeWheel *pWheel = NULL ;
	for(int i = 0 ; i < WHEEL_TTL ; ++i) {
		pWheel = static_cast<BikeWheel*>(wheelFactory.rent(i, this)) ;
		p_wheel[i] = pWheel ; 
	}
}
void Bike::createBrain() {
	p_brain = new BikeBrain(this) ;
	p_brain->create() ;
}
void Bike::flip(bwReal fx, bwReal fy, bwReal fz, bwReal px, bwReal py, bwReal pz) {
	getMain()->getBody()->addRelForceAtRelPos(bwVector3(fx,fy,fz), bwPoint3(px,py,pz)) ;
}
void Bike::rollLeft(bwReal degree) {
	bwReal force = getMain()->getBody()->bodyInfo().getMass() * -100 ;
	flip(0, 1, 0, force, 0, 0) ;
}
void Bike::rollRight(bwReal degree) {
	bwReal force = getMain()->getBody()->bodyInfo().getMass() * 100 ;
	flip(0, 1 , 0, force, 0, 0) ;
}
void Bike::fireMissile() {
	p_missiles->pullTrigger() ;
}
void Bike::fireLaser() {
	if(!p_lasers->getTriggerState())
		p_lasers->pullTrigger() ;
	else
		p_lasers->releaseTrigger() ;
}
} //end namespace BwVr::Bots::Bike 