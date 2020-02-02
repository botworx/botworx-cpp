/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <buggybots/BbTerrain.h>
#include <buggybots/BbTerrainQuad.h>

#include <bwvr/VrLayout.h>
#include <bwvr/VrWorld.h>
#include <bwvr/VrShape.h>
#include <bwvr/VrBuilder.h>

BbTerrainQuad::BbTerrainQuad(VrGroup *pGroup, BbTerrain *pTerrain, vrIndex quadIndex, int level) 
: VrTerrainQuad(pGroup, pTerrain, quadIndex, level) {
	p_terrain = pTerrain ;
}
void BbTerrainQuad::doConfig() {
	if(m_isSmallest) {
		VrOmTriMesh::VertexHandle hNW = h_vertices[VR_NW] ;
		VrOmTriMesh::VertexHandle hNE = h_vertices[VR_NE] ;
		VrOmTriMesh::VertexHandle hSE = h_vertices[VR_SE] ;
		VrOmTriMesh::VertexHandle hSW = h_vertices[VR_SW] ;

		VrOmTriMesh::Point point1 = p_tree->p_mesh->point(hNW) ;
		VrOmTriMesh::Point point2 = p_tree->p_mesh->point(hNE) ;
		VrOmTriMesh::Point point3 = p_tree->p_mesh->point(hSE) ;
		VrOmTriMesh::Point point4 = p_tree->p_mesh->point(hSW) ;
		
		bwPoint3 p1(point1[0], point1[1], point1[2]) ;
		bwPoint3 p2(point2[0], point2[1], point2[2]) ;
		bwPoint3 p3(point3[0], point3[1], point3[2]) ;
		bwPoint3 p4(point4[0], point4[1], point4[2]) ;

		bwTriangle tri(p1, p2, p3) ;
		bwVector3 norm = normal(tri) ;

		bwQuat quat(norm[0], norm[1], norm[2], 0) ;

		bwReal x = (p1[0] + p2[0] + p3[0] + p4[0]) / 4 ;
		bwReal y = (p1[1] + p2[1] + p3[1] + p4[1]) / 4 ;
		bwReal z = (p1[2] + p2[2] + p3[2] + p4[2]) / 4 ;

		bwPoint3 point = bwPoint3(x, y, z) - getPos() ;
		
		#if BB_OPTION_USE_DUNES
		//Add dunes ... 1 out of 10 random
		if(( (double)rand() / (double)(RAND_MAX+1) ) < .1) {
			VrModel *pDune = VrBuilder::singleton::get().build("Dune", this) ;
			pDune->setRelPos(point) ;
			pDune->setQuat(quat) ;
		}
		#endif
	}
	VrTerrainQuad::doConfig() ;
}