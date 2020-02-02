/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _VrTriMeshData_H
#define _VrTriMeshData_H

#include <bwcore/BwPart.h>

class VrTriMeshDataLoader ;

class VrTriMeshData : public BwPart {
public:
	VrTriMeshData(BwPart *pOwner, const bwString& pName) ;
	virtual void load() ;
	virtual void onLoad() ;
	virtual void update() ;
	//Vertices
	void setVertexBuffer(bwVector3* pBuffer) { p_vertices = pBuffer ; }
	bwVector3* getVertexBuffer() { return p_vertices ; }
	void setVertexCount(size_t count) { m_vertexCount = count ; }
	size_t getVertexCount() { return m_vertexCount ; }
	void setVertexStride(int stride) { m_vertexStride = stride ; }
	size_t getVertexStride() { return m_vertexStride ; }
	//Normals
	void setNormalBuffer(bwVector3* pBuffer) { p_normals = pBuffer ; }
	bwVector3* getNormalBuffer() { return p_normals ; }
	//Faces
	void setFaceBuffer(vrTriFace* pBuffer) { p_faces = pBuffer ; }
	vrTriFace* getFaceBuffer() { return p_faces ; }
	void setFaceCount(size_t count) { m_faceCount = count ; }
	size_t getFaceCount() { return m_faceCount ; }
	//Indices
	vrIndex32* getIndices() { return ((vrIndex32*)p_faces) ; }
	void setIndexCount(size_t count) { m_indexCount = count ; }
	size_t getIndexCount() { return m_indexCount ; }
	void setIndexStride(int stride) { m_indexStride = stride ; }
	size_t getIndexStride() { return m_indexStride ; }
	void setUses32bitIndex(bool val) { m_uses32bitIndex = val ; }
	bool getUses32bitIndex() { return m_uses32bitIndex ; }
	//
	bool isLoaded() { return m_isLoaded ; }
	void setIsLoaded(bool val) { m_isLoaded = val ; }
	bwSize3 computeSize() ;
	void setLoader(VrTriMeshDataLoader *pLoader) { p_loader = pLoader ; }
	//Data
public:
	bool m_isLoaded ;
	VrTriMeshDataLoader *p_loader ;
	vrTriFace *p_faces ;

	bwVector3 *p_vertices ;
	bwVector3 *p_normals ;
	size_t m_vertexCount ;
	size_t m_vertexStride ;
	size_t m_indexCount ;
	size_t m_indexStride ;
	size_t m_faceCount ;
//
	bool m_uses32bitIndex ;
} ;

#endif //_VrTriMeshData_H
