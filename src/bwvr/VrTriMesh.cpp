/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <bwvr/VrTriMesh.h>
#include <bwvr/VrTriMeshData.h>
#include <bwvr/VrTriMeshDataOgreImporter.h>
#include <bwvr/VrVu.h>

VrTriMesh::VrTriMesh(VrGroup *pGroup) : VrShape(pGroup) {
	//TODO:this is an abstract class ... use Convex or Concave!!!
	p_triMeshData = NULL ;
	m_meshDataID = NULL ;
}
//
void VrTriMesh::doCreate(const BwPartInfo& info) {
	createTriMeshData() ;
	VrShape::doCreate(info) ;
}
void VrTriMesh::validateMass() {
	//TODO:calculate mass based on mesh!!!
	m_bodyInfo.setBox(m_size) ;
	VrShape::validateMass() ;
}
void VrTriMesh::createTriMeshData() {
	if(p_triMeshData == NULL) {
		p_triMeshData = new VrTriMeshData(this, vuInfo().getMeshName()) ;
		p_triMeshData->create() ;
	}
	generateMesh() ; //custom mesh generation and sets loader
	p_triMeshData->load() ;
	setSize(p_triMeshData->computeSize()) ;
	vuInfo().setMeshSize(m_size) ;
}
void VrTriMesh::generateMesh() {
	p_triMeshData->setLoader(new VrTriMeshDataOgreLoader()) ;
}
//
void VrTriMesh::createGeom() {
	m_meshDataID = dGeomTriMeshDataCreate();
	buildMeshData() ;
	m_geomID = dCreateTriMesh(NULL, m_meshDataID, 0, 0, 0);

	VrShape::createGeom() ;

#if VR_OPTION_COLLISION_TC
	dGeomTriMeshEnableTC(m_geomID, dBoxClass, true) ;
	dGeomTriMeshEnableTC(m_geomID, dSphereClass, true) ;
	dGeomTriMeshEnableTC(m_geomID, dCCylinderClass, true) ;
#endif //VR_OPTION_COLLISION_TC
}
void VrTriMesh::validateGeom() {
	if(m_geomID == NULL)
		return ;
	//else
	VrShape::validateGeom() ;
	//
	if(!invalidSize())
		return ;
	//else
	buildMeshData() ;
}
void VrTriMesh::buildMeshData() {
	//need different compile options based on bwReal size.
#if MATH_OPTION_SINGLE_PRECISION
	dGeomTriMeshDataBuildSingle1(m_meshDataID, 
		p_triMeshData->getVertexBuffer(),
		p_triMeshData->m_vertexStride,
		p_triMeshData->getVertexCount(),
		p_triMeshData->getIndices(),
		p_triMeshData->m_indexCount,
		p_triMeshData->m_indexStride,
		p_triMeshData->p_normals
		);
#else
	dGeomTriMeshDataBuildDouble1(m_meshDataID, 
		p_triMeshData->getVertexBuffer(),
		p_triMeshData->m_vertexStride,
		p_triMeshData->getVertexCount(),
		p_triMeshData->getIndices(),
		p_triMeshData->m_indexCount,
		p_triMeshData->m_indexStride,
		p_triMeshData->p_normals
		);
#endif
}
void VrTriMesh::doPostEnable(bool sleeping) {
	captureTransform() ;
	VrShape::doPostEnable(sleeping) ;
}
bool VrTriMesh::onPostStep(BwStepper& stepper) {

	captureTransform() ;

	//TODO:call every n steps?
	#if VR_OPTION_COLLISION_TC
		//dGeomTriMeshClearTCCache(m_geomID) ;
	#endif //VR_OPTION_COLLISION_TC

	return VrShape::onPostStep(stepper) ;
}
// set previous transformation matrix for trimesh
void VrTriMesh::captureTransform()
{
	const dReal* Pos = dGeomGetPosition(m_geomID);
	const dReal* Rot = dGeomGetRotation(m_geomID);

	const double Transform[16] = 
	{
		Rot[0], Rot[4], Rot[8],  0,
		Rot[1], Rot[5], Rot[9],  0,
		Rot[2], Rot[6], Rot[10], 0,
		Pos[0], Pos[1], Pos[2],  1
	};
	dGeomTriMeshSetLastTransform( m_geomID, *(dMatrix4*)(&Transform) );
}