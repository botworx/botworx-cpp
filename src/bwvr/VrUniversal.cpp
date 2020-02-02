/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <bwvr/VrUniversal.h>
#include <bwvr/VrPhysics.h>
#include <bwvr/VrRigidBody.h>

VrUniversal::VrUniversal(VrGroup *pGroup) 
: VrJoint(pGroup), m_rod_1(NULL), m_rod_2(NULL)	{
}
VrUniversal::~VrUniversal() {
}
void VrUniversal::doCreate(const BwPartInfo& info) {
	VrJoint::doCreate(info) ;
	m_jointID = dJointCreateUniversal(VrPhysics::singleton::get().getWorldID(), NULL);
	m_rod_1.create(this) ;
	m_rod_2.create(this) ;
}
/*Rod1*/
void VrUniversalRod1::setAxis(bwReal x, bwReal y, bwReal z){
	bwVector3 axis = p_joint->getQuat() * bwVector3(x, y, z) ;
	dJointSetUniversalAxis1(getJoint().getJointID(), axis[0], axis[1], axis[2]);
}
bwReal VrUniversalRod1::getAngle(){
	return dJointGetUniversalAngle1(getJoint().getJointID()) ;
}
void VrUniversalRod1::setLoStop(bwReal loStop) {
	dJointSetUniversalParam(getJoint().getJointID(), dParamLoStop, loStop);
}
void VrUniversalRod1::setHiStop(bwReal hiStop) {
	dJointSetUniversalParam(getJoint().getJointID(), dParamHiStop, hiStop);
}
void VrUniversalRod1::setVelocity(bwReal value){
	dJointSetUniversalParam(getJoint().getJointID(), dParamVel, value);	
}
void VrUniversalRod1::setForceMax(bwReal value){
	dJointSetUniversalParam(getJoint().getJointID(), dParamFMax, value);
}
/*Rod2*/
void VrUniversalRod2::setAxis(bwReal x, bwReal y, bwReal z){
	bwVector3 axis = p_joint->getQuat() * bwVector3(x, y, z) ;
	dJointSetUniversalAxis2(getJoint().getJointID(), axis[0], axis[1], axis[2]);
}
bwReal VrUniversalRod2::getAngle(){
	return dJointGetUniversalAngle2(getJoint().getJointID()) ;
}
void VrUniversalRod2::setLoStop(bwReal loStop) {
	dJointSetUniversalParam(getJoint().getJointID(), dParamLoStop2, loStop);
}
void VrUniversalRod2::setHiStop(bwReal hiStop) {
	dJointSetUniversalParam(getJoint().getJointID(), dParamHiStop2, hiStop);
}
void VrUniversalRod2::setVelocity(bwReal value){
	dJointSetUniversalParam(getJoint().getJointID(), dParamVel2, value);	
}
void VrUniversalRod2::setForceMax(bwReal value){
	dJointSetUniversalParam(getJoint().getJointID(), dParamFMax2, value);
}
void VrUniversal::setAnchor(const bwPoint3& pos) {
	dJointSetUniversalAnchor(m_jointID, pos[0], pos[1], pos[2]) ;
}
bwPoint3 VrUniversal::getAnchor() {
	bwReal pos[3] ;
	dJointGetUniversalAnchor(m_jointID, pos) ;
	return bwPoint3(pos[0], pos[1], pos[2]) ;
}
void VrUniversal::setJointERP(bwReal erp) {
	dJointSetUniversalParam(m_jointID, dParamSuspensionERP, erp);
}
void VrUniversal::setJointCFM(bwReal cfm) {
	dJointSetUniversalParam(m_jointID, dParamSuspensionCFM, cfm);
}