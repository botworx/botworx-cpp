/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <bwvr/VrConcaveMesh.h>
#include <bwvr/VrTriMeshData.h>
#include <bwvr/VrBody.h>
#include <bwvr/VrPhysics.h>
#include <bwvr/VrVu.h>
#include <bwvr/VrSurfaceInfo.h>

VrConcaveMesh::VrConcaveMesh(VrGroup *pGroup) : VrTriMesh(pGroup) {
	setNodeType(NODE_CONCAVEMESH) ;
}
void VrConcaveMesh::createCollider() {
	VrTriMesh::createCollider() ;
}
void VrConcaveMesh::createConvex() {
	VrShape::createConvex() ;
}
void VrConcaveMesh::createTriMeshData() {
		VrTriMesh::createTriMeshData() ;
}