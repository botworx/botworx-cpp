/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <bwvr/VrTriMeshDataOmImporter.h>
#include <bwvr/VrTriMeshData.h>
#include <bwvr/VrOmTriMesh.h>

VrTriMeshDataOmImporter::VrTriMeshDataOmImporter(VrTriMeshData *pTriMeshData, VrOmTriMesh *pSrcMesh) : VrTriMeshDataBuilder(pTriMeshData) {
	p_srcMesh = pSrcMesh ;
	m_vertexCount = pSrcMesh->n_vertices() ;
	m_faceCount = pSrcMesh->n_faces() ;
}
void VrTriMeshDataOmImporter::copyFaces32() {
	VrOmTriMesh::ConstFaceIter fIt(p_srcMesh->faces_begin()),
		fEnd(p_srcMesh->faces_end());
	VrOmTriMesh::ConstFaceVertexIter fvIt;

	//Opcode can only use 32 bit indices!!!
	vrTriFace *pFace = (vrTriFace*)p_triMeshData->getIndices() ;

	for (; fIt!=fEnd; ++fIt) {

		fvIt = p_srcMesh->cfv_iter(fIt.handle());

		pFace[0][0] = fvIt.handle().idx() ;
		++fvIt;

		pFace[0][1] = fvIt.handle().idx() ;
		++fvIt;

		pFace[0][2] = fvIt.handle().idx() ;

		pFace++ ;
	}
}
void VrTriMeshDataOmImporter::copyFaces16() {
	//TODO:!!!
	return copyFaces32() ;
}
void VrTriMeshDataOmImporter::copyVertices() {
	memcpy(p_triMeshData->getVertexBuffer(), p_srcMesh->points(), sizeof(vrTriFace16)*m_vertexCount) ;
}
void VrTriMeshDataOmImporter::copyNormals() {
	memcpy(p_triMeshData->getNormalBuffer(), p_srcMesh->points(), sizeof(vrTriFace16)*m_vertexCount) ;
}
void VrTriMeshDataOmImporter::update() {
	copyVertices() ;

	if(p_triMeshData->getUses32bitIndex())
		copyFaces32() ;
	else
		copyFaces16() ;

	//copyNormals() ;
}
void VrTriMeshDataOmImporter::load() {
	bwAssert(m_vertexCount > 0) ;
	if(p_triMeshData->isLoaded())
		return ;
	if(p_srcMesh == NULL)
		return ;
	p_triMeshData->setIsLoaded(true) ;
//////////////
	p_triMeshData->setVertexCount(m_vertexCount) ;
	p_triMeshData->setVertexBuffer(new bwVector3[m_vertexCount]) ;
//////////////
	p_triMeshData->setUses32bitIndex(false) ;//TODO:fixable?
	size_t indexCount = m_faceCount*3 ;
	p_triMeshData->setIndexCount(indexCount) ;

	p_triMeshData->setFaceCount(m_faceCount) ; //TODO:watchme:dependent on triangles

	p_triMeshData->setFaceBuffer(new vrTriFace[m_faceCount]) ;
///////////////

	//p_normals = new bwVector3[m_vertexCount] ;
	p_triMeshData->setNormalBuffer(NULL) ;

	update() ;

	p_triMeshData->setIsLoaded(true) ;

}
bool VrTriMeshDataOmLoader::load(VrTriMeshData *pMesh) {
	VrTriMeshDataOmImporter importer(pMesh, p_srcMesh) ;
	importer.load() ;
	return true ;
}
