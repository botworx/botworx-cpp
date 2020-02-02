/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <buggybots/BbKernel.h>

#include <bwvr/VrSystem.h>
#include <bwvr/VrPhysicsManager.h>

//
//BbKernel
//
BbKernel::BbKernel() : BwKernel() {
}
void BbKernel::doCreate(const BwPartInfo& info) {
	BwKernel::doCreate(info) ;
	//Essential SubSystem creation
	VrSystem* pVr = new VrSystem(this) ;
	pVr->create() ;
	VrPhysicsManager* pPhysicsMgr = new VrPhysicsManager(pVr) ;
	pPhysicsMgr->create() ;
}
//Singleton support
void BbKernel::startup() {
	BbKernel* pKernel = new BbKernel() ;
	pKernel->create() ;
	pKernel->configAndEnable() ;
}
