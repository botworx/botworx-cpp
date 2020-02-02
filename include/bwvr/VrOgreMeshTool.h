/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _VrOgreMeshTool_H
#define _VrOgreMeshTool_H

#include "VrMeshTool.h"
#include <bwvr/VrScenario.h>

#include <OGRE/OgreMesh.h>

namespace Ogre {
	class SubMesh ; 
	class VertexData ;
	class IndexData ;
	class VertexBufferBinding ;
	class VertexDeclaration ;
	class HardwareVertexBufferSharedPtr ;
	class HardwareIndexBufferSharedPtr ;
}

class VrOgreMeshTool : public VrMeshTool {
public:
	VrOgreMeshTool(const bwString& pName) : VrMeshTool(pName) {}
	Ogre::MeshPtr getOgreMesh() { return p_ogreMesh ; }
	//Data
public:
	Ogre::MeshPtr p_ogreMesh ;
	Ogre::SubMesh *p_subMesh ; 
	Ogre::VertexData *p_vertexData ;
	Ogre::IndexData *p_indexData ;
	Ogre::VertexBufferBinding *p_vBind ;
	Ogre::VertexDeclaration *p_vDecl ;
	Ogre::HardwareVertexBufferSharedPtr p_posVertexBuffer ;
	Ogre::HardwareVertexBufferSharedPtr p_normVertexBuffer ;
	Ogre::HardwareVertexBufferSharedPtr p_texcoordsVertexBuffer ;
	Ogre::HardwareIndexBufferSharedPtr p_indexBuffer ;
} ;

#endif //_VrOgreMeshTool_H