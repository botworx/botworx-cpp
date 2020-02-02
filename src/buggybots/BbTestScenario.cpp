/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <buggybots/BbTestScenario.h>
#include <buggybots/BbWorld.h>
#include <buggybots/BbTestScenario.h>
#include <buggybots/BbBuilder.h>

#include <bwvr/VrCollider.h>
#include <bwvr/VrQuadNodeKit.h>

namespace BbTestScenario {

BbTestScenario::BbTestScenario(VrApplet* pApplet) : BbScenario(pApplet) {
	m_usesToys = true ;
	m_usesLevels = true ;
	m_usesBalls = true ;
	setGroundType(GROUND_PLANE) ;
	avatarInfo().setAvatarType(AVATAR_UFO) ;
}

} //namespace BbTestScenario