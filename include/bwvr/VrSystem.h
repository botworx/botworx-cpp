/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _VrSystem_H
#define _VrSystem_H

#include <bwcore/BwSystem.h>

class VrPhysicsManager ;
class VrPhysics ;

class VrSystem : public BwSystem {
public:
	VrSystem(BwPart *pPart) ;
	virtual void doCreate(const BwPartInfo& info) ;
	VrPhysics* createPhysics(physicsType type = PHYSICS_DEFAULT, bool enabled = true) ;
	//Singleton support
public:
	typedef BwSingletonT<VrSystem> singleton ;
	singleton m_singleton ;
} ;

#endif //_VrSystem_H