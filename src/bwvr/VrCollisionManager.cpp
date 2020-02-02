/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <bwvr/VrCollisionManager.h>
#include <bwvr/VrSystem.h>
#include <bwvr/VrApplet.h>

#include <bwvr/VrOdeCollision.h>
#include <bwvr/VrContact.h>

VrCollisionManager::VrCollisionManager(BwPart *pParent) : BwSystem(pParent) {
	p_contacts = NULL ;
	m_contactMax = MAXCONTACTS ; //need to call setContactMax before calling init!
	//TODO:newstuff
	p_odeCollisionKit = new VrOdeCollisionKit(this) ;
	p_odeCollisionKit->create() ;
}
void VrCollisionManager::doCreate(const BwPartInfo& info) {
	BwSystem::doCreate(info) ;
	createContactBuffer() ;
}
void VrCollisionManager::createContactBuffer() {
	p_contacts = static_cast<VrContact*>(new VrContact[m_contactMax]) ;
}
VrCollision* VrCollisionManager::createCollision(collisionType type) {
	switch(type) {
		case COLLISION_ODE :
			return p_odeCollisionKit->createCollision() ;
	}
	return NULL ;
}
void VrCollisionManager::destroyCollision(VrCollision* pCollision) {
	collisionType type = pCollision->m_type ;
	switch(type) {
		case COLLISION_ODE :
			return p_odeCollisionKit->destroyCollision(pCollision) ;
	}
}
//Singleton support
template<> VrCollisionManager::singleton::pointer VrCollisionManager::singleton::g_singleton = 0 ;
//
VrCollisionManager* VrCollisionManager::singleton_alloc::alloc() { 
	VrCollisionManager* pPart = new VrCollisionManager(VrSystem::singleton::getPtr()) ;
	pPart->createEnabled() ;
	//TODO:kitstuff
	VrSystem::singleton::get().addKit(pPart) ;
	return pPart ;
}