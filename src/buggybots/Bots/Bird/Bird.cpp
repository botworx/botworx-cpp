/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <buggybots/bots/bird/Bird.h>
#include <buggybots/bots/bird/BirdBrain.h>

#include <bwvr/VrVu.h>
#include <bwvr/VrBody.h>
#include <bwvr/VrCollider.h>

Bird::Bird(VrGroup *pGroup) : VrBall(pGroup) {
	setMotionType(MOTION_KINEMATIC) ;
	setIsGhost(true) ;
	_setSize(bwSize3(1.25, .5, 2)) ;
	vuInfo().setMeshName("Bird.mesh") ;
}
void Bird::createBrain() {
	p_brain = new BirdBrain(this) ;
	p_brain->create() ;
}