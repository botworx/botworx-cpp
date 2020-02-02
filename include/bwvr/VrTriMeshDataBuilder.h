/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _VrTriMeshDataBuilder_H
#define _VrTriMeshDataBuilder_H

#include <bwcore/BwPart.h>

class VrTriMeshData ;

//this is pretty much an abstract class ...
class VrTriMeshDataBuilder {
public:
	VrTriMeshDataBuilder(VrTriMeshData *pTriMeshData) : p_triMeshData(pTriMeshData) {}
	void copyVertices() ;
	void copyNormals() ;
	void copyFaces32() ;
	void copyFaces16() ;
	virtual void update() {}
	virtual void load() {}
	//Data
public:
	VrTriMeshData *p_triMeshData ;
} ;
class VrTriMeshDataLoader {
public:
	VrTriMeshDataLoader() {}
	virtual bool load(VrTriMeshData *pMesh) { return false ; }
	virtual bool update(VrTriMeshData *pMesh) { return false ; }
};

#endif //_VrTriMeshDataBuilder_H
