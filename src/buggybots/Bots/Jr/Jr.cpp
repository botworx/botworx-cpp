/*JrBots - A Botworx VR reference app and AI playground
Copyright (C) 2005  Kurtis Fields. See JrBots_License.txt for details.
*/
#include "stdafx.h"

#include <buggybots/bots/jr/JrFactory.h>
#include <buggybots/bots/jr/Jr.h>
#include <buggybots/bots/jr/JrEngine.h>
#include <buggybots/bots/jr/JrBrain.h>
#include <buggybots/bots/jr/JrChassis.h>
#include <buggybots/bots/jr/JrBody.h>
#include <buggybots/bots/jr/JrWheel.h>

#include <buggybots/BbMissileLauncher.h>
#include <buggybots/BbLaserGun.h>
#include <buggybots/BbLaser.h>

#include <bwvr/VrMotor.h>
#include <bwvr/VrSteering.h>
#include <bwvr/VrJoint.h>
#include <bwvr/VrBody.h>

namespace Jr {
/////////
Jr::Jr(VrGroup *pGroup) : VrDynamicAssembly(pGroup) {
	setSize(bwSize3(3, 3, 3)) ;
	setMaxSize(bwSize3(6, 6, 6)) ;
	setIsEntity(true) ;
	setTestInternal(false) ; 
	setIsAutoSleeper(false) ;
	//p_chassis = NULL ;
	p_missiles = NULL ;
	p_lasers = NULL ;
	for(int i=0; i < WHEEL_TTL ; ++i) {
		p_wheel[i] = NULL ; 
	}
}
Jr::~Jr(){
}
void Jr::doCreate(const BwPartInfo& info) {
	VrDynamicAssembly::doCreate(info) ;

	JrChassis *pChassis = new JrChassis(this) ;
	pChassis->create() ;
	//p_chassis = pChassis ;
	p_main = pChassis ;

	p_missiles = new BbMissileLauncher(pChassis) ;
	p_missiles->create() ;
	p_missiles->setRelPos(-.75, .25, 0) ;
	p_missiles->setSize(.25, .25, 1) ;

	p_lasers = new BbLaserGun(pChassis) ;
	p_lasers->create() ;
	p_lasers->setRelPos(.75, .25, 0) ;
	p_lasers->setSize(.25, .25, 1) ;

	JrWheelFactory& wheelFactory = JrWheelFactory::singleton::get() ;

	JrWheel *pWheel = NULL ;
	for(int i=0; i<WHEEL_TTL; ++i) {
		pWheel = static_cast<JrWheel*>(wheelFactory.rent(i, this)) ;
		p_wheel[i] = pWheel ; 
	}
}
void Jr::createBrain() {
	p_brain = new JrBrain(this) ;
	p_brain->create() ;
}
void Jr::flip(bwReal fx, bwReal fy, bwReal fz, bwReal px, bwReal py, bwReal pz) {
	//p_chassis->getBody()->addRelForceAtRelPos(bwVector3(fx,fy,fz), bwPoint3(px,py,pz)) ;
	p_main->getBody()->addRelForceAtRelPos(bwVector3(fx,fy,fz), bwPoint3(px,py,pz)) ;
}
void Jr::rollLeft(bwReal degree) {
	//bwReal force = p_chassis->getBody()->m_mass.mass * 100 ;
	bwReal force = p_main->getBody()->bodyInfo().getMass() * 100 ;
	flip(0, 1, 0, force, 0, 0) ;
}
void Jr::rollRight(bwReal degree) {
	//bwReal force = p_chassis->getBody()->m_mass.mass * -100 ;
	bwReal force = p_main->getBody()->bodyInfo().getMass() * -100 ;
	flip(0, 1 , 0, force, 0, 0) ;
}
void Jr::fireMissile() {
	p_missiles->pullTrigger() ;
}
void Jr::fireLaser() {
	if(!p_lasers->getTriggerState())
		p_lasers->pullTrigger() ;
	else
		p_lasers->releaseTrigger() ;
}
} //end namespace BwVr::Bots::Jr 
