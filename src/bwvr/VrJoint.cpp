/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <bwvr/VrJoint.h>
#include <bwvr/VrRigidBody.h>

VrJoint::VrJoint(VrGroup *pGroup) : VrJointBase(pGroup) {
	m_jointID = NULL ;
}
VrJoint::~VrJoint() {
}
void VrJoint::doEnable(bool sleeping) {
	VrRigidBody *pBody1 = NULL ;
	VrRigidBody *pBody2 = NULL ;

	if(p_model_1 != NULL)
		pBody1 = dynamic_cast<VrRigidBody*>(p_model_1->getBody()) ;
	if(p_model_2 != NULL)
		pBody2 = dynamic_cast<VrRigidBody*>(p_model_2->getBody()) ;

	dBodyID pBodyID1 = NULL ;
	dBodyID pBodyID2 = NULL ;

	if(pBody1 != NULL)
		pBodyID1 = pBody1->getBodyID() ;
	if(pBody2 != NULL)
		pBodyID2 = pBody2->getBodyID() ;

	if(!sleeping) {
		dJointAttach(m_jointID, pBodyID1, pBodyID2);
		setAnchor(getPos()) ;
	}
	VrJointBase::doEnable(sleeping) ;
}
void VrJoint::doDisable(bool sleeping) {
	if(sleeping)
		dJointAttach(m_jointID, NULL, NULL);
	else
		dJointDestroy(m_jointID);
	VrJointBase::doDisable(sleeping) ;
}
////////////
void VrJoint::createDynamicLay() {
	// VrJointLay jointLay ;
	// jointLay.clone(m_lay) ;
	// setLay(jointLay) ;
	// TODO: What a code smell we have here!
	setLay(std::move(VrJointLay().clone(m_lay)));
}
VrJoint& VrJointLay::getJoint() { 
	VrJoint *pJoint = ((VrJoint*)((bwByte*)this - offsetof(VrModel, m_lay))) ;
	return *pJoint ;
}
void VrJointLay::validate() {
	_setPos(getJoint().getAnchor()) ;
	_setQuat(model().getQuat()) ;
	return VrAbsLay::validate() ;
}