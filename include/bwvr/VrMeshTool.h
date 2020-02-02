/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _VrMeshTool_H
#define _VrMeshTool_H

class VrMeshTool {
public:
	VrMeshTool(const bwString& pName) { m_meshName = pName ; }
	//Data
public:
	bool m_isLoaded ;
	bwString m_meshName ;

	bwVector3 *p_vertices ;
	bwVector3 *p_normals ;
	size_t m_vertexCount ;
	size_t m_vertexStride ;
	size_t m_indexCount ;
	size_t m_indexStride ;
	size_t m_faceCount ;
} ;

#endif //_VrMeshTool_H