/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <bwvr/VrMotor.h>
#include <bwvr/VrMech.h>

VrMotor::VrMotor(BwPart *pOwner, VrRod *pRod, bwReal radius) : VrGear(pOwner, pRod, radius) {
}
VrMotor::~VrMotor() {
}
void VrMotor::setPower(bwReal power) {
	m_power = power ;
}
	
