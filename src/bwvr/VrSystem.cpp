/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <bwvr/VrSystem.h>

#include <bwvr/VrPhysicsManager.h>
#include <bwvr/VrPhysics.h>

VrSystem::VrSystem(BwPart *pPart) : BwSystem(pPart) {
}
void VrSystem::doCreate(const BwPartInfo& info) {
	BwSystem::doCreate(info) ;
}
VrPhysics* VrSystem::createPhysics(physicsType type, bool enabled) {
	VrPhysics* pPhysics = VrPhysicsManager::singleton::get().createPhysics(type) ;
	bwAssert(pPhysics) ;
	if(pPhysics != NULL) {
		if(enabled) {
			pPhysics->config() ;
			pPhysics->enable() ;
		}
	}
	return pPhysics ;
}
//Singleton support
template<> VrSystem::singleton::pointer VrSystem::singleton::g_singleton = 0 ;
