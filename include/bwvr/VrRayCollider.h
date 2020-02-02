/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _VrRayCollider_H
#define _VrRayCollider_H

#include <bwvr/VrShapeCollider.h>

class VrRay ;

class VrRayCollider : public VrShapeCollider {
public:
	VrRayCollider(VrRay *pCollider) : VrShapeCollider(pCollider) {
		p_collider = pCollider ;
	}
	virtual void processContact(VrCollisionRecord& record, VrSurfaceInfo& surfaceInfo, VrContact *contact) {
		VrCollider::processContact(record, surfaceInfo, contact) ;
	}
	virtual bool canCollide(VrNode* pCollider, VrNode* pCollidee) { return false ; }
	//
	VrRay *p_collider ;
};

#endif //_VrRayCollider_H
