/*JrBots - A Botworx VR reference app and AI playground
Copyright (C) 2005  Kurtis Fields. See JrBots_License.txt for details.
*/
#include "stdafx.h"

#include <buggybots/bots/jr/JrBrain.h>
#include <buggybots/bots/jr/Jr.h>
#include <buggybots/bots/jr/JrFactory.h>
#include <buggybots/bots/jr/JrWheel.h>
#include <buggybots/bots/jr/JrChassis.h>
#include <buggybots/bots/jr/JrEngine.h>

#include <bwvr/VrSteering.h>

namespace Jr {
JrBrain::JrBrain(Jr *pJr) : VrBrain(pJr),
		m_firingTimer(std::chrono::seconds(1)),
		m_steeringTimer(std::chrono::milliseconds(16)),
		m_drivingTimer(std::chrono::seconds(1)) {
	p_jr = pJr ;
	p_jrFactory = JrFactory::singleton::getPtr() ;
	p_wheelFactory = JrWheelFactory::singleton::getPtr() ;
	//p_engine = NULL ;
	p_steering = NULL ;
	m_powerIncrement = .50 ;
}
void JrBrain::doCreate(const BwPartInfo& info) {
	VrBrain::doCreate(info) ;

	//p_chassis = static_cast<JrChassis*>(p_jr->getChassis()) ;
	p_chassis = static_cast<JrChassis*>(p_jr->getMain()) ;
	p_steering = new VrSteering(this) ;
	p_steering->create() ;

	JrWheelMech *pMech ;

	for(int i = 0 ; i < Jr::WHEEL_TTL ; ++i) {
		pMech = new JrWheelMech(p_jr->getWheelAt(i)) ;
		addSlave(pMech) ;
		pMech->create() ;
		p_wheelMech[i] = pMech ;
	}
}
void JrBrain::fireMissile() {
 	if(m_firingTimer.checkAlarm()) {
		p_jr->fireMissile() ;
		m_firingTimer.resetAlarm() ;
	}
}
void JrBrain::fireLaser() {
 	if(m_firingTimer.checkAlarm()) {
		p_jr->fireLaser() ;
		m_firingTimer.resetAlarm() ;
	}
}
void JrBrain::rollLeft() {
	p_jr->rollLeft(bwRealTraits::PiDiv180) ;
}
void JrBrain::rollRight() {
	p_jr->rollRight(bwRealTraits::PiDiv180) ;
}

} //end namespace BwVr::Bots::Jr 