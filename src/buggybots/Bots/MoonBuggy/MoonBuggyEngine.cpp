/*BuggyBots - A Botworx VR reference app and AI playground
Copyright (C) 2005  Kurtis Fields. See BuggyBots_License.txt for details.
*/
#include "stdafx.h"

#include <buggybots/bots/moonbuggy/MoonBuggyFactory.h>
#include <buggybots/bots/moonbuggy/MoonBuggy.h>
#include <buggybots/bots/moonbuggy/MoonBuggyEngine.h>

namespace MoonBuggy {
BuggyEngine::BuggyEngine(VrMech *pMech) : VrMotor(pMech, NULL, 1) {
}
void BuggyEngine::setPower(bwReal power) {
	m_power = power ;
	if(m_power > 0) {
		setVelocity(m_power) ;
		setForceMax(m_power*.1) ;
	}
	else {
		setVelocity(m_power) ;
		setForceMax(-m_power*.1) ;
	}
}
}//end namespace MoonBuggy {
