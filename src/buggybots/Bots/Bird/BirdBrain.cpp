/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <buggybots/bots/bird/BirdBrain.h>
#include <buggybots/bots/bird/Bird.h>

#include <bwvr/VrKinematicPoser.h>

BirdBrain::BirdBrain(Bird *pBird) : BbPilotBrain(pBird) {
	p_animat = pBird ;
	p_poser = new VrKinematicPoser(p_animat) ;
}
void BirdBrain::turnLeft() {
	p_poser->turnLeft(bwRealTraits::PiDiv180) ;
}
void BirdBrain::turnRight() {
	p_poser->turnRight(bwRealTraits::PiDiv180) ;
}
void BirdBrain::moveForward() {
	p_poser->moveForward(.5) ;
}
void BirdBrain::moveReverse() {
	p_poser->moveReverse(.5) ;
}
void BirdBrain::pitchUp() {
	p_poser->pitchUp(bwRealTraits::PiDiv180) ;
}
void BirdBrain::pitchDown() {
	p_poser->pitchDown(bwRealTraits::PiDiv180) ;
}
void BirdBrain::rollLeft() {
	p_poser->rollLeft(bwRealTraits::PiDiv180) ;
}
void BirdBrain::rollRight() {
	p_poser->rollRight(bwRealTraits::PiDiv180) ;
}