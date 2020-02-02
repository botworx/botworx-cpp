/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <bwvr/VrBall.h>
#include <bwvr/VrVu.h>

VrBall::VrBall(VrGroup *pGroup) : VrShape(pGroup) {
	setNodeType(NODE_BALL) ;
	vuInfo().setMeshName("VrBall.mesh") ;
}
void VrBall::validateMass() {
	m_bodyInfo.setSphere(getRadius());
	VrShape::validateMass() ;
}
void VrBall::createGeom() {
	m_geomID = dCreateSphere(NULL, getRadius()) ;
	VrShape::createGeom() ;
}
void VrBall::validateGeom() {
	if(m_geomID == NULL)
		return ;
	//else
	VrShape::validateGeom() ;
	if(!invalidSize())
		return ;
	//else
	dGeomSphereSetRadius (m_geomID, getRadius()) ;
}
void VrBall::createConvex() {
	VrShape::createConvex() ;
}