/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _VrPhysicsManager_H
#define _VrPhysicsManager_H

#include <bwcore/BwSystem.h>

class VrPhysics ;

class VrPhysicsManager : public BwSystem {
public:
	VrPhysicsManager(BwPart *pPart) ;
	virtual void doCreate(const BwPartInfo& info) ;
	virtual VrPhysics* createPhysics(physicsType type) ;
	//
	typedef BwSingletonT<VrPhysicsManager> singleton ;
	singleton m_singleton ;
} ;

#endif //_VrPhysicsManager_H