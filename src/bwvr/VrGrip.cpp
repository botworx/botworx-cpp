/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <bwvr/VrGrip.h>
#include <bwvr/VrVu.h>
#include <bwvr/VrShapeCollider.h>
#include <bwvr/VrOdeCollision.h>
#include <bwvr/VrBody.h>
#include <bwvr/VrBallJoint.h>
#include <bwvr/VrPhysics.h>
#include <bwvr/VrPlace.h>

void VrDynamicGrip::grab(const bwPoint3& pos) {
	VrShapeGrip::grab(pos) ;
	p_grippee->touch(p_gripper) ;
	//TODO:we are extending ODE's dMass struct, and .mass = our .invMass ... either wrap or ..?
	m_power = p_grippee->getBody()->bodyInfo().getMass() * bwReal(10) ; //TODO: may want to change 10 to a constant variable?

	p_grabJoint = VrPhysics::singleton::get().createJoint(JOINT_BALL, p_gripper->getPlace()) ;

	p_grabModel = new VrModel(p_gripper->getPlace()) ;
	p_grabModel->setMotionType(MOTION_DYNAMIC) ;
	p_grabModel->createEnabled() ;

	//p_grabModel->createBody() ;
	p_grabBody = p_grabModel->getBody() ;
	p_grabBody->setGravityMode(0) ;
	//
	p_grabJoint->setPos(pos) ;
	p_grabBody->setPos(pos) ;
	//p_grabJoint->attachModels(pShape, p_grabModel) ;
	p_grabJoint->attachModels(p_grippee, p_grabModel) ;
	p_grabJoint->enable() ;
}
void VrDynamicGrip::doStep(BwStepper& stepper) {
	p_grippee->touch(p_gripper) ;
	//bwVector3 force = (p_grabBody->getPos() - p_gripper->getPos()) * (p_grippee->getBody()->m_mass.mass * 10) ;
	bwVector3 force = (p_gripper->getPos() - p_grabBody->getPos()) * m_power ;
	p_grabBody->addForce(force) ;
}
void VrDynamicGrip::release() {
	p_grabJoint->die() ;
	p_grabJoint = NULL ;
	p_grabModel->die() ;
	p_grabModel = NULL ;
	p_grippee = NULL ;
}
void VrStaticGrip::grab(const bwPoint3& pos) {
	VrGrip::grab(pos) ;
	m_oldPos = p_grippee->getPos() ;
	m_offset = m_oldPos - pos ;
}
void VrStaticGrip::doStep(BwStepper& stepper) {
	bwPoint3 oldPos = m_oldPos ;
	m_oldPos = p_grippee->getPos() ;
	p_grippee->setPos(p_gripper->getPos() + m_offset) ;
	p_grippee->setQuat(p_gripper->getQuat()) ;
	p_grippee->invokeStep(stepper) ;
}
void VrStaticGrip::doPostStep(BwStepper& stepper) {
	p_grippee->invokePostStep(stepper) ;
}