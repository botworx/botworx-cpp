/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <bwvr/VrTriMeshData.h>
#include <bwvr/VrTriMeshDataBuilder.h>

VrTriMeshData::VrTriMeshData(BwPart *pOwner, const bwString& name) : BwPart(pOwner) {
	m_vertexStride = sizeof(bwVector3) ;
	m_indexStride = sizeof(vrTriFace) ;
	m_name = name ;
	p_loader = NULL ;
	m_isLoaded = false ;
	p_faces = NULL ;

	p_vertices = NULL ;
	p_normals = NULL ;
	m_vertexCount = 0 ;
	m_indexCount = 0 ;
	m_faceCount = 0 ;
//
	m_uses32bitIndex = false ;

}
void VrTriMeshData::load() {
	m_isLoaded = p_loader->load(this) ;
	onLoad() ;
}
void VrTriMeshData::onLoad() {
}
void VrTriMeshData::update() {
	p_loader->update(this) ;
}
bwSize3 VrTriMeshData::computeSize() {
	bwBounds3 bounds ;
	for(size_t i = 0 ; i < m_vertexCount ; ++i) {
		extendVolume(bounds, bwPoint3(p_vertices[i][0], p_vertices[i][1], p_vertices[i][2])) ;
	}
	bwPoint3 min = bounds.getMin() ;
	bwPoint3 max = bounds.getMax() ;
	bwReal width = max[0] - min[0] ;
	bwReal height = max[1] - min[1] ;
	bwReal length = max[2] - min[2] ;

	if(width == bwRealTraits::Zero) width = bwRealTraits::One ;
	if(height == bwRealTraits::Zero) height = bwRealTraits::One ;
	if(length == bwRealTraits::Zero) length = bwRealTraits::One ;

	return bwSize3(width, height, length) ;
}