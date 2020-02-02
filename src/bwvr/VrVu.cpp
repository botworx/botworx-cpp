/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <bwvr/config/options_debug.h>
#include <bwvr/config/options_vu.h>
#include <bwvr/VrVu.h>
#include <bwvr/VrShape.h>
#include <bwvr/VrGroup.h>
#include <bwvr/VrScene.h>
#include <bwvr/VrScenario.h>
#include <bwvr/VrApplet.h>
//

#include <bwvr/config/ogre.h>

using namespace Ogre ;

VrVu::VrVu(VrModel *pModel) : BwActor(pModel) {
	p_model = pModel ;
	setIsStageDriven(false) ;
	p_sceneNode = NULL ;
	p_meshInstance = NULL ;
	m_scale = bwSize3(1,1,1) ;
	m_isBatchable = true ;
}
VrVu::~VrVu() {
}
void VrVu::doCreate(const BwPartInfo& info) {
	BwActor::doCreate(info) ;
	//setVuInfo(p_model->vuInfo()) ;
	//createAssets() ;
}
bool VrVu::onCreate(const BwPartInfo& info) {
	return BwActor::onCreate(info) ;
}
void VrVu::createAssets() {
#if VR_OPTION_SHAREDVU
	if(m_isBatchable && 
		!VrScenario::singleton::get().isOperational() && 
		(p_model->getMotionType() == MOTION_STATIC)
		) {
		createMeshInstance() ;
		return ;
	}
#endif
	createSceneNode() ;

	createMeshInstance() ;
	attachMeshInstance() ;
}
void VrVu::doEnable(bool sleeping) {
	if(!isOperational()) {
		setVuInfo(p_model->vuInfo()) ;
		createAssets() ;
	}
	BwActor::doEnable(sleeping) ;
}
void VrVu::doPostEnable(bool sleeping) {
	if(vuInfo().getIsAutoScaler())
		setScale(p_model->getSize()) ;
	if(p_sceneNode != NULL)
		p_sceneNode->setVisible(true) ;
	updateScene() ;
	BwActor::doPostEnable(sleeping) ;
}
void VrVu::doDisable(bool sleeping) { 
	if(p_sceneNode != NULL && !sleeping)
		p_sceneNode->setVisible(false) ;
	BwActor::doDisable(sleeping) ;
}
void VrVu::doPostDisable(bool sleeping) {
	if(sleeping)
		updateScene() ;
	else {
		if(p_sceneNode != NULL) {
			Ogre::SceneNode *pParent = static_cast<Ogre::SceneNode*>(p_sceneNode->getParent() ) ;
			pParent->removeAndDestroyChild(p_sceneNode->getName()) ;
			#if VR_OPTION_DEBUG_BOUNDS
			pParent->removeAndDestroyChild(p_boundingNode->getName()) ;
			#endif
		}
	}
	BwActor::doPostDisable(sleeping) ;
}
void VrVu::setScale(const bwSize3& scale) {
	m_scale[0] = scale[0] / m_vuInfo.m_meshSize[0] ;
	m_scale[1] = scale[1] / m_vuInfo.m_meshSize[1] ;
	m_scale[2] = scale[2] / m_vuInfo.m_meshSize[2] ;

	if(p_sceneNode != NULL)
		p_sceneNode->setScale(m_scale[0], m_scale[1], m_scale[2] );
}

void VrVu::createMeshInstance() {
	if(m_vuInfo.m_meshName.empty())
		return ;
    p_meshInstance = VrScene::singleton::get().getManager()->createEntity(p_model->getName(), m_vuInfo.m_meshName);
	//
	if(m_vuInfo.m_meshSize == bwSize3()) {
		const AxisAlignedBox& aabox = p_meshInstance->getMesh()->getBounds() ;
		Vector3 size = aabox.getMaximum() - aabox.getMinimum() ;
		m_vuInfo.m_meshSize = bwSize3(size[0], size[1], size[2]) ;
	}
	//
	if(!m_vuInfo.m_materialName.empty()) {
		Ogre::SubEntity* pSubEntity = p_meshInstance->getSubEntity(0) ;
		pSubEntity->setMaterialName(m_vuInfo.m_materialName) ;
	}
}
void VrVu::attachMeshInstance() {
	if(p_meshInstance != NULL)
		if(p_sceneNode != NULL)
			p_sceneNode->attachObject(p_meshInstance);
}
void VrVu::createSceneNode() {
	p_sceneNode = static_cast<Ogre::SceneNode*>(VrScene::singleton::get().getManager()->getRootSceneNode()->createChild());
	p_sceneNode->setVisible(false) ;
	#if VR_OPTION_DEBUG_BOUNDS
	p_boundingNode = static_cast<Ogre::SceneNode*>(p_scene->getManager()->getRootSceneNode()->createChild());
	p_boundingNode->attachObject(p_scene->getManager()->createEntity(p_model->makeThingName("Bound"), "VrBox.mesh"));
	p_boundingNode->setVisible(false) ;
	#endif
}
bool VrVu::onPostStep(BwStepper& stepper) {
	updateScene() ;
	return true ;
}
void VrVu::updateScene() {
	validateNode() ;

	#if VR_OPTION_DEBUG_BOUNDS
	bwPoint3 center = p_model->getCollider()->getNode()->getPos() ;
	bwBounds3 bounds = p_model->getCollider()->getNode()->getBounds() ;
	bwSize3 size = bounds.getMax() - bounds.getMin() ;
	if(p_boundingNode != NULL) {
		p_boundingNode->setPosition(center[0], center[1], center[2]);
		p_boundingNode->setScale(size[0], size[1], size[2]) ;
		p_boundingNode->showBoundingBox(true) ;
	}
	#endif

	#if VR_OPTION_DEBUG_SLEEP
	if(!p_model->isPureStatic() && p_model->isSleeping())
		setShowBoundingBox(true) ;
	else
		setShowBoundingBox(false) ;
	#endif
}
void VrVu::validateNode() {
	bwPoint3 pos ;
	bwQuat quat ;
	VrGroup *pGroup = p_model->getGroup() ;
	if(pGroup == NULL)
		return ;
	pos = p_model->getPos() ;
	if(p_sceneNode != NULL)
		p_sceneNode->setPosition(pos[0], pos[1], pos[2]);

	quat = p_model->getQuat() ;
	if(p_sceneNode != NULL)
		p_sceneNode->setOrientation(quat[3],quat[0],quat[1],quat[2]);
}
void VrVu::setShowBoundingBox(bool flag) {
	if(p_sceneNode != NULL)
		p_sceneNode->showBoundingBox(flag) ;
}
