/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <bwvr/VrHeightfield.h>

VrHeightfield::VrHeightfield(VrGroup *pGroup) : VrShape(pGroup) {
	setNodeType(NODE_HEIGHTFIELD) ;
	m_hfDataID = NULL ;
	setMotionType(MOTION_STATIC) ;
}
/*void VrHeightfield::validateMass() {
	m_bodyInfo.setSphere(getRadius());
	VrShape::validateMass() ;
}*/
void VrHeightfield::createGeom() {
	m_hfDataID = dGeomHeightfieldDataCreate();
	buildHfData() ;

	// Give some very bounds which, while conservative,
	// makes AABB computation more accurate than +/-INF.
	//dGeomHeightfieldDataSetBounds( m_hfDataID, REAL( -4.0 ), REAL( +6.0 ) );
	//dGeomHeightfieldDataSetBounds( m_hfDataID, REAL( -4.0 ), REAL( +100.0 ) );

	m_geomID = dCreateHeightfield(NULL, m_hfDataID, 1 );

	VrShape::createGeom() ;
}
void VrHeightfield::validateGeom() {
	if(m_geomID == NULL)
		return ;
	//else
	//VrShape::validateGeom() ;
	bwPoint3 pos = getPos() ;
	pos[1] -= m_size[1] * .5f ;
	setGeomPos(pos) ;
	setGeomQuat(getQuat()) ;
	//
	if(!invalidSize())
		return ;
	//else
	buildHfData() ;
}
void VrHeightfield::createConvex() {
	VrShape::createConvex() ;
}
/*
void dGeomHeightfieldDataBuildSingle( dHeightfieldDataID d,
                                     const float *pHeightData, int bCopyHeightData,
                                     dReal width, dReal depth, int widthSamples, int depthSamples,
                                     dReal scale, dReal offset, dReal thickness, int bWrap )
*/
void VrHeightfield::buildHfData() {
	//need different compile options based on bwReal size.
	int widthSamples = 513 ;
	int depthSamples = 513 ;

#if MATH_OPTION_SINGLE_PRECISION
dGeomHeightfieldDataBuildSingle( m_hfDataID,
                                     p_heightData, 0,
                                     m_size[0], m_size[2], widthSamples, depthSamples,
                                     m_size[1], 0, 1, 0) ;
#else
dGeomHeightfieldDataBuildDouble( m_hfDataID,
                                     p_heightData, 0,
                                     m_size[0], m_size[2], widthSamples, depthSamples,
                                     m_size[1], 0, 1, 0) ;
#endif
}