/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _VrTriMeshDataOgreImporter_H
#define _VrTriMeshDataOgreImporter_H

#include "VrTriMeshDataBuilder.h"

#include <OGRE/OgreMesh.h>
#include <OGRE/OgreSubMesh.h>
#include <OGRE/OgreMeshManager.h>

class VrTriMeshDataOgreImporter : public VrTriMeshDataBuilder {
public:
	VrTriMeshDataOgreImporter(VrTriMeshData *pMesh) ;
	void copyVertices() ;
	void copyNormals() ;
	void copyFaces32() ;
	void copyFaces16() ;
	virtual void update() ;
	virtual void load() ;
	//Data
public:
	Ogre::MeshPtr p_ogreMesh ;
	Ogre::SubMesh *p_subMesh ; 
	Ogre::VertexData *p_vertexData ;
	Ogre::IndexData *p_indexData ;

	Ogre::HardwareVertexBufferSharedPtr p_posVertexBuffer ;
	Ogre::HardwareVertexBufferSharedPtr p_normVertexBuffer ;
	Ogre::HardwareVertexBufferSharedPtr p_texcoordsVertexBuffer ;
	Ogre::HardwareIndexBufferSharedPtr p_indexBuffer ;
} ;
class VrTriMeshDataOgreLoader : public VrTriMeshDataLoader {
public:
	VrTriMeshDataOgreLoader() {}
	virtual bool load(VrTriMeshData *pMesh) ;
	//Data Members
public:
};
#endif //_VrTriMeshDataOgreImporter_H
