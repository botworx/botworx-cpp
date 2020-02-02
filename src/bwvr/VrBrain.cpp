/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <bwvr/VrBrain.h>
#include <bwvr/_VrBrain.h>

#include <bwvr/VrGroup.h>

//VrBrain::VrBrain(VrModel* pModel) : BwBrain(pModel) {
VrBrain::VrBrain(VrModel* pModel) : VrMech(pModel) {
	p_model = pModel ;
}
VrBrain::~VrBrain() {
}
bool VrBrain::processMessage(BwMessage&& msg)
{
	switch(msg.what()) {
		case _VrBrain::COMMAND_LEFT :
			turnLeft() ;
			break ;
		case _VrBrain::COMMAND_RIGHT :
			turnRight() ;
			break ;
		case _VrBrain::COMMAND_FORWARD :
			moveForward() ;
			break ;
		case _VrBrain::COMMAND_REVERSE :
			moveReverse() ;
			break ;
		case _VrBrain::COMMAND_PITCH_UP :
			pitchUp() ;
			break ;
		case _VrBrain::COMMAND_PITCH_DOWN :
			pitchDown() ;
			break ;
		case _VrBrain::COMMAND_ROLL_LEFT :
			rollLeft() ;
			break ;
		case _VrBrain::COMMAND_ROLL_RIGHT:
			rollRight() ;
			break ;
		case _VrBrain::COMMAND_JUMP :
			jump() ;
			break ;
		case _VrBrain::COMMAND_FIRE_MISSILE :
			fireMissile() ;
			break ;
		case _VrBrain::COMMAND_FIRE_LASER :
			fireLaser() ;
			break ;
	}
	return true ;
}