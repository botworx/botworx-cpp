/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _VrShapeCollider_H
#define _VrShapeCollider_H

#include "VrCollider.h"
#include "VrShape.h"

class VrWorld ;
class VrShape ;
class VrPhysics ;
class VrSurfaceInfo ;
class VrOdeCollision ;
//
//VrShapeCollider
//
class VrShapeCollider : public VrCollider {
public:
	VrShapeCollider(VrShape *pCollider) ;
	virtual ~VrShapeCollider() ;
	VrShape* getShape() { return p_shape ; }
	virtual VrCollisionRecord& createCollision(VrNode* pCollider, VrNode* pCollidee) ;
	virtual VrCollisionRecord& createOdeCollision(VrNode* pCollider, VrNode* pCollidee) ;
	//
	virtual bool canCollide(VrNode *pCollider, VrNode *pCollidee) ;
	virtual void processContact(VrCollisionRecord& record, VrSurfaceInfo& surfaceInfo, VrContact *contact) ;
	//
	virtual int processCollision(VrCollisionRecord& record) ;
	virtual int processOdeCollision(VrCollisionRecord& record) ;
	//
	virtual void computeContactSurfaceInfo(VrSurfaceInfo& surfaceInfo, VrShape *pShape1, VrShape *pShape2) ;
	//TODO:newstuff
	virtual dGeomID getConvex() { return p_shape->getConvex() ; }
	/*Data Members*/
public:
	VrShape *p_shape ;
protected:
} ;

#endif //_VrShapeCollider_H
