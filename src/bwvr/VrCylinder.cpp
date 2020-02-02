/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <bwvr/VrCylinder.h>
#include <bwvr/VrVu.h>
#include <bwvr/VrBody.h>

VrCylinder::VrCylinder(VrGroup *pGroup) : VrShape(pGroup) {
	m_nodeType = NODE_CYLINDER ;
	vuInfo().setMeshName("VrCylinder.mesh") ;
	vuInfo().setMeshSize(bwSize3(1, 1, 1)) ;
}
void VrCylinder::validateMass() {
	/*void dMassSetCappedCylinder (dMass *m, dReal density, int direction,
			     dReal radius, dReal length)*/
	m_bodyInfo.setBox(m_size) ;
	VrShape::validateMass() ;
}
void VrCylinder::createGeom() {
	switch(getUpAxis()) {
		case AXIS_Z :
			m_geomID = dCreateCylinder(NULL, m_size[0] * .5f, m_size[2]) ;
			break ;
		case AXIS_Y :
			m_geomID = dCreateCylinder(NULL, m_size[0] * .5f, m_size[1]) ;
			break ;
		case AXIS_X :
			m_geomID = dCreateCylinder(NULL, m_size[2] * .5f, m_size[0]) ; //TODO:
			break ;
	}
	VrShape::createGeom() ;
}
void VrCylinder::validateGeom() {
	if(m_geomID == NULL)
		return ;
	//else
	VrShape::validateGeom() ;
	if(!invalidSize())
		return ;
	//else
	switch(getUpAxis()) {
		case AXIS_Z :
			dGeomCylinderSetParams(m_geomID, m_size[0] * .5f, m_size[2]) ;
			break ;
		case AXIS_Y :
			dGeomCylinderSetParams(m_geomID, m_size[0] * .5f, m_size[1]) ;
			break ;
		case AXIS_X :
			dGeomCylinderSetParams(m_geomID, m_size[2] * .5f, m_size[0]) ;
			break ;
	}
}
void VrCylinder::createConvex() {
	VrShape::createConvex() ;
}