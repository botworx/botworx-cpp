/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <buggybots/BbGun.h>

BbGun::BbGun(VrGroup *pGroup) : VrCapsule(pGroup) {
	m_triggerState = false ;
}