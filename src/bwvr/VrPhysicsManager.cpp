/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <bwvr/VrPhysicsManager.h>
#include <bwvr/VrQuickPhysics.h>
#include <bwvr/VrStablePhysics.h>
#include <bwvr/VrScenario.h>

VrPhysicsManager::VrPhysicsManager(BwPart *pPart) : BwSystem(pPart) {
}
void VrPhysicsManager::doCreate(const BwPartInfo& info) {
	BwSystem::doCreate(info) ;
	dInitODE2(0);
}
VrPhysics* VrPhysicsManager::createPhysics(physicsType type) {
	VrPhysics* pPhysics = NULL ;
	switch(type) {
		case PHYSICS_ODE_QUICK :
			pPhysics = new VrQuickPhysics(VrScenario::singleton::getPtr()) ;
			break ;
		case PHYSICS_ODE_STABLE :
			pPhysics = new VrStablePhysics(VrScenario::singleton::getPtr()) ;
			break ;
	}
	if(pPhysics != NULL)
		pPhysics->create() ;
	return pPhysics ;
}
//Singleton support
template<> VrPhysicsManager::singleton::pointer VrPhysicsManager::singleton::g_singleton = 0 ;
