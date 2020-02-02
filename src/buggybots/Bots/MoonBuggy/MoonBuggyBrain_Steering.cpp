/*BuggyBots - A Botworx VR reference app and AI playground
Copyright (C) 2005  Kurtis Fields. See BuggyBots_License.txt for details.
*/
#include "stdafx.h"

#include <buggybots/bots/moonbuggy/MoonBuggyBrain.h>
#include <buggybots/bots/moonbuggy/MoonBuggy.h>
#include <buggybots/bots/moonbuggy/MoonBuggyFactory.h>
#include <buggybots/bots/moonbuggy/MoonBuggyEngine.h>

#include <bwvr/VrSteering.h>

namespace MoonBuggy {
void BuggyBrain::turnLeft() {
	if(!m_steeringTimer.checkAlarm()) {
		return ;
	}
	m_steeringTimer.resetAlarm() ;
	p_steering->turnLeft() ;
}
 
void BuggyBrain::turnRight() {
		if(!m_steeringTimer.checkAlarm()) {
		return ;
	}
	m_steeringTimer.resetAlarm() ;
	p_steering->turnRight() ;
}
void BuggyBrain::turnNone() {
	if(!m_steeringTimer.checkAlarm()) {
		return ;
	}
	m_steeringTimer.resetAlarm() ;
	p_steering->turnNone() ;
}
}//end namespace BwVr::Bots::MoonBuggy 