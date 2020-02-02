/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <buggybots/bots/ufo/Ufo.h>
#include <buggybots/bots/ufo/UfoBrain.h>

#include <bwvr/VrVu.h>
#include <bwvr/VrBody.h>
#include <bwvr/VrCollider.h>

Ufo::Ufo(VrGroup *pGroup) : VrBall(pGroup) {
	setMotionType(MOTION_KINEMATIC) ;
	setIsGhost(true) ;
	vuInfo().setMeshName("Ufo.mesh") ;
	vuInfo().setIsAutoScaler(false) ;
}
void Ufo::createBrain() {
	p_brain = new UfoBrain(this) ;
	p_brain->create() ;
}