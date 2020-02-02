#ifndef _BwcPolyGroup_H
#define _BwcPolyGroup_H

#include <bwvr/VrOmTriMesh.h>

class BwcGeometry ;

class BwcPolyGroup {
public:
	BwcPolyGroup(BwcGeometry* pGeometry) {
		p_geometry = pGeometry ;
		m_indexStride = 0 ;
		m_vertexOffset = -1 ;
	}
	BwcGeometry& geometry() { return *getGeometry() ; }
	BwcGeometry* getGeometry() { return p_geometry ; }
	//Data Members
	BwcGeometry* p_geometry ;
	size_t	m_faceCount ;
	size_t	m_indexStride ;
	size_t	m_vertexCount ;
	size_t	m_vertexStride ;
	//
	size_t	m_vertexOffset ;
	//
	domInputLocalOffset_Array m_inputArray ;
	size_t m_inputCount ;
	domListOfUInts m_indexArray ;
	size_t m_indexCount ;
	//
	//
	VrOmTriMesh m_mesh ;
	std::vector<VrOmTriMesh::VertexHandle> m_vertices ;
};
typedef std::vector<BwcPolyGroup*> BwcPolyGroups ;
typedef BwcPolyGroups::iterator  BwcPolyGroupIter ;

inline bwSize3 createBoundingBox(VrOmTriMesh& mesh) {
	using OpenMesh::Vec3f;
    VrOmTriMesh::ConstVertexIter vIt(mesh.vertices_begin());
    VrOmTriMesh::ConstVertexIter vEnd(mesh.vertices_end());
	Vec3f bbMin, bbMax;
    
    bbMin = bbMax = OpenMesh::vector_cast<Vec3f>(mesh.point(vIt));
    
    for (size_t count=0; vIt!=vEnd; ++vIt, ++count) {
      bbMin.minimize( OpenMesh::vector_cast<Vec3f>(mesh.point(vIt)));
      bbMax.maximize( OpenMesh::vector_cast<Vec3f>(mesh.point(vIt)));
    }
	bwSize3 result ;
	result[0] = bbMax[0] - bbMin[0] ;
	result[1] = bbMax[1] - bbMin[1] ;
	result[2] = bbMax[2] - bbMin[2] ;

	return result ;
}

#endif //_BwcPolyGroup_H