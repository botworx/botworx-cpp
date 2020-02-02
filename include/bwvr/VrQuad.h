/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _VrQuad_H
#define _VrQuad_H

#include "VrPlace.h"
#include "VrOmTriMesh.h"

class VrQuadTree ;

class VrQuad : public VrPlace {
public:
	VrQuad(VrGroup *pGroup, VrQuadTree *pTree, vrIndex quadIndex, int level) ;
	int subdivide(bwReal minWidth) ;
	virtual void onSubdivision() {}
	void linkNorth() ;
	void linkEast() ;
	void linkSouth() ;
	void linkWest() ;
	void link() ;
	VrQuad* getParent() { return static_cast<VrQuad*>(p_group) ; }
	//VrQuad* createQuad(vrIndex index, int level) ;
	void createQuads() ;
	VrOmTriMesh::VertexHandle lookupVertexNE() ;
	VrOmTriMesh::VertexHandle lookupVertexSE() ;
	VrOmTriMesh::VertexHandle lookupVertexSW() ;
	void buildVertices(int level) ;
	void buildTexcoords() ;
	void buildFaces(int level) ;
	VrOmTriMesh::VertexHandle getVertex() { return h_vertices[VR_NW] ; }
	//void setVertexHeight(bwReal height) ;
	/*Data Members*/
public:
	int m_level ; //do we really need this?
	bool m_isSmallest ;
	VrQuadTree *p_tree ;
	vrIndex32 m_faceIndex ;
	//VrOmTriMesh::VertexHandle h_vertexNW ; //quads own nw vertex
	VrOmTriMesh::VertexHandle h_vertices[4] ; //quads own nw vertex
	//VrOmTriMesh::FaceHandle h_face ;
	VrQuad* m_quads[4] ;
	VrQuad* p_north ;
	VrQuad* p_east ;
	VrQuad* p_south ;
	VrQuad* p_west ;
};

#endif //_VrQuad_H