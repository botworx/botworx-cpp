/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _VrHexahedron_H
#define _VrHexahedron_H

#include "VrConvexMesh.h"

#include "VrOmTriMesh.h"

class VrHexahedronBuilder ;

class VrHexahedron : public VrConvexMesh {
public:
	VrHexahedron(VrGroup *pGroup) ;
	virtual bwString getClassName() { return "VrHexahedron" ; }
	virtual void doCreate(const BwPartInfo& info) ;
	void setPoint(int index, const bwPoint3& point) {
		m_points[index] = point ; 
	}
	//TODO:this needs to go higher up?
	virtual void generateMesh() ;
	/*Data Members*/
public:
	bwPoint3 m_points[8] ;
};
/////////////////
class VrHexahedronBuilder {
public:
	VrHexahedronBuilder(VrHexahedron *pModel) {
		p_model = pModel ;
	}
	void buildSides() ;
	void buildSide(int faceIndex, int index1, int index2, int index3, int index4) ;
	void buildFace(int sideIndex, int index1, int index2, int index3) ;
	void buildTexcoords(int faceIndex, int index1, int index2, int index3) ;
	void generateMesh() ;
	//Data Members
public:
	VrHexahedron *p_model ;
	VrOmTriMesh::VertexHandle h_vertices[6][4] ; //6 faces with 4 verts each
	//VrOmTriMesh::VertexHandle h_vertices[6][5] ; //6 faces with 5 verts each, corners and center points
	VrOmTriMesh *p_mesh ;
};

#endif //_VrHexahedron_H
