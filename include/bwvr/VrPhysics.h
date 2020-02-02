/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _VrPhysics_H
#define _VrPhysics_H

#include <bwvr/VrPhysicsBase.h>

class VrScenario ;
class VrCollider ;
class VrCollision ;
class VrCollisionKit ;
struct VrContact ;
class VrSurfaceInfo ;
//
//VrPhysics
//
class VrPhysics : public VrPhysicsBase {
public:
	VrPhysics(BwActor *pActor) ;
	virtual ~VrPhysics();
	virtual bool onPostStep(BwStepper& stepper) ;
	//Factory Methods
	virtual VrBody* createBody(VrModel* pModel) ;
	virtual VrJoint* createJoint(jointType type, VrGroup* pGroup) ;
public:
	dWorldID getWorldID() { return m_worldID ; }
	virtual void processContact(VrCollisionRecord& record, VrSurfaceInfo& contactSurfaceInfo, VrContact *pContact) ;
	//
	typedef BwSingletonT<VrPhysics> singleton ;
	singleton m_singleton ;
protected:
	//
	dWorldID m_worldID ;
	dJointGroupID m_contactJointGroupID ;
};

#endif //_VrPhysics_H


