/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _VrCone_H
#define _VrCone_H

#include "VrConvexMesh.h"

class VrCone : public VrConvexMesh {
public:
	VrCone(VrGroup *pGroup) : VrConvexMesh(pGroup) {
		vuInfo().setMeshName("VrCone.mesh") ;
	}
	virtual bwString getClassName() { return "VrCone" ; }
};

#endif //_VrCone_H
