/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <bwvr/VrPoser.h>
#include <bwvr/VrModel.h>
#include <bwvr/VrModelOps.h>

VrPoser::VrPoser(VrModel* pModel) : BwActor(pModel) {
	setIsStageDriven(false) ; //manually stepped by VrModel.
	p_model = pModel ;
}
void VrPoser::doStep(BwStepper& stepper) {
}
bool VrPoser::onPostStep(BwStepper& stepper) {
	return true ;
}
void VrPoser::setQuat(const bwQuat& quat) { 
	m_quat = quat ; 
}
//
void VrPoser::jump() {
	m_isJumping = true ;
	bwPoint3 pos = getPos() ;
	pos[1] += .1f ;
	setPos(pos) ;
}
void VrPoser::jumpNone() {
	m_isJumping = false ;
}
void VrPoser::move(bwReal dist) {
	setPos(getPos() + (( makeNormal(getQuat()) * bwVector3(0,0,1) ) * dist)) ;
}
void VrPoser::moveNone() {
}
void VrPoser::moveForward(bwReal dist) {
	move(dist) ;
}
void VrPoser::moveReverse(bwReal dist) {
	move(-dist) ;
}
void VrPoser::turnLeft(bwReal degree) {
	yaw(degree) ;
}
void VrPoser::turnRight(bwReal degree) {
	yaw(-degree) ;
}
void VrPoser::pitchUp(bwReal degree) {
	pitch(degree) ;
}
void VrPoser::pitchDown(bwReal degree) {
	pitch(-degree) ;
}
void VrPoser::rollLeft(bwReal degree) {
	roll(degree) ;
}
void VrPoser::rollRight(bwReal degree) {
	roll(-degree) ;
}
void VrPoser::pitch(bwReal angle) {
	rotate(bwAxisAngle(angle, makeNormal(getQuat()) * bwVector3(-1,0,0))) ;
}
void VrPoser::roll(bwReal angle) {
	rotate(bwAxisAngle(angle, makeNormal(getQuat()) * bwVector3(0,0,-1))) ;
}
void VrPoser::yaw(bwReal angle) {
	//rotate(bwAxisAngle(angle, m_quat * bwVector3(0,1,0))) ;
	rotate(bwAxisAngle(angle, bwVector3(0,1,0))) ;
}
void VrPoser::rotate(const bwAxisAngle& axisAngle) {
	bwQuat q ;
	set(q, axisAngle) ;
	//normalize(q) ;
	setQuat(q * m_quat) ;
}