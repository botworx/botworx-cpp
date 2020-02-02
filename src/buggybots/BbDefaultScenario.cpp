/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <buggybots/BbScenario.h>
#include <buggybots/BbWorld.h>

BbSimpleScenario::BbSimpleScenario(VrApplet* pApplet) : BbScenario(pApplet) {
}
BbDefaultScenario::BbDefaultScenario(VrApplet* pApplet) : BbScenario(pApplet) {
	m_usesToys = true ;
	m_usesLevels = true ;
	m_usesBalls = true ;
	avatarInfo().setAvatarType(AVATAR_BUGGY) ;
}
BbTerrainScenario::BbTerrainScenario(VrApplet* pApplet) : BbScenario(pApplet) {
	setGroundType(GROUND_TERRAIN) ;
	m_usesToys = true ;
	m_usesLevels = true ;
	m_usesBalls = true ;
	avatarInfo().setAvatarType(AVATAR_BUGGY) ;
}