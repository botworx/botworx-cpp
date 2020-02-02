/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <bwvr/VrQuad.h>
#include <bwvr/VrQuadTree.h>

VrQuad::VrQuad(VrGroup *pGroup, VrQuadTree *pTree, vrIndex quadIndex, int level) : VrPlace(pGroup) {
	p_tree = pTree ;
	m_indice = quadIndex ;
	m_level = level ;
	m_size[1] = 100 ;
	setMinSize(bwSize3(0,100,0)) ;
	p_north = p_east = p_south = p_west = NULL ;
	for(int i = 0 ; i < 4 ; ++i)
		m_quads[i] = NULL ;
//
	m_isSmallest = false ;
	vrIndex32 m_faceIndex = 0 ;
	// VrRelLay newLay ;
	// setLay(newLay) ;
	setLay(VrRelLay()) ;
}
/*void VrQuad::setVertexHeight(bwReal height) {
	VrOmTriMesh::Vertex &vertex = p_tree->p_mesh->deref(h_vertices[VR_NW]) ; 
}*/

void VrQuad::linkNorth() {
	VrQuad *pNorth ;
	switch(m_indice) {
		case VR_NW :
			pNorth = getParent()->p_north ;
			if(pNorth != NULL)
				pNorth = pNorth->m_quads[VR_SW] ;
			break ;
		case VR_NE :
			pNorth = getParent()->p_north ;
			if(pNorth != NULL)
				pNorth = pNorth->m_quads[VR_SE] ;
			break ;
		case VR_SE :
			pNorth = getParent()->m_quads[VR_NE] ;
			break ;
		case VR_SW :
			pNorth = getParent()->m_quads[VR_NW] ;
			break ;
	}
	p_north = pNorth ;
}
void VrQuad::linkEast() {
	VrQuad *pEast ;
	switch(m_indice) {
		case VR_NW :
			pEast = getParent()->m_quads[VR_NE] ;
			break ;
		case VR_NE :
			pEast = getParent()->p_east ;
			if(pEast != NULL)
				pEast = pEast->m_quads[VR_NW] ;
			break ;
		case VR_SE :
			pEast = getParent()->p_east ;
			if(pEast != NULL)
				pEast = pEast->m_quads[VR_SW] ;
			break ;
		case VR_SW :
			pEast = getParent()->m_quads[VR_SE] ;
			break ;
	}
	p_east = pEast ;
}
void VrQuad::linkSouth() {
	VrQuad *pSouth ;
	switch(m_indice) {
		case VR_NW :
			pSouth = getParent()->m_quads[VR_SW] ;
			break ;
		case VR_NE :
			pSouth = getParent()->m_quads[VR_SE] ;
			break ;
		case VR_SE :
			pSouth = getParent()->p_south ;
			if(pSouth != NULL)
				pSouth = pSouth->m_quads[VR_NE] ;
			break ;
		case VR_SW :
			pSouth = getParent()->p_south ;
			if(pSouth != NULL)
				pSouth = pSouth->m_quads[VR_NW] ;
			break ;
	}
	p_south = pSouth ;
}
void VrQuad::linkWest() {
	VrQuad *pWest ;
	switch(m_indice) {
		case VR_NW :
			pWest = getParent()->p_west ;
			if(pWest != NULL)
				pWest = pWest->m_quads[VR_NE] ;
			break ;
		case VR_NE :
			pWest = getParent()->m_quads[VR_NW] ;
			break ;
		case VR_SE :
			pWest = getParent()->m_quads[VR_SW] ;
			break ;
		case VR_SW :
			pWest = getParent()->p_west ;
			if(pWest != NULL)
				pWest = pWest->m_quads[VR_SE] ;
			break ;
	}
	p_west = pWest ;
}
void VrQuad::link() {
	linkNorth() ;
	linkEast() ;
	linkSouth() ;
	linkWest() ;

	if(p_west == NULL && p_north == NULL)
		p_tree->m_outerQuads[VR_NW] = this ;
	else if(p_north == NULL && p_east == NULL)
		p_tree->m_outerQuads[VR_NE] = this ;
	else if(p_east == NULL && p_south == NULL)
		p_tree->m_outerQuads[VR_SE] = this ;
	else if(p_south == NULL && p_west == NULL)
		p_tree->m_outerQuads[VR_SW] = this ;

	if(m_isSmallest)
		return ;
	//else
	VrQuad *pChild = NULL ;
	for(int i = 0 ; i < 4 ; ++i) {
		pChild = m_quads[i] ;
		pChild->link() ;
	}
}
VrOmTriMesh::VertexHandle VrQuad::lookupVertexNE() {
	VrOmTriMesh::VertexHandle hVertex ;
	bwReal y = 0 ;
	bwPoint3 pos = getPos() ;

	if(p_east != NULL) {
		hVertex = p_east->getVertex() ;
		//new
		VrOmTriMesh::Point point = p_tree->p_mesh->point(hVertex) ; 
		hVertex = p_tree->p_mesh->add_vertex(point) ;
		//new-end
	}
	else {
		bwReal x = pos[0] + m_size[0] * bwRealTraits::Half ;
		if(p_north == NULL || p_east == NULL)
			y = p_tree->getPos()[1] ;
		else
			y = pos[1] ;
		bwReal z = pos[2] - m_size[2] * bwRealTraits::Half ;
		hVertex = p_tree->p_mesh->add_vertex(VrOmTriMesh::Point(x, y, z)) ;
	}
	return hVertex ;
}
VrOmTriMesh::VertexHandle VrQuad::lookupVertexSE() {
	VrOmTriMesh::VertexHandle hVertex ;
	bwReal y = 0 ;
	bwPoint3 pos = getPos() ;

	if(p_east != NULL && p_east->p_south != NULL) {
		hVertex = p_east->p_south->getVertex() ; 
		//new
		VrOmTriMesh::Point point = p_tree->p_mesh->point(hVertex) ; 
		hVertex = p_tree->p_mesh->add_vertex(point) ;
		//new-end
	}
	else {
		bwReal x = pos[0] + m_size[0] * bwRealTraits::Half ;
		if(p_south == NULL || p_east == NULL)
			y = p_tree->getPos()[1] ;
		else
			y = pos[1] ;
		bwReal z = pos[2] + m_size[2] * bwRealTraits::Half ;
		hVertex = p_tree->p_mesh->add_vertex(VrOmTriMesh::Point(x, y, z)) ;
	}
	return hVertex ;
}
VrOmTriMesh::VertexHandle VrQuad::lookupVertexSW() {
	VrOmTriMesh::VertexHandle hVertex ;
	bwReal y = 0 ;
	bwPoint3 pos = getPos() ;

	if(p_south != NULL) {
		hVertex = p_south->getVertex() ;
		//new
		VrOmTriMesh::Point point = p_tree->p_mesh->point(hVertex) ; 
		hVertex = p_tree->p_mesh->add_vertex(point) ;
		//new-end
	}
	else {
		bwReal x = pos[0] - m_size[0] * bwRealTraits::Half ;
		if(p_south == NULL || p_west == NULL)
			y = p_tree->getPos()[1] ;
		else
			y = pos[1] ;
		bwReal z = pos[2] + m_size[2] * bwRealTraits::Half ;
		hVertex = p_tree->p_mesh->add_vertex(VrOmTriMesh::Point(x, y, z)) ;
	}
	return hVertex ;
}
void VrQuad::buildVertices(int level) {
	bwPoint3 pos = getPos() ;

	if(m_level != level) {
		VrQuad *pChild ;
		for(int i = 0 ; i < 4 ; ++i) {
			pChild = m_quads[i] ;
			if(pChild != NULL)
				pChild->buildVertices(level) ;
		}
		return ;
	}
	//else
	bwReal y = 0 ;

	bwReal x = pos[0] - m_size[0] * bwRealTraits::Half ;
	if(p_north == NULL || p_west == NULL)
		y = p_tree->getPos()[1] ;
	else
		y = pos[1] ;
	bwReal z = pos[2] - m_size[2] * bwRealTraits::Half ;

	h_vertices[VR_NW] = p_tree->p_mesh->add_vertex(VrOmTriMesh::Point(x, y, z)) ;
}
void VrQuad::buildTexcoords() {
	p_tree->p_mesh->set_texcoord2D(h_vertices[VR_NW],VrOmTriMesh::TexCoord2D(.99f, .01f) ) ;
	p_tree->p_mesh->set_texcoord2D(h_vertices[VR_NE], VrOmTriMesh::TexCoord2D(.01f, .01f));
	p_tree->p_mesh->set_texcoord2D(h_vertices[VR_SE], VrOmTriMesh::TexCoord2D(.99f, .99f)) ;
	p_tree->p_mesh->set_texcoord2D(h_vertices[VR_SW], VrOmTriMesh::TexCoord2D(.01f, .99f));
}
void VrQuad::buildFaces(int level) {
	if(m_level != level) {
		VrQuad *pChild ;
		for(int i = 0 ; i < 4 ; ++i) {
			pChild = m_quads[i] ;
			if(pChild != NULL)
				pChild->buildFaces(level) ;
		}
		return ;
	}
	//else
	VrOmTriMesh::VertexHandle hNW = h_vertices[VR_NW] ;
	VrOmTriMesh::VertexHandle hNE = h_vertices[VR_NE] = lookupVertexNE() ;
	VrOmTriMesh::VertexHandle hSE = h_vertices[VR_SE] = lookupVertexSE() ;
	VrOmTriMesh::VertexHandle hSW = h_vertices[VR_SW] = lookupVertexSW() ;

	buildTexcoords() ;

	std::vector<VrOmTriMesh::VertexHandle>  face_vhandles;

	//NW Triangle
	face_vhandles.clear();
	face_vhandles.push_back(hNW);
	face_vhandles.push_back(hSW);
	face_vhandles.push_back(hNE);

	p_tree->p_mesh->add_face(face_vhandles) ;

	//SE Triangle
	face_vhandles.clear();
	face_vhandles.push_back(hNE);
	face_vhandles.push_back(hSW);
	face_vhandles.push_back(hSE);
	p_tree->p_mesh->add_face(face_vhandles) ;
}
void VrQuad::createQuads() {
	bwPoint3 pos = getPos() ;
	bwReal x = 0, y = pos[1] , z = 0 ;
	VrQuadTree *pRoot = p_tree ;
	//TODO:this could be trouble ... pointer to self? ... recursion trap ...
	if(pRoot == NULL)
		pRoot = static_cast<VrQuadTree*>(this) ;

	for(int index = 0 ; index < 4 ; ++index) {
		VrQuad *pChild = pRoot->createQuad(this, index, m_level + 1) ;
		switch(index) {
			case VR_NW :
				x = pos[0] - m_size[0] * bwRealTraits::Quarter ;
				z = pos[2] - m_size[2] * bwRealTraits::Quarter ;
				break ;
			case VR_NE :
				x = pos[0] + m_size[0] * bwRealTraits::Quarter ;
				z = pos[2] - m_size[2] * bwRealTraits::Quarter ;
				break ;
			case VR_SE :
				x = pos[0] + m_size[0] * bwRealTraits::Quarter ;
				z = pos[2] + m_size[2] * bwRealTraits::Quarter ;
				break ;
			case VR_SW :
				x = pos[0] - m_size[0] * bwRealTraits::Quarter ;
				z = pos[2] + m_size[2] * bwRealTraits::Quarter ;
				break ;
		}
		pChild->setPos(x, y, z) ;
		pChild->setSize(bwSize3(m_size[0] * bwRealTraits::Half, m_size[1], m_size[2] * bwRealTraits::Half)) ;
		pChild->setMinSize(bwSize3(m_size[0] * bwRealTraits::Half, m_size[1], m_size[2] * bwRealTraits::Half)) ;

		m_quads[index] = pChild ;
	}	
}
int VrQuad::subdivide(bwReal minWidth) {
	int level = 0 ;

	if(m_size[0] <= minWidth) {
		m_isSmallest = true ;
		onSubdivision() ;
		return m_level ;
	}
	//else

	VrQuad *pChild = NULL ;

	createQuads() ;

	for(int i = 0 ; i < 4 ; ++i) {
		pChild = m_quads[i] ;
		level = pChild->subdivide(minWidth) ;
	}
	onSubdivision() ;
	return level ;
}