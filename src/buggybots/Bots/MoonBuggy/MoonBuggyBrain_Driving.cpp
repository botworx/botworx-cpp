/*BuggyBots - A Botworx VR reference app and AI playground
Copyright (C) 2005  Kurtis Fields. See BuggyBots_License.txt for details.
*/
#include "stdafx.h"

#include <buggybots/bots/moonbuggy/MoonBuggyBrain.h>
#include <buggybots/bots/moonbuggy/MoonBuggy.h>
#include <buggybots/bots/moonbuggy/MoonBuggyEngine.h>
#include <buggybots/bots/moonbuggy/MoonBuggyBody.h>
#include <buggybots/bots/moonbuggy/MoonBuggyWheel.h>
#include <buggybots/bots/moonbuggy/MoonBuggyFactory.h>

#include <bwvr/VrSteering.h>

namespace MoonBuggy {
void BuggyBrain::moveForward() {
	if(!m_drivingTimer.checkAlarm()) {
		return ;
	}
	m_drivingTimer.resetAlarm() ;
	//m_power += .25 ;
	m_power += m_powerIncrement ;
	p_engine->setPower(m_power) ;
}
void BuggyBrain::moveReverse() {
	if(!m_drivingTimer.checkAlarm()) {
		return ;
	}
	m_drivingTimer.resetAlarm() ;
	m_power -= m_powerIncrement ;
	p_engine->setPower(m_power) ;
}
void BuggyBrain::moveNone() {
	if(!m_drivingTimer.checkAlarm()) {
		return ;
	}
	m_drivingTimer.resetAlarm() ;

	m_power = 0 ;
	p_engine->setPower(m_power) ;
}
}//end namespace BwVr::Bots::MoonBuggy 