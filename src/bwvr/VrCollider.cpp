/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <bwvr/VrCollider.h>
#include <bwvr/VrCollision.h>
#include <bwvr/VrCollisionManager.h>
#include <bwvr/VrContactListener.h>
#include <bwvr/VrShape.h>
#include <bwvr/VrPhysics.h>
#include <bwvr/VrBody.h>
#include <bwvr/VrNode.h>
#include <bwvr/VrNodeKit.h>
#include <bwvr/VrGroup.h>

VrCollider::VrCollider(VrModel *pModel) {
	p_model = pModel ;
	m_isColliding = false ;
	m_isContacting = false  ;
	m_contactMax = MAXCONTACTS ; //need to call setContactMax before calling init!
	p_listener = NULL ;
}
VrCollider::~VrCollider() {
}
VrCollisionRecord& VrCollider::createCollision(VrNode* pCollider, VrNode* pCollidee) { 
	m_collisions.push_back(VrCollisionRecord(COLLISION_NULL, pCollider, pCollidee, NULL)) ;
	return m_collisions.back() ;
}
void VrCollider::collide(VrNodeKit *pNodeKit, VrNode* pNode) {
	m_isContacting = false ;
	m_isColliding = false ;
	if(p_listener != NULL)
		p_listener->clear() ;
	pNodeKit->collide(pNode) ;
	processCollisions() ;
}
void VrCollider::addCollisionPair(VrNode *pCollider, VrNode *pCollidee) {
	if(!m_isColliding) {
		m_isColliding = true ;
	}
	VrCollisionRecord& record = cacheCollision(pCollider, pCollidee) ;
}
void VrCollider::processCollisions() {
	if(m_collisions.empty())
		return ;
	VrNode* pCollider = NULL ;
	VrNode* pCollidee = NULL ;
	VrCollision *pCollision = NULL ;
	for(VrCollisionRecordIter iter = m_collisions.begin(); iter != m_collisions.end() ;)	{
		VrCollisionRecord& record = *iter ;
		if(record.m_touched) {
			record.m_hits = processCollision(record) ;
			record.m_touched = false ;
			++iter ;
		}
		else {
			if(--record.m_counter == 0) {
				destroyCollision(record) ;
				m_collisions.erase(iter++) ;
			}
			else {
				record.m_touched = false ;
				++iter ;
			}
		}
	}
}
void VrCollider::processContact(VrCollisionRecord& record, VrSurfaceInfo& surfaceInfo, VrContact *contact) {
	if(p_listener != NULL)
		p_listener->onContact(record.pair(), surfaceInfo, contact) ;
}
void VrCollider::onCollidee(VrCollider *pCollider) {
	onCollision(pCollider) ;
}
void VrCollider::onCollider(VrCollider *pCollider) {
	if(pCollider->getModel() == NULL)
		return ;
	//else
	p_model->touch(pCollider->getModel()) ;
	onCollision(pCollider) ;
}
void VrCollider::onCollision(VrCollider *pCollider) {
	m_isContacting = true ;
}
bool VrCollider::findCollision(VrNode* pCollider, VrNode* pCollidee) {
	for(VrCollisionRecordIter iter = m_collisions.begin() ; iter != m_collisions.end() ; ++iter) {
		if(iter->p_collidee != pCollidee)
			continue ;
		if(iter->p_collider == pCollider)
			return true ;
	}
	return false ;
}
void VrCollider::destroyCollision(VrCollisionRecord& record) {
		VrCollision *pCollision = record.p_collision ;
		if(pCollision != NULL)
			VrCollisionManager::singleton::get().destroyCollision(pCollision) ;
		void *pInner = record.p_inner ;
		if(pInner != NULL)
			VrPhysics::singleton::get().releaseInnerCollision(pInner) ;
}
VrCollisionRecord& VrCollider::cacheCollision(VrNode* pCollider, VrNode* pCollidee) {
	VrCollisionRecordIter iter ;
	for(iter = m_collisions.begin() ; iter != m_collisions.end() ; ++iter) {
		if(iter->p_collidee != pCollidee)
			continue ;
		if(iter->p_collider == pCollider) {
			break ;
		}
	}
	if(iter != m_collisions.end()) {
		iter->touch() ;
	}
	else {
		return createCollision(pCollider, pCollidee) ;
	}
	return *iter ;
}