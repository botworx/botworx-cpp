/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _VrCollisionSystem_H
#define _VrCollisionSystem_H

#include <bwcore/BwSystem.h>

class VrCollision ;

class VrCollisionSystem : public BwSystem {
public:
	VrCollisionSystem(BwPart *pPart) ;
	virtual VrCollision* createCollision(collisionType type) = 0 ;
	//Data Members
} ;

typedef std::vector<VrCollisionSystem*> VrCollisionSystems ;
typedef VrCollisionSystems::iterator VrCollisionSystemIter ;

#endif //_VrCollisionSystem_H