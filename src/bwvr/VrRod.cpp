#include "stdafx.h"

#include <bwvr/VrRod.h>

VrRod::VrRod(BwPart *pOwner) : BwPart(pOwner) {
	m_hasAngleLimits = false ;
	m_angle = 0 ;
}
void VrRod::setAxis(bwReal x, bwReal y, bwReal z) {
}
void VrRod::setLoStop(bwReal value) {
}
void VrRod::setHiStop(bwReal value) {
}
void VrRod::setVelocity(bwReal value) {
}
void VrRod::setForceMax(bwReal value) {
}
void VrRod::addTorque(bwReal value) {
}
//
void VrRod::setAngle(bwReal angle) {
	bwReal temporary = angle ;
	if(angle < -bwRealTraits::Pi)
		temporary = (-angle) - bwRealTraits::Pi ;
	else if(angle > bwRealTraits::Pi)
		temporary = - (angle - bwRealTraits::Pi) ;

	if(m_hasAngleLimits) {
		if(temporary < m_angleMin)
			temporary = m_angleMin ;
		else if(temporary > m_angleMax)
			temporary = m_angleMax ;
	}
	m_angle = temporary ;
	setLoStop(m_angle - bwRealTraits::PiDiv180) ;
	setHiStop(m_angle + bwRealTraits::PiDiv180) ;
}
bwReal VrRod::getAngle() {
	return m_angle;
}
