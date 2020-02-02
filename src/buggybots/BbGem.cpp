/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <buggybots/BbGem.h>

#include <bwvr/VrCollider.h>

BbGem::BbGem(VrGroup *pGroup) : VrConvexMesh(pGroup) {
	setMotionType(MOTION_QUASISTATIC) ;
	setIsGhost(true) ;
	vuInfo().setMeshName("Gem.mesh") ;
}