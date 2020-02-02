/*BikeBots - A Botworx VR reference app and AI playground
Copyright (C) 2005  Kurtis Fields. See BikeBots_License.txt for details.
*/
#include "stdafx.h"

#include <buggybots/bots/bike/BikeBrain.h>
#include <buggybots/bots/bike/Bike.h>
#include <buggybots/bots/bike/BikeEngine.h>
#include <buggybots/bots/bike/BikePrimary.h>
#include <buggybots/bots/bike/BikeWheel.h>
#include <buggybots/bots/bike/BikeFactory.h>

#include <bwvr/VrSteering.h>

namespace Bike {
void BikeBrain::moveForward() {
	if(!m_drivingTimer.checkAlarm()) {
		return ;
	}
	m_drivingTimer.resetAlarm() ;
	//m_power += .25 ;
	m_power += m_powerIncrement ;
	p_engine->setPower(m_power) ;
}
void BikeBrain::moveReverse() {
	if(!m_drivingTimer.checkAlarm()) {
		return ;
	}
	m_drivingTimer.resetAlarm() ;
	m_power -= m_powerIncrement ;
	p_engine->setPower(m_power) ;
}
void BikeBrain::moveNone() {
	if(!m_drivingTimer.checkAlarm()) {
		return ;
	}
	m_drivingTimer.resetAlarm() ;

	m_power = 0 ;
	p_engine->setPower(m_power) ;
}
}//end namespace BwVr::Bots::Bike 