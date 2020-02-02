/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <bwvr/VrNode.h>
#include <bwvr/VrShape.h>
#include <bwvr/VrGroup.h>
#include <bwvr/VrNodeKit.h>
#include <bwvr/VrCollider.h>

VrNode::VrNode(VrModel *pModel) {
	p_model = pModel ;
	p_collider = NULL ;
	p_parent = NULL ;
	p_next = NULL ;
	p_child = NULL ;
	p_entity = NULL ;
	m_isEntity = false ;
	m_testInternal = true ;
	m_nodeType = NODE_BOX ;
	//
	m_isMigrant = true ;
	m_isMigrating = false ;
}
void VrNode::validate() {
	migrate() ;
}
void VrNode::fit() {
	if(p_child == NULL)
		return ;
	bwBounds3 worldBounds ;
	VrModel *pModel = NULL ;
	bwPoint3 centroid ;
	int childCount = 0 ;
	for(VrNode *pChild = p_child ; pChild != NULL ; pChild = pChild->p_next) {
		extendVolume(worldBounds, pChild->getBounds()) ;
		centroid = centroid + pChild->getPos() ;
		childCount++ ;
	}
	m_bounds = worldBounds ;
	setPos(
		centroid[0] / childCount,
		centroid[1] / childCount,
		centroid[2] / childCount) ;
}
void VrNode::attachNode(VrNode *pNode) {
	bwAssert(pNode != this) ;
	VrNode *pChild = p_child ;
	p_child = pNode ;
	pNode->p_parent = this ;
	pNode->p_next = pChild ;
	//
	if(isEntity())
		pNode->setEntity(this) ;
	else
		pNode->setEntity(p_entity) ;
}
void VrNode::detachNode(VrNode *pNode) {
	VrNode *pChild = p_child ;
	VrNode *pPrev = NULL ;
	bwAssert(pChild != NULL) ;

	if(pNode == pChild) {
		p_child = pChild->p_next ;
		pNode->p_parent = NULL ;
		pNode->p_next = NULL ;
		return ;
	}

	for( ; pChild != NULL ; ) {
		if(pChild == pNode)
			break ;
		pPrev = pChild ;
		pChild = pChild->p_next ;
	}
	bwAssert(pChild != NULL) ;
	if(pChild != NULL) {

		if(pPrev != NULL)
			pPrev->p_next = pChild->p_next ; //splice
		else
			p_child = NULL ;

		pNode->p_parent = NULL ;
		pNode->p_next = NULL ;

		return ;
	}
	bwAssert(0) ;
}
bool VrNode::testOverlap(VrNode *pNode) {
	if(pNode == this)
		return false ;
	//else
	if(pNode->p_entity == p_entity)
		if(!p_entity->testInternal())
			return false ;
	//else
	if(pNode->p_parent == this)
		if(!testInternal())
			return false ;
	//else
	if(pNode->p_parent == p_parent)
		if(!p_parent->testInternal())
			return false ;
	//else
	bool fContact = false ;

	switch(m_nodeType) {
		case NODE_RAY :
			fContact = testRay(pNode) ;
			break ;
		case NODE_LINESEG :
			fContact = testLineSeg(pNode) ;
			break ;
		case NODE_BOX :
			fContact = testBox(pNode) ;
			break ;
		case NODE_BALL :
			fContact = testBall(pNode) ;
			break ;
		case NODE_CONVEXMESH :
		case NODE_CONCAVEMESH :
			fContact = testMesh(pNode) ;
			break ;
		default :
			fContact = testBox(pNode) ;
			break ;
	}
	return fContact ;
}
void VrNode::processOverlap(VrNode *pNode) {
	bool fCanCollide = false ;
	if(p_collider != NULL) {
		fCanCollide = p_collider->canCollide(pNode, this) ;
	}
	if(fCanCollide)
		pNode->getCollider()->addCollisionPair(pNode, this) ;

	return ;
}
void VrNode::collide(VrNode *pNode, bool recursive) {
	bool fOverlap = testOverlap(pNode) ;
	if(!fOverlap)
		return ;
	//else
	processOverlap(pNode) ;
	if(recursive)
		for(VrNode *pChild = p_child ; pChild != NULL ; pChild = pChild->p_next) {
				pChild->collide(pNode) ;
		}
}
void VrNode::migrate() {
	if(!m_isMigrant)
		return ;
	//else
	if(!p_parent->testBoxInBox(this)) {
		VrNode* pRoot = p_model->getNodeKit()->getRoot() ;
		pRoot->host(this) ;
	}
}
void VrNode::host(VrNode* pMigrant) {
	if(!pMigrant->m_isMigrant)
		return ;
	if(!isPlace()) //ONLY PLACES CAN HOST
		return ;
	if(!testBoxInBox(pMigrant))
		return ;
	pMigrant->setIsMigrating(true) ;
	pMigrant->getModel()->p_futureGroup = static_cast<VrGroup*>(getModel()) ;
	//
	for(VrNode *pChild = p_child ; pChild != NULL ; pChild = pChild->p_next) {
			pChild->host(pMigrant) ;
	}
}
bwRay VrNode::getRay() {
	bwReal halfLength = m_radius ; //fixme to radius
	//TODO:must be better way via pose
	const bwQuat& quat = getQuat() ;
	bwPoint3 start = getPos() + quat * bwVector3(0, 0, halfLength) ;
	bwVector3 dir = quat * bwVector3(0, 0, -m_radius*2) ;
	bwRay ray(start, dir) ;
	return ray ;
}
bwLine VrNode::getLineSeg() {
	bwReal halfLength = m_radius ; //fixme to radius
	const bwQuat& quat = getQuat() ;
	bwPoint3 start = getPos() + quat * bwVector3(0, 0, halfLength) ;
	bwVector3 dir = quat * bwVector3(0, 0, -m_radius*2) ;
	bwLine seg(start, dir) ;
	return seg ;
}
bool VrNode::testSphereRay(VrNode *pNode) {
	bwRay ray = pNode->getRay() ;
	int numhits ; bwReal t0 ; bwReal t1 ;
	return gmtl::intersect(bwSphere(getPos(), m_radius), ray, numhits, t0, t1) ;
}
bool VrNode::testSphereLineSeg(VrNode *pNode) {
	bwLine seg = pNode->getLineSeg() ;
	int numhits ; bwReal t0 ; bwReal t1 ;
	//return gmtl::intersect(bwSphere(m_pos, m_radius), seg, numhits, t0, t1) ;
	//need intersectVolume to register hits when endpoints are inside sphere!!!
	return gmtl::intersectVolume(bwSphere(getPos(), m_radius), seg, numhits, t0, t1) ;
}
bool VrNode::testBoxRay(VrNode *pNode) {
	bwRay ray = pNode->getRay() ;
	unsigned int numhits ; bwReal t0 ; bwReal t1 ;
	return gmtl::intersect(m_bounds, ray, numhits, t0, t1) ;
}
bool VrNode::testBoxLineSeg(VrNode *pNode) {
	bwLine seg = pNode->getLineSeg() ;
	unsigned int numhits ; bwReal t0 ; bwReal t1 ;
	return gmtl::intersect(m_bounds, seg, numhits, t0, t1) ;
}
