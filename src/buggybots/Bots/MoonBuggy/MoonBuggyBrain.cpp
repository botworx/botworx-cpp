/*BuggyBots - A Botworx VR reference app and AI playground
Copyright (C) 2005  Kurtis Fields. See BuggyBots_License.txt for details.
*/
#include "stdafx.h"

#include <buggybots/bots/moonbuggy/MoonBuggyBrain.h>
#include <buggybots/bots/moonbuggy/MoonBuggy.h>
#include <buggybots/bots/moonbuggy/MoonBuggyFactory.h>
#include <buggybots/bots/moonbuggy/MoonBuggyWheel.h>
#include <buggybots/bots/moonbuggy/MoonBuggyChassis.h>
#include <buggybots/bots/moonbuggy/MoonBuggyEngine.h>

#include <bwvr/VrSteering.h>
#include <bwvr/_VrBrain.h>

namespace MoonBuggy {
BuggyBrain::BuggyBrain(Buggy *pBuggy) : VrBrain(pBuggy),
		m_firingTimer(std::chrono::milliseconds(500)),
		m_steeringTimer(std::chrono::milliseconds(16)),
		m_drivingTimer(std::chrono::seconds(1)) {
	p_buggy = pBuggy ;
	p_buggyFactory = BuggyFactory::singleton::getPtr() ;
	p_wheelFactory = BuggyWheelFactory::singleton::getPtr() ;
	p_engine = NULL ;
	p_steering = NULL ;
	m_powerIncrement = .50 ;
}
void BuggyBrain::doCreate(const BwPartInfo& info) {
	BwBrain::doCreate(info) ;

	p_chassis = static_cast<BuggyChassis*>(p_buggy->getMain()) ;
	p_engine = new BuggyEngine(this) ;
	p_engine->create() ;
	p_steering = new VrSteering(this) ;
	p_steering->create() ;

	BuggyWheelMech *pMech ;

	for(int i = 0 ; i < Buggy::WHEEL_TTL ; ++i) {
		pMech = new BuggyWheelMech(p_buggy->getWheelAt(i)) ;
		addSlave(pMech) ;
		pMech->create() ;
	}

}
void BuggyBrain::fireMissile() {
 	if(m_firingTimer.checkAlarm()) {
		p_buggy->fireMissile() ;
		m_firingTimer.resetAlarm() ;
	}
}
void BuggyBrain::fireLaser() {
 	if(m_firingTimer.checkAlarm()) {
		p_buggy->fireLaser() ;
		m_firingTimer.resetAlarm() ;
	}
}
void BuggyBrain::rollLeft() {
	p_buggy->rollLeft(bwRealTraits::PiDiv180) ;
}
void BuggyBrain::rollRight() {
	p_buggy->rollRight(bwRealTraits::PiDiv180) ;
}

} //end namespace BwVr::Bots::MoonBuggy 