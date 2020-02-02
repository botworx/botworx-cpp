/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <buggybots/bots/ufo/UfoBrain.h>
#include <buggybots/bots/ufo/Ufo.h>

#include <bwvr/VrKinematicPoser.h>

UfoBrain::UfoBrain(Ufo *pUfo) : BbPilotBrain(pUfo) {
	p_animat = pUfo ;
	p_poser = new VrKinematicPoser(p_animat) ;
}
void UfoBrain::turnLeft() {
	p_poser->turnLeft(bwRealTraits::PiDiv180) ;
}
void UfoBrain::turnRight() {
	p_poser->turnRight(bwRealTraits::PiDiv180) ;
}
void UfoBrain::moveForward() {
	p_poser->moveForward(.5) ;
}
void UfoBrain::moveReverse() {
	p_poser->moveReverse(.5) ;
}
void UfoBrain::pitchUp() {
	p_poser->pitchUp(bwRealTraits::PiDiv180) ;
}
void UfoBrain::pitchDown() {
	p_poser->pitchDown(bwRealTraits::PiDiv180) ;
}
void UfoBrain::rollLeft() {
	p_poser->rollLeft(bwRealTraits::PiDiv180) ;
}
void UfoBrain::rollRight() {
	p_poser->rollRight(bwRealTraits::PiDiv180) ;
}