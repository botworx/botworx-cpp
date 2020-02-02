/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <bwvr/VrTriMeshDataOgreImporter.h>
#include <bwvr/VrTriMeshData.h>
#include <bwvr/VrScenario.h>

VrTriMeshDataOgreImporter::VrTriMeshDataOgreImporter(VrTriMeshData *pTriMeshData) : VrTriMeshDataBuilder(pTriMeshData) {
	//TODO:why are we getting the mesh name from the collision mesh???
	bwString meshName = pTriMeshData->getName() ;
	if(meshName.empty())
		throw BwException();
		p_ogreMesh = Ogre::MeshManager::getSingleton().load(Ogre::String(meshName),
			VrScenario::singleton::get().getName()) ;
	p_subMesh = NULL ;
	p_vertexData = NULL ;
	p_indexData = NULL ;

}
void VrTriMeshDataOgreImporter::copyFaces32() {
	vrIndex32 *pIndices = p_triMeshData->getIndices() ;
	size_t index = 0 ;
	size_t indexCount = p_triMeshData->getIndexCount() ;
	unsigned int* indexBuffer = (unsigned int*)
		p_indexBuffer->lock(0, indexCount*(sizeof(unsigned int)), Ogre::HardwareBuffer::HBL_DISCARD);

	for(size_t i = 0 ; i < indexCount ; ++i) {
		index = pIndices[i] = indexBuffer[i] ;
	}
	p_indexBuffer->unlock() ;
}
void VrTriMeshDataOgreImporter::copyFaces16() {
	vrIndex32 *pIndices = p_triMeshData->getIndices() ;
	size_t index = 0 ;
	size_t indexCount = p_triMeshData->getIndexCount() ;

	unsigned short* indexBuffer = (unsigned short*)
		p_indexBuffer->lock(0, indexCount*(sizeof(unsigned short)), Ogre::HardwareBuffer::HBL_DISCARD);

	for(size_t i = 0 ; i < indexCount ; ++i) {
		index = pIndices[i] = indexBuffer[i] ;
	}
	p_indexBuffer->unlock() ;
}
void VrTriMeshDataOgreImporter::copyVertices() {
	int scale = 1 ;
	bwReal x = 0, y = 0, z = 0 ;

	const Ogre::VertexElement* posElem = p_vertexData->vertexDeclaration->findElementBySemantic(Ogre::VES_POSITION);

	unsigned char* vertexBuffer = static_cast<unsigned char*>(
		p_posVertexBuffer->lock(Ogre::HardwareBuffer::HBL_DISCARD));

	size_t vertexSize = p_posVertexBuffer->getVertexSize() ;

	Ogre::Real *pVertex ;
	bwVector3 *pDestVertex = p_triMeshData->getVertexBuffer() ;

	size_t vertexCount = p_triMeshData->getVertexCount() ;
	for(size_t i = 0 ; i < vertexCount ; ++i) {
		posElem->baseVertexPointerToElement(vertexBuffer, &pVertex);

		x = pVertex[0] ;
		y = pVertex[1] ;
		z = pVertex[2] ;

		pDestVertex[i][0] = x ;
		pDestVertex[i][1] = y ;
		pDestVertex[i][2] = z ;

		vertexBuffer += vertexSize ;

	}
	p_posVertexBuffer->unlock() ;
}
void VrTriMeshDataOgreImporter::copyNormals() {
	int scale = 1 ;
	bwReal x = 0, y = 0, z = 0 ;

	const Ogre::VertexElement* normElem = p_vertexData->vertexDeclaration->findElementBySemantic(Ogre::VES_NORMAL);

	unsigned char* normBuffer = static_cast<unsigned char*>(
		p_normVertexBuffer->lock(Ogre::HardwareBuffer::HBL_DISCARD));


	Ogre::Real *pNormal ;
	bwVector3 *pDstNormal = p_triMeshData->getNormalBuffer() ;
	size_t vertexSize = p_normVertexBuffer->getVertexSize() ;
	size_t vertexCount = p_triMeshData->getVertexCount() ;
	for(size_t i = 0 ; i < vertexCount ; ++i) {
		normElem->baseVertexPointerToElement(normBuffer, &pNormal);
		x = pNormal[0] ;
		y = pNormal[1] ;
		z = pNormal[2] ;

		pDstNormal[i][0] = x ;
		pDstNormal[i][1] = y ;
		pDstNormal[i][2] = z ;

		normBuffer += vertexSize ;
	}
	p_normVertexBuffer->unlock() ;
}
void VrTriMeshDataOgreImporter::update() {
	copyVertices() ;

	if(p_triMeshData->getUses32bitIndex())
		copyFaces32() ;
	else
		copyFaces16() ;

	copyNormals() ;
}
void VrTriMeshDataOgreImporter::load() {
	if(p_triMeshData->isLoaded())
		return ;
	if(p_ogreMesh.isNull())
		return ;
	p_ogreMesh->load() ;
	p_triMeshData->setIsLoaded(true) ;

	p_subMesh = p_ogreMesh->getSubMesh(0) ;

	p_vertexData = p_subMesh->vertexData ;
	p_indexData = p_subMesh->indexData ;
///////////////////////////
	const Ogre::VertexElement* posElem = p_vertexData->vertexDeclaration->findElementBySemantic(Ogre::VES_POSITION);
	p_posVertexBuffer =
		p_vertexData->vertexBufferBinding->getBuffer(posElem->getSource());
	size_t vertexCount = p_vertexData->vertexCount ;
	bwAssert(vertexCount > 0) ;
	p_triMeshData->setVertexCount(vertexCount) ;

	p_triMeshData->setVertexBuffer(new bwVector3[vertexCount]) ;

//////////////////////
	p_indexBuffer = p_indexData->indexBuffer ;
	p_triMeshData->setUses32bitIndex(p_indexBuffer->getType() == Ogre::HardwareIndexBuffer::IT_32BIT) ;
	size_t indexCount = p_indexData->indexCount ;
	p_triMeshData->setIndexCount(indexCount) ;

	size_t faceCount = indexCount / 3 ;
	p_triMeshData->setFaceCount(faceCount) ; //TODO:watchme:dependent on triangles

	p_triMeshData->setFaceBuffer(new vrTriFace[faceCount]) ;

/////////////////////
	const Ogre::VertexElement* normElem = p_vertexData->vertexDeclaration->findElementBySemantic(Ogre::VES_NORMAL);
	p_normVertexBuffer =
		p_vertexData->vertexBufferBinding->getBuffer(normElem->getSource());


	//p_triMeshData->setNormalBuffer(NULL) ;
	p_triMeshData->setNormalBuffer(new bwVector3[vertexCount]) ;

	update() ;

	p_triMeshData->setIsLoaded(true) ;
}
bool VrTriMeshDataOgreLoader::load(VrTriMeshData *pMesh) {
	VrTriMeshDataOgreImporter importer(pMesh) ;
	importer.load() ;
	return true ;
}
