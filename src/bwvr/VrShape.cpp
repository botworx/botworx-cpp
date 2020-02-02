/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <bwvr/VrSystem.h>
#include <bwvr/VrScenario.h>
#include <bwvr/VrWorld.h>
#include <bwvr/VrGroup.h>
#include <bwvr/VrShape.h>
#include <bwvr/VrBody.h>
#include <bwvr/VrShapeCollider.h>
#include <bwvr/VrCollision.h>
#include <bwvr/VrScene.h>
#include <bwvr/VrVu.h>
#include <bwvr/VrPhysics.h>
#include <bwvr/VrDynamicAssembly.h>
#include <bwvr/VrBody.h>
#include <bwvr/VrSurfaceInfo.h>
#include <bwvr/VrLay.h>

VrShape::VrShape(VrGroup *pGroup) : VrModel(pGroup) {
	setMotionType(MOTION_DYNAMIC) ;
	m_isAutoSleeper = true ;
	//
	p_convex = NULL ;
	m_geomID = NULL ;
}
VrShape::~VrShape() {
	if(m_geomID != NULL)
		dGeomDestroy(m_geomID) ;
}
void VrShape::doCreate(const BwPartInfo& info) {
	VrModel::doCreate(info) ;
	createGeom() ;
	createConvex() ;
}
void VrShape::doEnable(bool sleeping) {
	if(getMotionType() == MOTION_STATIC)
		sleeping = true ;
	enableGeom() ;
	VrModel::doEnable(sleeping) ;
}
void VrShape::enableGeom() {
	if(m_geomID == NULL)
		return ;
	dGeomEnable(m_geomID) ;
}
void VrShape::doDisable(bool sleeping) {
	if(!sleeping) //this means we are REALLY disabling this shape.
		disableGeom() ;
	VrModel::doDisable(sleeping) ;
}
void VrShape::disableGeom() {
	if(m_geomID == NULL)
		return ;
		dGeomDisable(m_geomID) ;
}
void VrShape::doValidate() {
	VrModel::doValidate() ;
	if(m_geomID != NULL)
		validateGeom() ;
	if(p_convex != NULL)
		validateConvex() ;
}
void VrShape::validateGeom() {
	if(m_geomID == NULL)
		return ;
	//else
	setGeomPos(getPos()) ;
	//setGeomQuat(getQuat()) ;
	switch(getUpAxis()) {
		case AXIS_Z :
			setGeomQuat(getQuat()) ;
			break ;
		case AXIS_Y :
		case AXIS_X :
			setGeomQuat(getQuat() * m_alignment) ;
			break ;
	}
}
void VrShape::createCollider() {
	p_collider = new VrShapeCollider(this) ;
}
//TODO:need unembed too!
void VrShape::embed() {
	//TODO:need to delete old body if it exists.
	bwAssert(p_body == NULL) ;
	p_body = p_group->getBody() ;
	setMotionType(MOTION_FIXED) ;
}
//TODO:improveme:make sure all class derivatives createGeom call this one!
void VrShape::createGeom() {
	if(m_geomID == NULL)
		return ;
	dGeomSetData(m_geomID, this) ;
	validateGeom() ;
}
void VrShape::setGeomQuat(const bwQuat &quat) {
	dQuaternion dQuat ;
	dQuat[0] = quat[3] ;
	dQuat[1] = quat[0] ;
	dQuat[2] = quat[1] ;
	dQuat[3] = quat[2] ;

	if(m_isPlaceable && m_geomID != NULL)
		dGeomSetQuaternion(m_geomID, dQuat) ;
}
void VrShape::setGeomPos(const bwPoint3& pos) {
	if(m_isPlaceable && m_geomID != NULL) {
		dGeomSetPosition(m_geomID, pos[0], pos[1], pos[2]) ;
	}
}
void VrShape::createConvex() {
	if(p_convex == NULL)
		return ;
}
void VrShape::validateConvex() {
	if(p_convex == NULL)
		return ;
}
