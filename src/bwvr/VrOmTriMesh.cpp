/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <bwvr/VrOmTriMesh.h>

void VrOmTriMesh::subdivide(size_t n) {
	Subdivider subdivide;
	subdivide.attach(*this);
	subdivide( n );
	subdivide.detach();
}