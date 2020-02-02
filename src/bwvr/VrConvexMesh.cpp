/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <bwvr/VrConvexMesh.h>
#include <bwvr/VrBody.h>
#include <bwvr/VrPhysics.h>
#include <bwvr/VrVu.h>
#include <bwvr/VrSurfaceInfo.h>
#include <bwvr/VrTriMeshData.h>

VrConvexMesh::VrConvexMesh(VrGroup *pGroup) : VrTriMesh(pGroup) {
	setNodeType(NODE_CONVEXMESH) ;
}
void VrConvexMesh::createConvex() {
	VrShape::createConvex() ;
}
void VrConvexMesh::addPoint(const bwPoint3& point) {
}
void VrConvexMesh::computePoints() {
	int pointCount = 1 ;

	typedef std::vector<bwPoint3> Points ;

	typedef Points::iterator PointIter ;
	Points points ;

	points.resize(64) ;
	int vertexCount = p_triMeshData->getVertexCount() ;
	bwVector3* vertice = p_triMeshData->getVertexBuffer() ;
	for(int i = 0 ; i < vertexCount ; ++i) {
		bool redundant = false ;
		for(int j = 0 ; j < pointCount ; ++j) {
			if(vertice[i] == points[j]) {
				redundant = true ;
				break ;
			}
		}
		if(!redundant) {
			points.push_back(vertice[i]) ;
			addPoint(vertice[i]) ;
			pointCount++ ;
		}
	}
}
