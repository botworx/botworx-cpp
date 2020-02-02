/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _VrTerrain_H
#define _VrTerrain_H

#include "VrQuadTree.h"

class VrTerrain : public VrQuadTree {
public:
	VrTerrain(VrGroup *pGroup) ;
	virtual void createQuadFactory() ;
	virtual VrQuad* createQuad(VrGroup *pGroup, int index, int level) ;
	/*Data Members*/
public:	
};

#endif //_VrTerrain_H
