/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <bwvr/VrBallJoint.h>
#include <bwvr/VrPhysics.h>

VrBallJoint::VrBallJoint(VrGroup *pGroup) : VrJoint(pGroup)	{
}
VrBallJoint::~VrBallJoint() {
}
void VrBallJoint::doCreate(const BwPartInfo& info) {
	VrJoint::doCreate(info) ;
	m_jointID = dJointCreateBall(VrPhysics::singleton::get().getWorldID(), NULL) ;
}
void VrBallJoint::setAnchor(const bwPoint3& pos) {
	dJointSetBallAnchor(m_jointID, pos[0], pos[1], pos[2]) ;
}
bwPoint3 VrBallJoint::getAnchor() {
	bwReal pos[3] ;
	dJointGetBallAnchor(m_jointID, pos) ;
	return bwPoint3(pos[0], pos[1], pos[2]) ;
}