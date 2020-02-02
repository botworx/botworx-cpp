/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _VrCollisionKit_H
#define _VrCollisionKit_H

#include "VrCollider.h"
#include "VrCollision.h"
//
//VrCollisionKit
//
class VrCollisionKit : public BwKit {
public:
	VrCollisionKit(BwPart *pPart) : BwKit(pPart) {}
	virtual VrCollision* createCollision() = 0 ;
	virtual void destroyCollision(VrCollision *pCollision) = 0 ;
	//Data Members
} ;
//
//VrCollisionKitT
//
template<typename T_Class, typename T_Base = VrCollisionKit>
class VrCollisionKitT : public BwPoolKitT<T_Class, T_Base> {
	using T_Part = typename VrCollisionKitT<T_Class, T_Base>::T_Part;
public:
	VrCollisionKitT(BwPart *pPart) : BwPoolKitT<T_Class, T_Base>(pPart) {}
	virtual VrCollision* createCollision() { 
		return new(this->rent(sizeof(T_Part))) T_Part() ; }
	virtual void destroyCollision(VrCollision *pCollision) { this->release(pCollision) ; }
	//Data Members
public:
};

#endif //_VrCollisionKit_H
