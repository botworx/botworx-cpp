/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <bwvr/VrQuadTree.h>
#include <bwvr/VrLayout.h>

VrQuadTree::VrQuadTree(VrGroup *pGroup) 
	//: VrQuad(pGroup, NULL, 0, 0), m_pool(sizeof(VrQuad)) {
	: VrQuad(pGroup, NULL, 0, 0) {
	p_tree = this ;
	//p_pool = NULL ;
	m_minQuadSize = 10 ;
	m_levelCount = 0 ;
	m_quadCount = 0 ; 
	m_rowCount = 0 ;
	m_tileUnit = 0 ;

	p_mesh = new VrOmTriMesh() ;
	//p_mesh->create() ;
	for(int i = 0 ; i < 4 ; ++i)
		m_outerQuads[i] = NULL ;
}
void VrQuadTree::doCreate(const BwPartInfo& info) {
	VrQuad::doCreate(info) ;
	createQuadFactory() ;
	divide(getMinQuadSize()) ;
}
int VrQuadTree::divide(bwReal minWidth) {
	int maxLevel = subdivide(minWidth) ;
	m_levelCount = maxLevel ;
	m_quadCount = pow(4, (float)maxLevel) ;
	m_rowCount = sqrt((float)m_quadCount) ;

	VrQuad *pChild ;
	for(int i = 0 ; i < 4 ; ++i) {
		pChild = m_quads[i] ;
		pChild->link() ;
	}

	m_tileUnit = m_outerQuads[VR_NW]->getWidth() ;

	return maxLevel ;
}
void VrQuadTree::generateMesh(int level) {
	buildVertices(level) ;
	buildFaces(level) ;

	VrOmTriMesh::VertexHandle hNW = h_vertices[VR_NW] = m_outerQuads[VR_NW]->h_vertices[VR_NW] ;
	VrOmTriMesh::VertexHandle hNE = h_vertices[VR_NE] = m_outerQuads[VR_NE]->h_vertices[VR_NE] ;
	VrOmTriMesh::VertexHandle hSE = h_vertices[VR_SE] = m_outerQuads[VR_SE]->h_vertices[VR_SE] ;
	VrOmTriMesh::VertexHandle hSW = h_vertices[VR_SW] = m_outerQuads[VR_SW]->h_vertices[VR_SW] ;

	buildTexcoords() ;
	//TODO:if we do need to sew it up.  Make sure bottom < 0.

	//time to sew it up, remember this is the bottom, reverse the order!
	/*std::vector<VrOmTriMesh::VertexHandle>  face_vhandles;
	//NW Triangle
	face_vhandles.clear();

	face_vhandles.push_back(hNW);
	face_vhandles.push_back(hNE);
	face_vhandles.push_back(hSW);

	p_root->p_mesh->add_face(face_vhandles) ;
	//SE Triangle
	face_vhandles.clear();

	face_vhandles.push_back(hNE);
	face_vhandles.push_back(hSE);
	face_vhandles.push_back(hSW);

	p_mesh->add_face(face_vhandles) ;*/
	//TODO:experimental
	p_mesh->update_normals(); //don't call subdivide without doing this! :)
	//p_mesh->subdivide(1) ; //TODO:why doesn't this work!!! :( ... Too slow anyhow.
	//p_mesh->update_normals(); //don't call subdivide without doing this! :)
}
void VrQuadTree::randomizeHeight(bwReal scale) {
	VrQuad *pQuadRow = m_outerQuads[VR_NW] ;
	VrQuad *pQuad = pQuadRow ;
	bwPoint3 point ;
	int rowCounter = 0, colCounter = 0 ;
	while(pQuadRow != NULL) {
		while(pQuad != NULL) {
			point = pQuad->getPos() ; //fixme
			pQuad->setPos(point[0], bwReal(rand())*scale, point[2]) ;
			pQuad = pQuad->p_east ;
			rowCounter = rowCounter + 1 ;
		}
		pQuad = pQuadRow = pQuadRow->p_south ;
		colCounter = colCounter + 1 ;
	}
}
void VrQuadTree::createQuadFactory() {
	//p_pool = new vrQuadPool(sizeof(VrQuad)) ; 
	p_quadFactory = new VrQuadFactory(sizeof(VrQuad)) ; 
}
VrQuad* VrQuadTree::createQuad(VrGroup *pGroup, int index, int level) {
	//VrQuad *pQuad = new((VrQuad*)p_pool->malloc())BbTerrainQuad(pGroup, this, index, level) ;
	//VrQuad *pQuad = new VrQuad(pGroup, this, index, level) ;
	VrQuad *pQuad = new (p_quadFactory->rentQuad()) VrQuad(pGroup, this, index, level) ;
	pQuad->setFactory(p_quadFactory) ;

	pQuad->create() ;
	return pQuad ;
}
//////////
VrQuadFactory::VrQuadFactory(size_t size) : BwFactory(NULL) {
	m_quadSize = size ;
	p_pool = new vrQuadPool(size) ; 
}
VrQuad* VrQuadFactory::rentQuad() {
	return static_cast<VrQuad*>(rent(m_quadSize)) ;
}

void* VrQuadFactory::rent(size_t size) {
	return p_pool->malloc() ;
}
void VrQuadFactory::release(void *pCell) {
	p_pool->free(pCell) ;
}