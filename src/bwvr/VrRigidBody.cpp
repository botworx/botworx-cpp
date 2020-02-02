/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <bwvr/VrRigidBody.h>
#include <bwvr/VrPhysics.h>

#include <bwvr/VrGroup.h>

#include <bwmessaging/BwMailSlot.h>

#include <bwcore/BwKernel.h>
#include <bwcore/_BwKernel.h>

VrRigidBody::VrRigidBody(VrModel *pModel) : VrBody(pModel) {
	m_bodyID = NULL ;
}
VrRigidBody::~VrRigidBody() {
	/*if(m_bodyID != NULL)
		dBodyDestroy(m_bodyID) ;*/
}
void VrRigidBody::doCreate(const BwPartInfo& info) {
	VrBody::doCreate(info) ;
	m_bodyID = dBodyCreate(VrPhysics::singleton::get().getWorldID());
	dBodySetData(m_bodyID, this) ;
}
void VrRigidBody::doEnable(bool sleeping) {
	if(m_bodyID != NULL) {
		if(sleeping)
			dBodyDisable(m_bodyID) ;
		else
			dBodyEnable(m_bodyID) ;
	}
	//TODO:seems like a tail call but maybe not here ... see VrBody::doEnable
	VrBody::doEnable(sleeping) ;
}
void VrRigidBody::doDisable(bool sleeping) {
	/*if(m_bodyID != NULL) {
		dBodyDisable(m_bodyID) ;
	}*/
	if(sleeping)
		dBodyDisable(m_bodyID) ;
	else
		dBodyDestroy(m_bodyID) ;
	VrBody::doDisable(sleeping) ;
}
void VrRigidBody::updateLinearVel() {
	const bwReal *vect = dBodyGetLinearVel(m_bodyID);
	m_linearVel = bwVector3(vect[0], vect[1], vect[2]) ;
	m_linearEnergy = lengthSquared(m_linearVel) ;
}
void VrRigidBody::updateAngularVel() {
	const bwReal *vect = dBodyGetAngularVel(m_bodyID) ;
	m_angularVel = bwVector3(vect[0], vect[1], vect[2]) ;
	m_angularEnergy = lengthSquared(m_angularVel) ;
}
void VrRigidBody::setBodyInfo(const VrBodyInfo *bodyInfo) {
	VrBody::setBodyInfo(bodyInfo) ;
	if(m_bodyID != NULL) {
	// The centre of mass must be at the origin.
	// Use dMassTranslate( mass, -mass->c[0], -mass->c[1], -mass->c[2] ) to correct it.
		dMass& mass = m_bodyInfo.m_dMass ;
		dMassTranslate( &mass, -mass.c[0], -mass.c[1], -mass.c[2] ) ;
		dBodySetMass(m_bodyID, &m_bodyInfo.m_dMass) ;
	}
}
void VrRigidBody::setGravityMode(int mode) {
	if(m_bodyID != NULL) {
		dBodySetGravityMode(getBodyID(), mode);
	}
}
void VrRigidBody::setQuat(const bwQuat& quat) {
	dQuaternion dQuat ;
	dQuat[0] = quat[3] ;
	dQuat[1] = quat[0] ;
	dQuat[2] = quat[1] ;
	dQuat[3] = quat[2] ;
	if(m_bodyID != NULL)
		dBodySetQuaternion(m_bodyID, dQuat) ;
}

bwQuat VrRigidBody::getQuat() {
	const bwReal *quat ;
	quat = dBodyGetQuaternion (m_bodyID);
	return bwQuat(quat[1], quat[2], quat[3], quat[0]) ;
}
void VrRigidBody::setPos(const bwPoint3& pos) {
	if(m_bodyID != NULL)
		dBodySetPosition(m_bodyID, pos[0], pos[1], pos[2]) ;
}
bwPoint3 VrRigidBody::getPos() {
	const bwReal *vector ;
	vector = dBodyGetPosition(m_bodyID);
	if(vector[0] != vector[0]) {
#if VR_OPTION_WARNING
		_BwKernel::Warning evt(p_model->getName() + " not in scenario!!!\n") ;
		BwKernel::singleton::get().getEventSlot()->send(evt) ;
#endif //VR_OPTION_WARNING
		return bwVector3(100,2,100) ;
	}
	return bwVector3(vector[0], vector[1], vector[2]) ;
}
void VrRigidBody::setLinearVel(const bwVector3& vel) {
	VrBody::setLinearVel(vel) ;
	dBodySetLinearVel(m_bodyID, vel[0], vel[1], vel[2]) ;
}
void VrRigidBody::setAngularVel(const bwVector3& vel) {
	VrBody::setAngularVel(vel) ;
	dBodySetAngularVel(m_bodyID, vel[0], vel[1], vel[2]) ;
}
void VrRigidBody::addForce(const bwVector3& force) {
	dBodyAddForce(getBodyID(), force[0], force[1], force[2]) ;
}
void VrRigidBody::addRelForce(const bwVector3& force) {
	dBodyAddRelForce(getBodyID(), force[0], force[1], force[2]) ;
}
void VrRigidBody::addForceAtPos(const bwVector3& force, const bwPoint3& point) {
	dBodyAddForceAtPos(getBodyID(), 
		force[0], force[1], force[2],
		point[0] , point[1] , point[2]) ;
}
void VrRigidBody::addForceAtRelPos(const bwVector3& force, const bwPoint3& point) {
	dBodyAddForceAtRelPos(getBodyID(),
		force[0], force[1], force[2],
		point[0] , point[1] , point[2]) ;
}
void VrRigidBody::addRelForceAtRelPos(const bwVector3& force, const bwPoint3& point) {
	dBodyAddRelForceAtRelPos(getBodyID(),
		force[0], force[1], force[2],
		point[0] , point[1] , point[2]) ;
}
void VrRigidBody::addTorque(const bwVector3& torque) {
	dBodyAddTorque(getBodyID(), torque[0], torque[1], torque[2]) ;
}
void VrRigidBody::addRelTorque(const bwVector3& torque) {
	dBodyAddRelTorque(getBodyID(), torque[0], torque[1], torque[2]) ;
}