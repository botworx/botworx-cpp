#include "stdafx.h"

#include <bwvr/VrSteering.h>

VrSteering::VrSteering(BwPart *pOwner, VrRod *pRod, bwReal radius) 
	: VrGear(pOwner, pRod, radius) {
}
void VrSteering::turnLeft() {
	setAngle(getAngle() - bwRealTraits::PiDiv180) ;
}
void VrSteering::turnRight() {
	setAngle(getAngle() + bwRealTraits::PiDiv180) ;
}
void VrSteering::turnNone() {
	setAngle(0) ;
}