/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <buggybots/BbTile.h>

BbTile::BbTile(VrGroup *pGroup) : VrBox(pGroup) {
	setMotionType(MOTION_STATIC) ;
	vuInfo().setMeshName("VrBox.mesh") ;
}