/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <buggybots/bots/mapper/MapperBrain.h>
#include <buggybots/bots/mapper/Mapper.h>

#include <bwvr/VrKinematicPoser.h>

MapperBrain::MapperBrain(Mapper *pMapper) : BbPilotBrain(pMapper) {
	p_animat = pMapper ;
	p_poser = new VrKinematicPoser(p_animat) ;
}
void MapperBrain::turnLeft() {
	p_poser->turnLeft(bwRealTraits::PiDiv180) ;
}
void MapperBrain::turnRight() {
	p_poser->turnRight(bwRealTraits::PiDiv180) ;
}
void MapperBrain::moveForward() {
	p_poser->moveForward(.5) ;
}
void MapperBrain::moveReverse() {
	p_poser->moveReverse(.5) ;
}
void MapperBrain::pitchUp() {
	p_poser->pitchUp(bwRealTraits::PiDiv180) ;
}
void MapperBrain::pitchDown() {
	p_poser->pitchDown(bwRealTraits::PiDiv180) ;
}
void MapperBrain::rollLeft() {
	p_poser->rollLeft(bwRealTraits::PiDiv180) ;
}
void MapperBrain::rollRight() {
	p_poser->rollRight(bwRealTraits::PiDiv180) ;
}