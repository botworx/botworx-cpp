/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <bwvr/VrTetrahedron.h>
#include <bwvr/VrOgreMeshBuilder.h>

VrTetrahedron::VrTetrahedron(VrGroup *pGroup) : VrConvexMesh(pGroup) {
	vuInfo().setMaterialName("VrBox/mat_1_0") ;
}
void VrTetrahedron::doCreate(const BwPartInfo& info) {
	vuInfo().setMeshName(getName()) ;
	VrConvexMesh::doCreate(info) ;
}
void VrTetrahedron::generateMesh() {
	VrTriMesh::generateMesh() ; //sets loader to create ode mesh from ogre mesh

	VrTetrahedronBuilder builder(this) ;
	builder.generateMesh() ;
	//
	std::string name = getName() ;
	VrOgreMeshBuilder ogreBuilder(name) ;
	ogreBuilder.setMaterialName(vuInfo().getMaterialName()) ;
	ogreBuilder.build(builder.p_mesh) ;
}
//////////////////////
void VrTetrahedronBuilder::buildTexcoords(int faceIndex, int index1, int index2, int index3) {
	p_mesh->set_texcoord2D(h_vertices[faceIndex][index1], VrOmTriMesh::TexCoord2D(.49, .49));
	p_mesh->set_texcoord2D(h_vertices[faceIndex][index2], VrOmTriMesh::TexCoord2D(.25, .01));
	p_mesh->set_texcoord2D(h_vertices[faceIndex][index3], VrOmTriMesh::TexCoord2D(.01, .49));
}
void VrTetrahedronBuilder::buildFace(int sideIndex, int index1, int index2, int index3) {
	std::vector<VrOmTriMesh::VertexHandle>  face_vhandles;

	face_vhandles.push_back(h_vertices[sideIndex][index1]);
	face_vhandles.push_back(h_vertices[sideIndex][index2]);
	face_vhandles.push_back(h_vertices[sideIndex][index3]);

	p_mesh->add_face(face_vhandles) ;

	buildTexcoords(sideIndex, index1, index2, index3) ;
}

void VrTetrahedronBuilder::buildSide(int sideIndex, int index1, int index2, int index3) {
	bwPoint3 p1 = p_model->m_points[index1] ;
	bwPoint3 p2 = p_model->m_points[index2] ;
	bwPoint3 p3 = p_model->m_points[index3] ;

	h_vertices[sideIndex][0] = p_mesh->add_vertex(
			VrOmTriMesh::Point(p1[0], p1[1], p1[2])) ;
	h_vertices[sideIndex][1] = p_mesh->add_vertex(
			VrOmTriMesh::Point(p2[0], p2[1], p2[2])) ;
	h_vertices[sideIndex][2] = p_mesh->add_vertex(
			VrOmTriMesh::Point(p3[0], p3[1], p3[2])) ;

	buildFace(sideIndex, 0, 1, 2) ;
}
void VrTetrahedronBuilder::buildSides() {
	buildSide(0,0,3,1) ; //right side
	buildSide(1,1,3,2) ; //back side
	buildSide(2,2,3,0) ; //left side
	buildSide(3,0,1,2) ; //bottom side
}
void VrTetrahedronBuilder::generateMesh() {
	p_mesh = new VrOmTriMesh() ;
	buildSides() ;
	p_mesh->update_normals();
}