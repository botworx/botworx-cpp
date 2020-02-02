/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _VrOmTriMesh_H
#define _VrOmTriMesh_H

#include <bwvr/config/openmesh.h>
//
struct VrOmTriMeshTraits : OpenMesh::DefaultTraits
{
	// add normal property to vertices and faces
	VertexAttributes ( (OpenMesh::Attributes::Normal | OpenMesh::Attributes::TexCoord2D) );
	FaceAttributes    ( OpenMesh::Attributes::Normal );
};
class VrOmTriMesh : public OpenMesh::TriMesh_ArrayKernelT<VrOmTriMeshTraits> {
public:
	//void create() {}
private:
	//
	typedef OpenMesh::Subdivider::Uniform::Sqrt3T<VrOmTriMesh>			Sqrt3;
	typedef OpenMesh::Subdivider::Uniform::LoopT<VrOmTriMesh>            Loop;
	typedef OpenMesh::Subdivider::Uniform::CompositeSqrt3T<VrOmTriMesh> CompositeSqrt3;
	typedef OpenMesh::Subdivider::Uniform::CompositeLoopT< VrOmTriMesh>  CompositeLoop;

	typedef Sqrt3 Subdivider ;
	//
public:
	void subdivide(size_t n) ;
};

#endif //_VrOmTriMesh_H