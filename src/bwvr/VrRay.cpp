/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <bwvr/VrRay.h>
#include <bwvr/VrRayCollider.h>
#include <bwvr/VrVu.h>
#include <bwvr/VrShapeCollider.h>
#include <bwvr/VrContactListener.h>
#include <bwvr/VrModelOps.h>

VrRay::VrRay(VrGroup *pGroup) : VrShape(pGroup) {
	//setNodeType(NODE_RAY) ;
	setNodeType(NODE_LINESEG) ;
	setSize(.1f, .1f, .1f) ;
	m_isAutoSleeper = false ;
	setMotionType(MOTION_KINEMATIC) ;
	vuInfo().setMeshName("BbLaser.mesh") ;
}
void VrRay::createGeom() {
	m_geomID = dCreateRay(NULL, getLength()) ;
	VrShape::createGeom() ;
}
void VrRay::validateGeom() {
	if(m_geomID == NULL)
		return ;
	//else
	VrShape::validateGeom() ;
	bwPoint3 start = getStart(*this) ;
	bwVector3 dir = getQuat() * bwVector3(0,0,getLength()) ;
	dGeomRaySet (m_geomID, start[0], start[1], start[2],
                  dir[0], dir[1], dir[2]);
}
void VrRay::createCollider() {
	p_collector = new VrContactCollector() ;
	p_collider = new VrRayCollider(this) ;
	p_collider->setListener(p_collector) ;
}