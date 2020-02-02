/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <bwvr/VrHinge2.h>
#include <bwvr/VrPhysics.h>
#include <bwvr/VrRigidBody.h>
#include <bwvr/VrGroup.h>

VrHinge2::VrHinge2(VrGroup *pGroup) 
	: VrJoint(pGroup), m_rod_1(NULL), m_rod_2(NULL)	{
}
VrHinge2::~VrHinge2() {
}
void VrHinge2::doCreate(const BwPartInfo& info) {
	VrJoint::doCreate(info) ;
	m_jointID = dJointCreateHinge2(VrPhysics::singleton::get().getWorldID(), NULL);
	m_rod_1.create(this) ;
	m_rod_2.create(this) ;
}
void VrHinge2::setAnchor(const bwPoint3& pos) {
	dJointSetHinge2Anchor(m_jointID, pos[0], pos[1], pos[2]) ;
}
bwPoint3 VrHinge2::getAnchor() {
	bwReal pos[3] ;
	dJointGetHinge2Anchor(m_jointID, pos) ;
	return bwPoint3(pos[0], pos[1], pos[2]) ;
}
void VrHinge2::setJointERP(bwReal erp) {
	dJointSetHinge2Param(m_jointID, dParamSuspensionERP, erp);
}
void VrHinge2::setJointCFM(bwReal cfm) {
	dJointSetHinge2Param(m_jointID, dParamSuspensionCFM, cfm);
}
/*Rod1*/
void VrHinge2Rod1::setAxis(bwReal x, bwReal y, bwReal z){
	bwVector3 axis = p_joint->getQuat() * bwVector3(x, y, z) ;
	dJointSetHinge2Axis1(getJoint().getJointID(), axis[0], axis[1], axis[2]);
}
bwReal VrHinge2Rod1::getAngle(){
	return dJointGetHinge2Angle1(getJoint().getJointID()) ;
}

void VrHinge2Rod1::setLoStop(bwReal loStop) {
	dJointSetHinge2Param(getJoint().getJointID(), dParamLoStop, loStop);
}
void VrHinge2Rod1::setHiStop(bwReal hiStop) {
	dJointSetHinge2Param(getJoint().getJointID(), dParamHiStop, hiStop);
}
/*Rod2*/
void VrHinge2Rod2::setAxis(bwReal x, bwReal y, bwReal z){
	bwVector3 axis = p_joint->getQuat() * bwVector3(x, y, z) ;
	dJointSetHinge2Axis2(getJoint().getJointID(), axis[0], axis[1], axis[2]);
}
bwReal VrHinge2Rod2::getAngle(){
	return dJointGetHinge2Angle1(getJoint().getJointID()) ;
}
void VrHinge2Rod2::setVelocity(bwReal value){
	dJointSetHinge2Param(getJoint().getJointID(), dParamVel2, value);	
}
void VrHinge2Rod2::setForceMax(bwReal value){
	dJointSetHinge2Param(getJoint().getJointID(), dParamFMax2, value);
}