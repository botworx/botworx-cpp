/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <bwvr/VrHexahedron.h>
#include <bwvr/VrOgreMeshBuilder.h>
//
VrHexahedron::VrHexahedron(VrGroup *pGroup) : VrConvexMesh(pGroup) {
	vuInfo().setMaterialName("VrBox/mat_1_0") ;
}
void VrHexahedron::doCreate(const BwPartInfo& info) {
	vuInfo().setMeshName(getName()) ;
	VrConvexMesh::doCreate(info) ;
}
void VrHexahedron::generateMesh() {
	VrTriMesh::generateMesh() ; //sets loader to create ode mesh from ogre mesh

	VrHexahedronBuilder builder(this) ;
	builder.generateMesh() ;
	//
	std::string name = getName() ;
	VrOgreMeshBuilder ogreBuilder(name) ;
	ogreBuilder.setMaterialName(vuInfo().getMaterialName()) ;
	ogreBuilder.build(builder.p_mesh) ;
}
//////////////////////
void VrHexahedronBuilder::buildTexcoords(int faceIndex, int index1, int index2, int index3) {
	if(index1 == 0) {
		p_mesh->set_texcoord2D(h_vertices[faceIndex][index1], VrOmTriMesh::TexCoord2D(.49, .01));
		p_mesh->set_texcoord2D(h_vertices[faceIndex][index2], VrOmTriMesh::TexCoord2D(.49, .49));
		p_mesh->set_texcoord2D(h_vertices[faceIndex][index3], VrOmTriMesh::TexCoord2D(.01, .49));
	}
	else {
		p_mesh->set_texcoord2D(h_vertices[faceIndex][index1], VrOmTriMesh::TexCoord2D(.01, .01));
		p_mesh->set_texcoord2D(h_vertices[faceIndex][index2], VrOmTriMesh::TexCoord2D(.01, .49));
		p_mesh->set_texcoord2D(h_vertices[faceIndex][index3], VrOmTriMesh::TexCoord2D(.49, .49));
	}
}
void VrHexahedronBuilder::buildFace(int sideIndex, int index1, int index2, int index3) {
	std::vector<VrOmTriMesh::VertexHandle>  face_vhandles;

	face_vhandles.push_back(h_vertices[sideIndex][index1]);
	face_vhandles.push_back(h_vertices[sideIndex][index2]);
	face_vhandles.push_back(h_vertices[sideIndex][index3]);

	p_mesh->add_face(face_vhandles) ;

	buildTexcoords(sideIndex, index1, index2, index3) ;
}

void VrHexahedronBuilder::buildSide(int sideIndex, int index1, int index2, int index3, int index4) {
	bwPoint3 p1 = p_model->m_points[index1] ;
	bwPoint3 p2 = p_model->m_points[index2] ;
	bwPoint3 p3 = p_model->m_points[index3] ;
	bwPoint3 p4 = p_model->m_points[index4] ;

	h_vertices[sideIndex][0] = p_mesh->add_vertex(
			VrOmTriMesh::Point(p1[0], p1[1], p1[2])) ;
	h_vertices[sideIndex][1] = p_mesh->add_vertex(
			VrOmTriMesh::Point(p2[0], p2[1], p2[2])) ;
	h_vertices[sideIndex][2] = p_mesh->add_vertex(
			VrOmTriMesh::Point(p3[0], p3[1], p3[2])) ;
	h_vertices[sideIndex][3] = p_mesh->add_vertex(
			VrOmTriMesh::Point(p4[0], p4[1], p4[2])) ;
	//
	bwReal x = (p1[0] + p2[0] + p3[0] + p4[0]) * bwRealTraits::Quarter ;
	bwReal y = (p1[1] + p2[1] + p3[1] + p4[1]) * bwRealTraits::Quarter ;
	bwReal z = (p1[2] + p2[2] + p3[2] + p4[2]) * bwRealTraits::Quarter ;

	buildFace(sideIndex, 0, 1, 3) ;
	buildFace(sideIndex, 1, 2, 3) ;
}
void VrHexahedronBuilder::buildSides() {
	buildSide(0,0,1,2,3) ; //top side
	buildSide(1,7,6,5,4) ; //bottom side
	buildSide(2,3,2,6,7) ; //front side
	buildSide(3,0,3,7,4) ; //left side
	buildSide(4,1,0,4,5) ; //back side
	buildSide(5,2,1,5,6) ; //right side
}
void VrHexahedronBuilder::generateMesh() {
	p_mesh = new VrOmTriMesh() ;
	buildSides() ;
	p_mesh->update_normals();
}