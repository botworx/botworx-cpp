/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <bwvr/VrOdeCollision.h>
#include <bwvr/VrContact.h>

#include <bwvr/VrShapeCollider.h>
#include <bwvr/VrSurfaceInfo.h>
#include <bwvr/VrShape.h>
#include <bwvr/VrPhysics.h>
#include <bwvr/VrBody.h>
#include <bwvr/VrNode.h>
#include <bwvr/VrCollisionManager.h>

VrShapeCollider::VrShapeCollider(VrShape *pShape) : VrCollider(pShape) {
	p_shape = pShape ;
}
VrShapeCollider::~VrShapeCollider() {
}
VrCollisionRecord& VrShapeCollider::createCollision(VrNode* pCollider, VrNode *pCollidee) {
    return createOdeCollision(pCollider, pCollidee) ;
	/*nodeType nodeType1 = pCollider->getNodeType() ;
	switch(nodeType1) {
			case NODE_CYLINDER :
			case NODE_CONVEXMESH :
			case NODE_CONCAVEMESH :
			case NODE_HEIGHTFIELD : {
				nodeType nodeType2 = pCollidee->getNodeType() ;
				switch(nodeType2) {
					case NODE_CYLINDER :
					case NODE_CONVEXMESH :
					case NODE_CONCAVEMESH :
					case NODE_HEIGHTFIELD :
						return createBtCollision(pCollider, pCollidee) ;
					default :
						return createOdeCollision(pCollider, pCollidee) ;
				}
			}
		default :
			return createOdeCollision(pCollider, pCollidee) ;
	}*/
}
/*VrCollisionRecord& VrShapeCollider::createCollision(VrNode* pCollider, VrNode *pCollidee) {
	return createBtCollision(pCollider, pCollidee) ;
}*/
//
VrCollisionRecord& VrShapeCollider::createOdeCollision(VrNode* pCollider, VrNode *pCollidee) {
	m_collisions.push_back(VrCollisionRecord(COLLISION_ODE, pCollider, pCollidee, NULL)) ;
	return m_collisions.back() ;
}
//
void VrShapeCollider::computeContactSurfaceInfo(VrSurfaceInfo& surfaceInfo, VrShape *pShape1, VrShape *pShape2) {
	VrSurfaceInfo& surfaceInfo1 = pShape1->getSurfaceInfo() ;
	VrSurfaceInfo& surfaceInfo2 = pShape2->getSurfaceInfo() ;
	surfaceInfo.setMode(dContactBounce | dContactApprox1) ;
	surfaceInfo.setMu(surfaceInfo1.getMu() + surfaceInfo2.getMu()) ;
	surfaceInfo.setBounce(0.3f) ;
	surfaceInfo.setBounceVel(0.1f) ;
}
bool VrShapeCollider::canCollide(VrNode* pCollider, VrNode* pCollidee) {
	if(p_shape->getMotionType() == MOTION_STATIC)
		return true ;
	VrBody *pBody1 = p_shape->getBody() ;
	VrBody *pBody2 = pCollider->getCollider()->getModel()->getBody() ;
	if( ( pBody1 != NULL) && ( pBody2 != NULL) )
		if(pBody1 == pBody2)
			return false ;
	//else
	return !findCollision(pCollider, pCollidee) ;
}
void VrShapeCollider::processContact(VrCollisionRecord& record, VrSurfaceInfo& surfaceInfo, VrContact *contact) {
	VrCollider::processContact(record, surfaceInfo, contact) ;
	VrPhysics::singleton::get().processContact(record, surfaceInfo, contact) ;
}
int VrShapeCollider::processCollision(VrCollisionRecord& record) {
	switch(record.m_type) {
		case COLLISION_ODE :
			return processOdeCollision(record) ;
	}
	return 0 ;
}
int VrShapeCollider::processOdeCollision(VrCollisionRecord& record) {
	VrShape *pShape = static_cast<VrShape*>(record.p_collidee->getModel()) ;
	VrSurfaceInfo contactSurfaceInfo ;
	computeContactSurfaceInfo(contactSurfaceInfo, p_shape, pShape) ;

	dGeomID geomID1 = p_shape->getGeomID() ;
	dGeomID geomID2 = pShape->getGeomID() ;

	VrContact *contacts = VrCollisionManager::singleton::get().getContactBuffer() ;
	int n = dCollide(geomID1,geomID2,m_contactMax,&contacts[0].geom,sizeof(VrContact));
	if (n > 0) {
		for (int i = 0 ; i < n ; ++i) {
			processContact(record, contactSurfaceInfo, &contacts[i]) ;
		}
		VrCollider *pCollider = pShape->getCollider() ;
		onCollidee(pCollider) ;
		pCollider->onCollider(this) ;
	}
	return n ;
}