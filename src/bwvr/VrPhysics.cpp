#include "stdafx.h"

#include <bwvr/VrPhysics.h>
#include <bwcore/BwStage.h>

#include <bwvr/VrCollision.h>
#include <bwvr/VrContact.h>
#include <bwvr/VrShape.h>
#include <bwvr/VrNode.h>

//Produced Types
#include <bwvr/VrRigidBody.h>
#include <bwvr/VrBallJoint.h>
#include <bwvr/VrHinge.h>
#include <bwvr/VrHinge2.h>
#include <bwvr/VrUniversal.h>

VrPhysics::VrPhysics(BwActor *pActor) : VrPhysicsBase(pActor) {
	// initalize the ODE world
	m_worldID = dWorldCreate();
	m_contactJointGroupID = dJointGroupCreate(0) ;
	dWorldSetGravity(m_worldID, m_gravity[0], m_gravity[1], m_gravity[2]);

	//dWorldSetAutoDisableFlag (m_worldID, 1);
	//dWorldSetAutoDisableTime(m_worldID, .01);
	//dWorldSetAutoDisableLinearThreshold (m_worldID, .015) ;
	//dWorldSetAutoDisableAngularThreshold (m_worldID, .008)
	//dWorldSetCFM (m_worldID,1e-5);
	//dWorldSetContactMaxCorrectingVel (m_worldID,0.1);
	//dWorldSetContactSurfaceLayer (m_worldID,0.001);
 }
/*************************************************
dReal dWorldGetAutoDisableLinearThreshold (dWorldID w)
void dWorldSetAutoDisableLinearThreshold (dWorldID w, dReal linear_threshold)
dReal dWorldGetAutoDisableAngularThreshold (dWorldID w)
void dWorldSetAutoDisableAngularThreshold (dWorldID w, dReal angular_threshold)
int dWorldGetAutoDisableSteps (dWorldID w)
void dWorldSetAutoDisableSteps (dWorldID w, int steps)
dReal dWorldGetAutoDisableTime (dWorldID w)
void dWorldSetAutoDisableTime (dWorldID w, dReal time)
int dWorldGetAutoDisableFlag (dWorldID w)
void dWorldSetAutoDisableFlag (dWorldID w, int do_auto_disable)
void dWorldSetQuickStepNumIterations (dWorldID w, int num)
int dWorldGetQuickStepNumIterations (dWorldID w)
void dWorldSetQuickStepW (dWorldID w, dReal param)
dReal dWorldGetQuickStepW (dWorldID w)
void dWorldSetContactMaxCorrectingVel (dWorldID w, dReal vel)
dReal dWorldGetContactMaxCorrectingVel (dWorldID w)
void dWorldSetContactSurfaceLayer (dWorldID w, dReal depth)
dReal dWorldGetContactSurfaceLayer (dWorldID w)
*************************************************/
VrPhysics::~VrPhysics() {
	dJointGroupDestroy(m_contactJointGroupID);
	dWorldDestroy(m_worldID);
}
bool VrPhysics::onPostStep(BwStepper& stepper) {
	dJointGroupEmpty(m_contactJointGroupID);
	return VrPhysicsBase::onPostStep(stepper) ;
}
//Factory Methods
VrBody* VrPhysics::createBody(VrModel* pModel) {
	VrRigidBody* pBody = new VrRigidBody(pModel) ;
	pBody->create() ;
	return pBody ;
}
VrJoint* VrPhysics::createJoint(jointType type, VrGroup* pGroup) {
	VrJoint* pJoint = NULL ;
	switch(type) {
		case JOINT_BALL :
			pJoint = new VrBallJoint(pGroup) ;
			break ;
		case JOINT_HINGE :
			pJoint = new VrHinge(pGroup) ;
			break ;
		case JOINT_HINGE2 :
			pJoint = new VrHinge2(pGroup) ;
			break ;
		case JOINT_UNIVERSAL :
			pJoint = new VrUniversal(pGroup) ;
			break ;
	}
	if(pJoint != NULL)
		pJoint->create() ;

	return pJoint ;
}
void VrPhysics::processContact(VrCollisionRecord& record, VrSurfaceInfo& contactSurfaceInfo, VrContact *contact) {

	VrRigidBody *pBody1 = static_cast<VrRigidBody*>(static_cast<VrShape*>(record.collider().getModel())->getBody()) ;
	VrRigidBody *pBody2 = static_cast<VrRigidBody*>(static_cast<VrShape*>(record.collidee().getModel())->getBody()) ;
	dBodyID pBodyID1 = NULL ;
	dBodyID pBodyID2 = NULL ;

	if(pBody1 != NULL)
		pBodyID1 = pBody1->getBodyID() ;
	if(pBody2 != NULL)
		pBodyID2 = pBody2->getBodyID() ;

	int mode = contactSurfaceInfo.getMode() ;
	contact->surface.mode = mode ;
	contact->surface.mu = contactSurfaceInfo.getMuAdjusted() ;
	contact->surface.mu2 = contactSurfaceInfo.getSecondMuAdjusted() ;
	contact->surface.bounce = contactSurfaceInfo.getBounce() ;
	contact->surface.bounce_vel = contactSurfaceInfo.getBounceVel() ;

	if(mode & dContactFDir1) {
		bwVector3 fdir1 = contactSurfaceInfo.getFirstFrictionDir() ;
		contact->fdir1[0] = fdir1[0] ;
		contact->fdir1[1] = fdir1[1] ;
		contact->fdir1[2] = fdir1[2] ;
	}

	dJointID c = dJointCreateContact(getWorldID(), m_contactJointGroupID, contact) ;
	dJointAttach (c, pBodyID1, pBodyID2);
}

template<> VrPhysics* VrPhysics::singleton::g_singleton = 0 ;