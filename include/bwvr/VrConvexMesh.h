/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _VrConvexMesh_H
#define _VrConvexMesh_H

#include "VrTriMesh.h"

class VrConvexMesh : public VrTriMesh {
public:
	VrConvexMesh(VrGroup *pGroup) ;
	virtual void computePoints() ;
	virtual void createConvex() ;
	virtual bwString getClassName() { return "VrConvexMesh" ; }
	virtual void addPoint(const bwPoint3& point) ;
	/*Data Members*/
};

#endif //_VrConvexMesh_H
