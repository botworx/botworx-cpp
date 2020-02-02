/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <bwvr/VrHinge.h>
#include <bwvr/VrPhysics.h>

VrHinge::VrHinge(VrGroup *pGroup) 
	: VrJoint(pGroup), m_rod_1(NULL) {
}
VrHinge::~VrHinge() {
}
void VrHinge::doCreate(const BwPartInfo& info) {
	VrJoint::doCreate(info) ;
	m_jointID = dJointCreateHinge(VrPhysics::singleton::get().getWorldID(), NULL);
	m_rod_1.create(this) ;
}
void VrHingeRod1::setAxis(bwReal x, bwReal y, bwReal z){
	bwVector3 axis = p_joint->getQuat() * bwVector3(x, y, z) ;
	dJointSetHingeAxis(getJoint().getJointID(), axis[0], axis[1], axis[2]);
}
bwReal VrHingeRod1::getAngle(){
	return dJointGetHingeAngle(getJoint().getJointID()) ;
}

void VrHingeRod1::setLoStop(bwReal loStop) {
	dJointSetHingeParam(getJoint().getJointID(), dParamLoStop, loStop);
}
void VrHingeRod1::setHiStop(bwReal hiStop) {
	dJointSetHingeParam(getJoint().getJointID(), dParamHiStop, hiStop);
}
void VrHingeRod1::setVelocity(bwReal value){
	dJointSetHingeParam(getJoint().getJointID(), dParamVel, value);	
}
void VrHingeRod1::setForceMax(bwReal value){
	dJointSetHingeParam(getJoint().getJointID(), dParamFMax, value);
}
void VrHingeRod1::addTorque(bwReal value){
	dJointAddHingeTorque(getJoint().getJointID(), value) ;
}
void VrHinge::setAnchor(const bwPoint3& pos) {
	dJointSetHingeAnchor(m_jointID, pos[0], pos[1], pos[2]) ;
}
bwPoint3 VrHinge::getAnchor() {
	bwReal pos[3] ;
	dJointGetHingeAnchor(m_jointID, pos) ;
	return bwPoint3(pos[0], pos[1], pos[2]) ;
}
void VrHinge::setJointERP(bwReal erp) {
	dJointSetHingeParam(m_jointID, dParamSuspensionERP, erp);
}
void VrHinge::setJointCFM(bwReal cfm) {
	dJointSetHingeParam(m_jointID, dParamSuspensionCFM, cfm);
}