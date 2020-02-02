/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _VrTriMeshDataOmImporter_H
#define _VrTriMeshDataOmImporter_H

#include "VrTriMeshDataBuilder.h"

class VrOmTriMesh ;

class VrTriMeshDataOmImporter : public VrTriMeshDataBuilder {
public:
	VrTriMeshDataOmImporter(VrTriMeshData *pMesh, VrOmTriMesh *pSrcMesh) ;
	void copyVertices() ;
	void copyNormals() ;
	void copyFaces32() ;
	void copyFaces16() ;
	virtual void update() ;
	virtual void load() ;
	//Data Members
public:
	VrOmTriMesh *p_srcMesh ;
	size_t m_vertexCount ;
	size_t m_faceCount ;
} ;
class VrTriMeshDataOmLoader : public VrTriMeshDataLoader {
public:
	VrTriMeshDataOmLoader(VrOmTriMesh *pSrcMesh) : p_srcMesh(pSrcMesh), VrTriMeshDataLoader() {}
	virtual bool load(VrTriMeshData *pMesh) ;
public:
	//Data Members
	VrOmTriMesh *p_srcMesh ;
};
#endif //_VrTriMeshDataOmImporter_H
