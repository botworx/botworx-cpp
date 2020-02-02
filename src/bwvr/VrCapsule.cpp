/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <bwvr/VrCapsule.h>
#include <bwvr/VrVu.h>
#include <bwvr/VrBody.h>

VrCapsule::VrCapsule(VrGroup *pGroup) : VrShape(pGroup) {
	m_nodeType = NODE_CAPSULE ;
	vuInfo().setMeshName("VrCapsule.mesh") ;
	vuInfo().setMeshSize(bwSize3(1, 1, 2)) ;
}
void VrCapsule::validateMass() {
	/*void dMassSetCappedCylinder (dMass *m, dReal density, int direction,
			     dReal radius, dReal length)*/
	m_bodyInfo.setBox(m_size) ;
	VrShape::validateMass() ;
}
void VrCapsule::createGeom() {
	switch(getUpAxis()) {
		case AXIS_Z :
			m_geomID = dCreateCapsule(NULL, m_size[0] * .5f, m_size[2]) ;
			break ;
		case AXIS_Y :
			m_geomID = dCreateCapsule(NULL, m_size[0] * .5f, m_size[1]) ;
			break ;
		case AXIS_X :
			m_geomID = dCreateCapsule(NULL, m_size[2] * .5f, m_size[1]) ; //TODO:
			break ;
	}
	VrShape::createGeom() ;
}
void VrCapsule::validateGeom() {
	if(m_geomID == NULL)
		return ;
	//else
	VrShape::validateGeom() ;
	if(!invalidSize())
		return ;
	//else
	switch(getUpAxis()) {
		case AXIS_Z :
			dGeomCapsuleSetParams (m_geomID, m_size[0] * .5f, m_size[2]) ;
			break ;
		case AXIS_Y :
			dGeomCapsuleSetParams (m_geomID, m_size[0] * .5f, m_size[1]) ;
			break ;
		case AXIS_X :
			dGeomCapsuleSetParams (m_geomID, m_size[2] * .5f, m_size[1]) ; //TODO:
			break ;
	}
}