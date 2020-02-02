/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <bwvr/VrMech.h>
#include <bwvr/VrModel.h>
#include <bwvr/VrMotor.h>
#include <bwvr/VrJoint.h>

VrMech::VrMech(BwActor *pOwner) : BwBrain(pOwner) {
	setIsStageDriven(false) ; //manually stepped by VrModel.  This is a master brain?
}