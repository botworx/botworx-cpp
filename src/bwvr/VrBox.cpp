/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <bwvr/VrBox.h>
#include <bwvr/VrVu.h>

VrBox::VrBox(VrGroup *pGroup) : VrShape(pGroup) {
	setNodeType(NODE_BOX) ;
	vuInfo().setMeshName("VrBox.mesh") ;
}
void VrBox::validateMass() {
	m_bodyInfo.setBox(m_size) ;
	VrShape::validateMass() ;
}
void VrBox::createGeom() {
	m_geomID = dCreateBox(NULL, m_size[0], m_size[1], m_size[2]) ;
	VrShape::createGeom() ;
}
void VrBox::validateGeom() {
	if(m_geomID == NULL)
		return ;
	//else
	VrShape::validateGeom() ;
	if(!invalidSize())
		return ;
	//else
	dGeomBoxSetLengths (m_geomID, m_size[0], m_size[1], m_size[2]) ;
}
void VrBox::createConvex() {
	VrShape::createConvex() ;
}