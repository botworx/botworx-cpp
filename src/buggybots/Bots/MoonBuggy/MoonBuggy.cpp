/*BuggyBots - A Botworx VR reference app and AI playground
Copyright (C) 2005  Kurtis Fields. See BuggyBots_License.txt for details.
*/
#include "stdafx.h"

#include <buggybots/bots/moonbuggy/MoonBuggyFactory.h>
#include <buggybots/bots/moonbuggy/MoonBuggy.h>
#include <buggybots/bots/moonbuggy/MoonBuggyEngine.h>
#include <buggybots/bots/moonbuggy/MoonBuggyBrain.h>
#include <buggybots/bots/moonbuggy/MoonBuggyChassis.h>
#include <buggybots/bots/moonbuggy/MoonBuggyBody.h>
#include <buggybots/bots/moonbuggy/MoonBuggyWheel.h>

#include <buggybots/BbMissileLauncher.h>
#include <buggybots/BbLaserGun.h>
#include <buggybots/BbLaser.h>

#include <bwvr/VrMotor.h>
#include <bwvr/VrSteering.h>
#include <bwvr/VrJoint.h>
#include <bwvr/VrBody.h>

namespace MoonBuggy {
/////////
Buggy::Buggy(VrGroup *pGroup) : VrDynamicAssembly(pGroup) {
	setIsAutoSleeper(false) ;
	setIsEntity(true) ;
	setTestInternal(false) ; //TODO:the whole test internal thing?
	p_missiles = NULL ;
	p_lasers = NULL ;
	for(int i=0; i<4; ++i) {
		p_wheel[i] = NULL ; 
	}
}
Buggy::~Buggy(){
}
void Buggy::doCreate(const BwPartInfo& info) {
	VrDynamicAssembly::doCreate(info) ;

	BuggyChassis *pChassis = new BuggyChassis(this) ;
	pChassis->create() ;

	setMain(pChassis) ;

	p_missiles = new BbMissileLauncher(pChassis) ;
	p_missiles->create() ;
	//p_missiles->setRelPos(.75, .25, 0) ;
	p_missiles->setRelPos(1.0f, .25, 0) ;
	p_missiles->setSize(.25, .25, 1) ;

	p_lasers = new BbLaserGun(pChassis) ;
	p_lasers->create() ;
	//p_lasers->setRelPos(-.75, .25, 0) ;
	p_lasers->setRelPos(-1.0f, .25, 0) ;
	p_lasers->setSize(.25, .25, 1) ;

	BuggyWheelFactory& wheelFactory = BuggyWheelFactory::singleton::get() ;

	BuggyWheel *pWheel = NULL ;
	for(int i=0; i<4; ++i) {
		pWheel = static_cast<BuggyWheel*>(wheelFactory.rent(i, this)) ;
		p_wheel[i] = pWheel ; 
	}
}
void Buggy::createBrain() {
	p_brain = new BuggyBrain(this) ;
	p_brain->create() ;
}
void Buggy::flip(bwReal fx, bwReal fy, bwReal fz, bwReal px, bwReal py, bwReal pz) {
	getMain()->getBody()->addRelForceAtRelPos(bwVector3(fx,fy,fz), bwPoint3(px,py,pz)) ;
}
void Buggy::rollLeft(bwReal degree) {
	bwReal force = getMain()->getBody()->bodyInfo().getMass() * -100 ;
	flip(0, 1, 0, force, 0, 0) ;
}
void Buggy::rollRight(bwReal degree) {
	bwReal force = getMain()->getBody()->bodyInfo().getMass() * 100 ;
	flip(0, 1 , 0, force, 0, 0) ;
}
void Buggy::fireMissile() {
	p_missiles->pullTrigger() ;
}
void Buggy::fireLaser() {
	if(!p_lasers->getTriggerState())
		p_lasers->pullTrigger() ;
	else
		p_lasers->releaseTrigger() ;
}
} //end namespace BwVr::Bots::MoonBuggy 