/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _VrConcaveMesh_H
#define _VrConcaveMesh_H

#include "VrTriMesh.h"

class VrConcaveMesh : public VrTriMesh {
public:
	VrConcaveMesh(VrGroup *pGroup) ;
	virtual bwString getClassName() { return "VrConcaveMesh" ; }
	virtual void createCollider() ;
	virtual void createConvex() ;
	virtual void createTriMeshData() ;
	/*Data Members*/
};

#endif //_VrConcaveMesh_H
