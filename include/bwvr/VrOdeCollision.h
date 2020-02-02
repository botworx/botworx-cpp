/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _VrOdeCollision_H
#define _VrOdeCollision_H

#include "VrCollision.h"
//
//VrOdeCollision
//
class VrOdeCollision : public VrCollision {
public:
	VrOdeCollision() ;
	virtual ~VrOdeCollision() ;
	//Data Members
} ;
//
//VrOdeCollisionKit
//
#include "VrCollisionKit.h"

class VrOdeCollisionKit ;
template<>
struct BwSigT<VrOdeCollisionKit> : BwSigT<BwKit> {
	typedef VrOdeCollision	T_Part ;
} ;
typedef VrCollisionKitT<VrOdeCollisionKit> VrOdeCollisionKitBase ;

class VrOdeCollisionKit : public VrOdeCollisionKitBase {
public:
	VrOdeCollisionKit(BwPart *pOwner) : VrOdeCollisionKitBase(pOwner) {}
};

#endif //_VrOdeCollision_H
