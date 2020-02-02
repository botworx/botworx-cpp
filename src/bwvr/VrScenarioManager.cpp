/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <bwvr/VrScenarioManager.h>
#include <bwvr/VrSystem.h>
#include <bwvr/VrApplet.h>

VrScenarioManager::VrScenarioManager(BwPart *pParent) : BwKit(pParent) {
}
void VrScenarioManager::addFactory(VrScenarioFactory *pFactory) {
	m_factories.push_back(pFactory) ;
	m_factoryMap[pFactory->getName()] = pFactory ; 
}
VrScenarioFactory* VrScenarioManager::findFactory(const bwString &name) {
	return m_factoryMap[name] ;
}
//Singleton support
template<> VrScenarioManager::singleton::pointer VrScenarioManager::singleton::g_singleton = 0 ;
//
VrScenarioManager* VrScenarioManager::singleton_alloc::alloc() { 
	VrScenarioManager* pPart = new VrScenarioManager(VrSystem::singleton::getPtr()) ;
	pPart->createEnabled() ;
	//TODO:kitstuff
	VrSystem::singleton::get().addKit(pPart) ;
	return pPart ;
}