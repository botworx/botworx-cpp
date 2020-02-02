/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _VrRandomQuadMap_H
#define _VrRandomQuadMap_H

#include "VrQuadMap.h"

class VrQuadTree ;

class VrRandomQuadMap : public VrQuadMap {
public:
	virtual void alter(VrQuadTree *pTree) ;
	//Data
public:
};

#endif //_VrRandomQuadMap_H