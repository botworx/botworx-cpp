/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <bwcore/BwKernel.h>
#include <bwmessaging/BwMessaging.h>

#include <bwvr/VrBody.h>
#include <bwvr/VrGroup.h>
#include <bwvr/VrPhysics.h>

VrBody::VrBody(VrModel *pModel) : BwActor(pModel) {
	p_model = pModel ;
	p_parent = NULL ;
	setIsStageDriven(false) ; //manually stepped by VrModel.
	m_restThresh = .025f ;
	m_linearEnergy = 0 ;
	m_angularEnergy = 0 ;
	m_energy = 0 ;
	m_rotMode = bwmath::ROTMODE_FREE ;
	m_posMode = bwmath::POSMODE_FREE ;
}
VrBody::~VrBody() {
	disable(false) ;
}
void VrBody::doCreate(const BwPartInfo& info) {
	BwActor::doCreate(info) ;
	VrModel *pGroup = p_model->getGroup() ;
	if(pGroup != NULL)
		p_parent = pGroup->getBody() ;
}
void VrBody::doEnable(bool sleeping) {
	if(!isSleeping()) {
		setPos(p_model->getPos()) ;
		setQuat(p_model->getQuat()) ;
	}
	BwActor::doEnable(sleeping) ;
}
void VrBody::doDisable(bool sleeping) {
	if(!m_isEnabled)
		return ;
	BwActor::doDisable(sleeping) ;
}
void VrBody::_touch(VrModel *pModel) {
	if(p_parent != NULL)
		p_parent->_touch(pModel) ;
	else
		p_model->_touch(pModel) ;
}
void VrBody::_wake() {
	if(!isSleeping())
		return ;
	if(p_parent != NULL)
		p_parent->_wake() ;
	else
		p_model->_wake() ;
}
void VrBody::_sleep() {
	if(isSleeping())
		return ;
	p_model->_sleep() ;
}
void VrBody::doStep(BwStepper& stepper) {
	bwDT deltaTime = VrPhysics::singleton::get().getDeltaTime() ;
	dampen(deltaTime) ;
}
bool VrBody::onPostStep(BwStepper& stepper) {
	updateLinearVel() ;
	updateAngularVel() ;
	m_energy = m_linearEnergy + m_angularEnergy ;
	if(m_energy < m_restThresh)
		rest() ;
	else
		unrest() ;
	return true ;
}
void VrBody::setBodyInfo(const VrBodyInfo *bodyInfo) {
	memcpy(&m_bodyInfo, bodyInfo, sizeof(VrBodyInfo)) ;
}
void VrBody::dampen(bwReal stepSize) {
	bwVector3 linVel, angVel ;
	//if(m_energy < m_restThresh)
	if(m_energy == 0)
		return ;

	bwReal power = bodyInfo().getMass() ;
	linVel = m_linearVel * bodyInfo().getLinearDrag() * power * stepSize ;
	addForce(linVel) ;
	angVel = m_angularVel * bodyInfo().getAngularDrag() * power * stepSize ;
	addTorque(angVel) ;
}
void VrBody::setLinearVel(const bwVector3& vel) {
	m_linearVel = vel ;
}
bwVector3 VrBody::getLinearVel() {
	return m_linearVel ;
}
void VrBody::setAngularVel(const bwVector3& vel) {
	m_angularVel = vel ;
}
bwVector3 VrBody::getAngularVel() {
	return m_angularVel ;
}