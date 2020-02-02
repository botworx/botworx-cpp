/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <bwvr/VrHand.h>
#include <bwvr/VrGrip.h>
#include <bwvr/VrBuilder.h>
#include <bwvr/VrVu.h>
#include <bwvr/VrShapeCollider.h>
#include <bwvr/VrOdeCollision.h>
#include <bwvr/VrBody.h>
#include <bwvr/VrBallJoint.h>
#include <bwvr/VrPhysics.h>
#include <bwvr/VrPlace.h>
#include <bwvr/VrContact.h>
#include <bwvr/VrNode.h>
#include <bwvr/VrCollisionManager.h>
#include <bwvr/VrModelOps.h>

class VrHandCollider : public VrShapeCollider {
public:
	VrHandCollider(VrHand *pHand) : VrShapeCollider(pHand) {
		p_hand = pHand ;
	}
	virtual int processOdeCollision(VrCollisionRecord& record) ;
	virtual bool canCollide(VrNode* pCollider, VrNode* pCollidee) { return false ; }
	virtual void addCollisionPair(VrNode *pCollider, VrNode *pCollidee) ;
	//
	VrHand *p_hand ;
};
VrHand::VrHand(VrGroup *pGroup) : VrBall(pGroup) {
	setNodeType(NODE_BALL) ;
	m_isAutoSleeper = false ;
	setMotionType(MOTION_KINEMATIC) ;
	setMaxSize(bwSize3(5,5,5)) ;
	vuInfo().setMeshName("VrHand.mesh") ;

	m_motionMode = FOLLOW_LOOK ;
	m_modeSwitchTimer.setAlarm(std::chrono::seconds(1)) ;
	m_followDistance = 6 ;
	m_followHeight = 0 ;
	//
	m_grabMode = GM_NONE ;
	p_grip = NULL ;
}
void VrHand::createCollider() {
	p_collider = new VrHandCollider(this) ;
}
void VrHand::doStep(BwStepper& stepper) {
	VrBall::doStep(stepper) ;
	bwDT deltaTime = VrPhysics::singleton::get().getDeltaTime() ;
	VrModel* pLeader = getLeader() ;
	if(pLeader == NULL)
		return ;
	bwVector3 focusPos = getLeader()->getPos() ;
	bwMatrix3x3 r ;
	bwQuat quat ;
	bwQuat followQuat ;

	if(p_grip != NULL)
		//p_grip->doStep(stepper) ;
		p_grip->invokeStep(stepper) ;

	switch(m_motionMode) {
		case FOLLOW_FOLLOW :
			quat = getLeader()->getQuat() ;
			break ;
		case FOLLOW_LOOK :
			quat = getLeader()->getQuat() * m_followQuat ;
			break ;
		case LOOK_FOLLOW :
		case LOOK_LOOK :
			quat = m_followQuat ;
			break ;
	}

	gmtl::setRot(r, quat) ;

	bwVector3 worldVector = vectorToWorld(r, 0, 0, 1) ;
	bwVector3 desiredPos( focusPos[0] + worldVector[0] * m_followDistance,
						focusPos[1] + worldVector[1] * m_followDistance + m_followHeight, 
						focusPos[2] + worldVector[2] * m_followDistance) ;

	bwPoint3 handPos = getPos() + (bwReal(4 * deltaTime) * (desiredPos - getPos()) );

	if(m_motionMode != LOOK_LOOK)
		setPos(handPos) ;
	setQuat(quat) ;
}
bool VrHand::onPostStep(BwStepper& stepper) {
	if(p_grip != NULL) {
		if(m_grabMode == GM_NONE)
			release() ;
		else
			p_grip->invokePostStep(stepper) ;
	}
	return VrBall::onPostStep(stepper) ;
}
void VrHand::grabShape(VrShape *pShape, const bwPoint3& pos) {
	if(p_grip != NULL)
		return ;
	if(!pShape->isPlaceable())
		return ;
	switch(pShape->getMotionType()) {
		case MOTION_DYNAMIC :
		case MOTION_FIXED :
			p_grip = new VrDynamicGrip(this, pShape) ;
			break ;
		default :
			p_grip = new VrStaticGrip(this, pShape) ;
	}
	p_grip->grab(pos) ;
}
void VrHand::release() {
	p_grip->release() ;
	delete p_grip ;
	p_grip = NULL ;
}
VrModel* VrHand::build(const bwString& name, const bwPose& pose, bool sleeping) {
	VrModel* pModel = VrBuilder::singleton::get().build(name, p_group, sleeping) ;
	pModel->setPos(getPos() + pose.getPos()) ;
	pModel->setQuat(getQuat() * pose.getQuat()) ;
	return pModel ;
}
VrModel* VrHand::buildEnabled(const bwString& name, const bwPose& pose, bool sleeping) {
	VrModel* pModel = build(name, pose, sleeping) ;
	pModel->config() ;
	pModel->enable(sleeping) ;
	return pModel ;
}
/*****************************/
void VrHandCollider::addCollisionPair(VrNode* pCollider, VrNode* pCollidee) {
	if(p_hand->getGrabMode() == VrHand::GM_NONE)
		return ;
	if(p_hand->p_grip != NULL)
		return ;
	//else
	VrCollider::addCollisionPair(pCollider, pCollidee) ;
}
int VrHandCollider::processOdeCollision(VrCollisionRecord& record) {
	if(p_hand->getGrabMode() == VrHand::GM_NONE)
		return 0 ;
	if(p_hand->p_grip != NULL)
		return 0 ;

	VrShape *pShape = static_cast<VrShape*>(record.p_collidee->getModel()) ;
	dGeomID geomID1 = p_shape->getGeomID() ;
	dGeomID geomID2 = pShape->getGeomID() ;

	VrContact *contacts = VrCollisionManager::singleton::get().getContactBuffer() ;
	int n = dCollide(geomID1, geomID2, m_contactMax, &contacts[0].geom, sizeof(VrContact));

	if (n > 0) {
		bwPoint3 point = contacts[0].getPos();
		p_hand->grabShape(pShape, point) ;
		VrCollider *pCollider = pShape->getCollider() ;
		onCollidee(pCollider) ;
		pCollider->onCollider(this) ;
	}
	return n ;
}