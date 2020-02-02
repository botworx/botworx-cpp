/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _VrOgreMeshBuilder_H
#define _VrOgreMeshBuilder_H

#include "VrOgreMeshTool.h"

#include "VrOmTriMesh.h"

class VrOgreMeshBuilder : public VrOgreMeshTool {
public:
	VrOgreMeshBuilder(const bwString& pName) ;
	void createMesh() ;
	void createVertexBuffer() ;
	void createNormalBuffer() ;
	void createTextureCoordsBuffer() ;
	void createIndexBuffer() ;
	void copyVertices(VrOmTriMesh *pTriMesh) ;
	void copyFaces(VrOmTriMesh *pTriMesh) ;
	void copyNormals(VrOmTriMesh *pTriMesh) ;
	void copyTextureCoords(VrOmTriMesh *pTriMesh) ;
	void createBoundingBox(VrOmTriMesh *pTriMesh) ;
	void build(VrOmTriMesh *pTriMesh) ;
	void setMaterialName(const bwString& name) { m_materialName = name ; }
	bwSize3 getSize() { return m_size ; }
	//Data
public:
	bwSize3 m_size ;
	bwString m_materialName ;
} ;

#endif //_VrOgreMeshBuilder_H