/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <bwvr/VrBodyInfo.h>

#define DENSITY_GOLD 19300.0f
#define DENSITY_URANIUM 19050.0f
#define DENSITY_LEAD 11350.0f
#define DENSITY_COPPER 8960.0f
#define DENSITY_IRON 7870.0f
#define DENSITY_ALUMINUM 2700.0f
#define DENSITY_WATER 1000.0f
#define DENSITY_AIR 1.2f

const bwReal VrBodyInfo::DENSITY_MIN = DENSITY_AIR ;
const bwReal VrBodyInfo::DENSITY_MAX = DENSITY_GOLD ;
const bwReal VrBodyInfo::DENSITY_DEFAULT = DENSITY_IRON ;

const bwReal VrBodyInfo::MASS_MIN = .0012f ;
const bwReal VrBodyInfo::MASS_MAX = 19.3f ;
const bwReal VrBodyInfo::MASS_DEFAULT = 0.1f ;

//const bwReal VrBodyInfo::DRAG_DEFAULT = -1 ;
const bwReal VrBodyInfo::DRAG_DEFAULT = -0.25f ;

VrBodyInfo::VrBodyInfo() {
	zero() ;
	//m_solidity = 1.0f ;
	m_solidity = .0001f ;
	m_density = DENSITY_DEFAULT ;
	//m_linearDrag = DRAG_DEFAULT ;
	m_linearDrag = 0 ;
	//m_angularDrag = DRAG_DEFAULT ;
	m_angularDrag = 0 ;
}
void VrBodyInfo::setDensity(bwReal density) {
	m_density = density ;
	m_invDensity = bwmath::rcp(density) ;
}
void VrBodyInfo::setInvDensity(bwReal invDensity) {
	m_invDensity = invDensity ;
	m_density = bwmath::rcp(invDensity) ;
}
//Mass
void VrBodyInfo::setMass(bwReal mass) {
	_setMass(mass) ;
	m_invMass = bwmath::rcp(mass) ;
}
void VrBodyInfo::setInvMass(bwReal invMass) {
	m_invMass = invMass ;
	_setMass(bwmath::rcp(invMass)) ;
}
void VrBodyInfo::translate(const bwPoint3& point) {
	dMassTranslate(&m_dMass, point[0], point[1], point[2]) ;
}
void VrBodyInfo::rotate(const bwQuat& quat) {
	//Rotation
	dMatrix3 rotation ;
	bwReal dQuat[4] ;
	dQuat[0] = quat[3] ;
	dQuat[1] = quat[0] ;
	dQuat[2] = quat[1] ;
	dQuat[3] = quat[2]  ;
	dRfromQ(rotation, dQuat) ;
	dMassRotate (&m_dMass,rotation);
}
void VrBodyInfo::setSphere(bwReal radius) {
	dMassSetSphere(&m_dMass, getDensity() * m_solidity, radius);
}
void VrBodyInfo::setBox(const bwSize3& size) {
	dMassSetBox(&m_dMass, getDensity() * m_solidity, size[0], size[1], size[2]);
}
void VrBodyInfo::setCapsule(const bwSize3& size) {
	bwAssert(0) ;
	///void dMassSetCappedCylinder (dMass *m, dReal density, int direction, dReal radius, dReal length)
	/*dMassSetCappedCylinder(&m_dMass, getDensity(), int direction,
			     dReal radius, dReal length)*/
}
