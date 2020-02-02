/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _VrTetrahedron_H
#define _VrTetrahedron_H

#include "VrConvexMesh.h"

#include "VrOmTriMesh.h"

class VrTetrahedronBuilder ;

class VrTetrahedron : public VrConvexMesh {
public:
	VrTetrahedron(VrGroup *pGroup) ;
	virtual void doCreate(const BwPartInfo& info) ;
	void setPoint(int index, const bwPoint3& point) {
		m_points[index] = point ; 
	}
	//virtual void addPoint(const bwPoint3& point) ; //TODO:confusing with set point ...
	//TODO:this needs to go higher up?
	virtual void generateMesh() ;
	virtual bwString getClassName() { return "VrTetrahedron" ; }
	/*Data Members*/
public:
	bwPoint3 m_points[4] ;
};
/////////////////
class VrTetrahedronBuilder {
public:
	VrTetrahedronBuilder(VrTetrahedron *pModel) {
		p_model = pModel ;
	}
	void buildSides() ;
	void buildSide(int faceIndex, int index1, int index2, int index3) ;
	void buildFace(int sideIndex, int index1, int index2, int index3) ;
	void buildTexcoords(int faceIndex, int index1, int index2, int index3) ;
	void generateMesh() ;
	//Data Members
public:
	VrTetrahedron *p_model ;
	VrOmTriMesh::VertexHandle h_vertices[4][3] ; //4 faces with 3 verts each
	VrOmTriMesh *p_mesh ;
};

#endif //_VrTetrahedron_H
