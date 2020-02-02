/*JrBots - A Botworx VR reference app and AI playground
Copyright (C) 2005  Kurtis Fields. See JrBots_License.txt for details.
*/
#include "stdafx.h"

#include <buggybots/bots/jr/JrFactory.h>
#include <buggybots/bots/jr/Jr.h>
#include <buggybots/bots/jr/JrEngine.h>

namespace Jr {
JrEngine::JrEngine(VrMech *pMech) : VrMotor(pMech, NULL, 1) {
}
void JrEngine::setPower(bwReal power) {
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
}//end namespace Jr {
