/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <bwvr/VrOgreMeshBuilder.h>
#include <bwvr/VrScenario.h>

#include <bwvr/config/ogre.h>
#include <OGRE/OgreHardwareBufferManager.h>

VrOgreMeshBuilder::VrOgreMeshBuilder(const bwString& pName) : VrOgreMeshTool(pName) {
}
void VrOgreMeshBuilder::createVertexBuffer() {
	p_vertexData = new Ogre::VertexData();
	p_vertexData->vertexStart = 0;
	p_vertexData->vertexCount = m_vertexCount ;

	p_vDecl = p_vertexData->vertexDeclaration;
	p_vBind = p_vertexData->vertexBufferBinding;


	p_vDecl->addElement(0, 0, Ogre::VET_FLOAT3, Ogre::VES_POSITION);
	p_vDecl->addElement(1, 0, Ogre::VET_FLOAT3, Ogre::VES_NORMAL);
	p_vDecl->addElement(2, 0, Ogre::VET_FLOAT2, Ogre::VES_TEXTURE_COORDINATES);

	p_posVertexBuffer =
		Ogre::HardwareBufferManager::getSingleton().createVertexBuffer(
            3*sizeof(Ogre::Real),
			m_vertexCount,
			Ogre::HardwareBuffer::HBU_STATIC_WRITE_ONLY);
	p_vBind->setBinding(0, p_posVertexBuffer);

	p_subMesh->vertexData = p_vertexData ;
}
void VrOgreMeshBuilder::createNormalBuffer() {
	p_normVertexBuffer =
         Ogre::HardwareBufferManager::getSingleton().createVertexBuffer(
            3*sizeof(Ogre::Real),
			m_vertexCount,
			Ogre::HardwareBuffer::HBU_STATIC_WRITE_ONLY);
	p_vBind->setBinding(1, p_normVertexBuffer);
}
void VrOgreMeshBuilder::createTextureCoordsBuffer() {
	p_texcoordsVertexBuffer =
         Ogre::HardwareBufferManager::getSingleton().createVertexBuffer(
            2*sizeof(Ogre::Real),
			m_vertexCount,
			Ogre::HardwareBuffer::HBU_STATIC_WRITE_ONLY);
    p_vBind->setBinding(2, p_texcoordsVertexBuffer);
}
void VrOgreMeshBuilder::createIndexBuffer() {
	p_indexData = new Ogre::IndexData();

	p_indexBuffer =
		Ogre::HardwareBufferManager::getSingleton().createIndexBuffer(
			Ogre::HardwareIndexBuffer::IT_16BIT,
			3*m_faceCount,
			Ogre::HardwareBuffer::HBU_STATIC_WRITE_ONLY);

	p_indexData->indexBuffer = p_indexBuffer ;
	p_indexData->indexCount = m_faceCount * 3 ;
	p_indexData->indexStart = 0 ;

	p_subMesh->indexData = p_indexData ;

}
void VrOgreMeshBuilder::copyVertices(VrOmTriMesh *pTriMesh) {
	p_posVertexBuffer->writeData(0,
		p_posVertexBuffer->getSizeInBytes(), // size
		pTriMesh->points(), // source
		true); // discard?
}
void VrOgreMeshBuilder::copyNormals(VrOmTriMesh *pTriMesh) {
	const VrOmTriMesh::Normal* pNormals = pTriMesh->vertex_normals() ;
	p_normVertexBuffer->writeData(0,
		p_normVertexBuffer->getSizeInBytes(), // size
		pNormals, // source
		true); // discard?
}
void VrOgreMeshBuilder::copyTextureCoords(VrOmTriMesh *pTriMesh) {
	VrOmTriMesh::TexCoord2D texcoord ;
	Ogre::Real u = 0, v = 0 ;
	Ogre::Real *pCoord = (Ogre::Real*)
		p_texcoordsVertexBuffer->lock(0, m_vertexCount*(sizeof(Ogre::Real))*2, Ogre::HardwareBuffer::HBL_DISCARD);

	for (VrOmTriMesh::VertexIter v_it = pTriMesh->vertices_begin();
           v_it != pTriMesh->vertices_end(); ++v_it)
      {
		  texcoord = pTriMesh->texcoord2D(*v_it);
		u = texcoord[0] ;
		*pCoord++ = u ;
		v = texcoord[1] ;
		*pCoord++ = v ;
      }
	p_texcoordsVertexBuffer->unlock() ;
}
void VrOgreMeshBuilder::copyFaces(VrOmTriMesh *pTriMesh) {
	VrOmTriMesh::ConstFaceIter    fIt(pTriMesh->faces_begin()),
									fEnd(pTriMesh->faces_end());
	VrOmTriMesh::ConstFaceVertexIter fvIt;

	vrTriFace16 *pFace = (vrTriFace16*)
		p_indexBuffer->lock(0, m_faceCount*3*2, Ogre::HardwareBuffer::HBL_DISCARD);

	for (; fIt!=fEnd; ++fIt) {

		fvIt = pTriMesh->cfv_iter(fIt.handle());

		pFace[0][0] = fvIt.handle().idx() ;
		++fvIt;

		pFace[0][1] = fvIt.handle().idx() ;
		++fvIt;

		pFace[0][2] = fvIt.handle().idx() ;

		pFace++ ;
	}

	p_indexBuffer->unlock() ;
}
void VrOgreMeshBuilder::createMesh() {
	// create mesh and submesh
	p_ogreMesh = Ogre::MeshManager::getSingleton().create(m_meshName, VrScenario::singleton::get().getName(), true) ;
	p_subMesh = p_ogreMesh->createSubMesh();
	p_subMesh->useSharedVertices = false; //TODO:?
}
void VrOgreMeshBuilder::createBoundingBox(VrOmTriMesh *pTriMesh) {
	using OpenMesh::Vec3f;
    VrOmTriMesh::ConstVertexIter vIt(pTriMesh->vertices_begin());
    VrOmTriMesh::ConstVertexIter vEnd(pTriMesh->vertices_end());
	Vec3f bbMin, bbMax;

    bbMin = bbMax = OpenMesh::vector_cast<Vec3f>(pTriMesh->point(vIt));

    for (size_t count=0; vIt!=vEnd; ++vIt, ++count)
    {
      bbMin.minimize( OpenMesh::vector_cast<Vec3f>(pTriMesh->point(vIt)));
      bbMax.maximize( OpenMesh::vector_cast<Vec3f>(pTriMesh->point(vIt)));
    }
	m_size[0] = bbMax[0] - bbMin[0] ;
	m_size[1] = bbMax[1] - bbMin[1] ;
	m_size[2] = bbMax[2] - bbMin[2] ;

	if(m_size[0] == bwRealTraits::Zero) m_size[0] = 1 ;
	if(m_size[1] == bwRealTraits::Zero) m_size[1] = 1 ;
	if(m_size[2] == bwRealTraits::Zero) m_size[2] = 1 ;

	p_ogreMesh->_setBounds(
		Ogre::AxisAlignedBox(bbMin[0],bbMin[1],bbMin[2], bbMax[0], bbMax[1], bbMax[2]));

	bwReal radius = sqrt((m_size[0]*m_size[0])+(m_size[1]*m_size[1])+(m_size[2]*m_size[2])) * bwRealTraits::Half ;
    p_ogreMesh->_setBoundingSphereRadius(radius);
}
void VrOgreMeshBuilder::build(VrOmTriMesh *pTriMesh) {
	/*pTriMesh->request_vertex_normals();
	pTriMesh->request_face_normals();*/
 // let the mesh update the normals
    //pTriMesh->update_normals();

	m_vertexCount = pTriMesh->n_vertices() ;
	bwAssert(m_vertexCount > 0) ;
	m_faceCount = pTriMesh->n_faces() ;
	createMesh() ;
	createVertexBuffer() ;
	createIndexBuffer() ;
	createNormalBuffer() ;
	createTextureCoordsBuffer() ;

	copyVertices(pTriMesh) ;
	copyFaces(pTriMesh) ;
	copyNormals(pTriMesh) ;
	copyTextureCoords(pTriMesh) ;

	createBoundingBox(pTriMesh) ;

	p_subMesh->setMaterialName(m_materialName) ;

   // dispose the face normals, as we don't need them anymore
    //pTriMesh->release_face_normals();
}
