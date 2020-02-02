/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"
///
///
///
#include <bwvr/VrPlane.h>
#include <bwvr/VrVu.h>
#include <bwvr/VrScene.h>
#include <bwvr/VrScenario.h>

#include <bwvr/config/ogre.h>

#include <bwvr/VrLay.h>

class VrShape ;
class VrPlane ;

class VrPlaneVu : public VrVu {
public:
	VrPlaneVu(VrPlane *pGround) : VrVu (pGround) {
		m_isBatchable = false ;
		p_ground = pGround ;
	}
	virtual void createMeshInstance() {
		bwString meshName = p_model->getName() + "_Mesh" ;
		bwReal planeWidth = p_model->getWidth() ;
		bwReal planeHeight = p_model->getLength() ;
		Ogre::Plane ogrePlane ;
		ogrePlane.normal = Ogre::Vector3::UNIT_Y;
		ogrePlane.d = 0;
		Ogre::MeshManager::getSingleton().createPlane(meshName,
			VrScenario::singleton::get().getName(),
			ogrePlane,planeWidth,planeHeight,5,5,true,1,40,40,Ogre::Vector3::UNIT_Z);
		p_meshInstance = VrScene::singleton::get().getManager()->createEntity(p_ground->getName(), meshName);
		p_meshInstance->setMaterialName(vuInfo().getMaterialName());
	}
//Data Members
public:
	VrPlane *p_ground ;
};

///
///
///

VrPlane::VrPlane(VrGroup *pGroup) : VrShape(pGroup) {
	setMotionType(MOTION_STATIC) ;
	setIsPlaceable(false) ;
	setNodeType(NODE_PLANE) ;
	vuInfo().setIsAutoScaler(false) ;
}
void VrPlane::createVu() {
	p_vu = new VrPlaneVu(this) ;
	p_vu->create() ;
}
void VrPlane::createGeom() {
	//m_geomID = dCreatePlane(NULL, 0, 1, 0, 0);
	bwVector3 normal = makeVec(getQuat()) ;
	bwReal d = -bwmath::distance(getPos(), bwPoint3()) ;
	m_geomID = dCreatePlane(NULL, normal[0], normal[1], normal[2], d);
	VrShape::createGeom() ;
}
void VrPlane::validateGeom() {
	if(m_geomID == NULL)
		return ;
	//else
	VrShape::validateGeom() ;
	//dGeomPlaneSetParams (m_geomID, 0, 1, 0, 0); //TODO: ...
	bwVector3 normal = makeVec(getQuat()) ;
	bwReal d = -bwmath::distance(getPos(), bwPoint3()) ;
	dGeomPlaneSetParams(m_geomID, normal[0], normal[1], normal[2], d);
}
void VrPlane::createConvex() {
	VrShape::createConvex() ;
}