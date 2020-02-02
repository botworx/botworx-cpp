/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <bwvr/VrScenario.h>
#include <bwvr/VrScene.h>
#include <bwvr/VrSystem.h>
#include <bwvr/VrBuilder.h>
#include <bwvr/VrPhysics.h>
#include <bwvr/VrApplet.h>
#include <bwvr/VrWorld.h>
#include <bwvr/VrCamera.h>
#include <bwvr/VrHand.h>
#include <bwvr/VrModelOps.h>

#include <bwcore/BwStage.h>
#include <bwcore/BwKernel.h>

#include <bwvr/config/options_debug.h>
//TODO:?:didn't want to get tied to Ogre in this class ...but.
#include <bwvr/config/ogre.h>
////////////////////////////
template<> VrScenario* VrScenario::singleton::g_singleton = 0 ;

VrScenario::VrScenario(VrApplet *pApplet) : BwRunner(pApplet) {
	p_applet = pApplet ;
	p_scene = NULL ;
	p_world = NULL ;
	p_avatar = NULL ;
	p_camera = NULL ;
	p_hand = NULL ;
	//
	m_usesGround = true ;
	m_usesProps = true  ;
	//
	m_isLoaded = false ;
	//
#ifndef VR_OPTION_THREADING
	setIsRunner(false) ;
#endif
#if VR_OPTION_CORENDER
	setIsCoRunner(true) ;
#endif
}
VrScenario::~VrScenario() {
}
void VrScenario::doCreate(const BwPartInfo& info) {
	BwRunner::doCreate(info) ;
	createScene() ;
	createPhysics() ;
	//TODO:?:didn't want to get tied to Ogre in this class ...but.
	Ogre::ResourceGroupManager::getSingleton().createResourceGroup(getName());
}
bool VrScenario::onCreate(const BwPartInfo& info) {
	createWorld() ;
	VrPhysics::singleton::get().addModel(p_world) ;

	if(m_usesGround)
		createGround() ;
	if(m_usesProps)
		createProps() ;

	createAvatar() ;
	createCamera(p_world) ;
	createHand(p_world) ;

	//TODO:?:didn't want to get tied to Ogre in this class ...but.
	Ogre::ResourceGroupManager::getSingleton().initialiseResourceGroup(getName());
	Ogre::ResourceGroupManager::getSingleton().loadResourceGroup(getName());
	//
		p_stage->addActor(p_scene) ; //this IS necessary

	return BwRunner::onCreate(info) ;
}
bool VrScenario::die() { 
	return BwRunner::die() ; 
}
void VrScenario::onLoad() {
	m_isLoaded = true ;
	enableSky(true) ;
}
void VrScenario::createScene() {
}
void VrScenario::bind() {
	p_scene->bind() ;
}
void VrScenario::unbind() {
	p_scene->unbind() ;
}
//
void VrScenario::createPhysics() {
	VrPhysics& physics = *VrSystem::singleton::get().createPhysics(PHYSICS_DEFAULT, false) ; //configured & enabled by stage!
	physics.setOwner(this) ;
	p_stage->addActor(&physics) ; //this IS necessary
}
void VrScenario::createWorld() {
	p_world = new VrWorld(this) ;
	p_world->create() ;
}
void VrScenario::doPostDisable(bool sleeping) {
	if(!sleeping) {//ugh ... weird concept.
		unbind() ;
		Ogre::ResourceGroupManager::getSingleton().destroyResourceGroup(getName());
	}
	BwRunner::doPostDisable(sleeping) ;
}
void VrScenario::switchAvatar(VrModel *pAvatar) { 
	p_avatar = pAvatar ; 
	VrModel* pPrimary = p_avatar->getPrimary() ;
	if(p_camera != NULL) {
		p_camera->setLeader(pPrimary) ;
		p_camera->setPos(getRelPoint(*pPrimary, bwPoint3(0, 2, -10))) ;
	}
	//
	if(p_hand != NULL) {
		p_hand->setLeader(pPrimary) ;
		p_hand->setPos(getRelPoint(*pPrimary, bwPoint3(0, 2, 1))) ;
	}
}
void VrScenario::createCamera(VrGroup *pGroup) {
	p_camera = new VrCamera(pGroup) ;
	p_camera->setFollowDistance(10) ;
	p_camera->setFollowHeight(4) ;
	p_camera->create() ;
}
void VrScenario::createHand(VrGroup *pGroup) {
	p_hand = new VrHand(pGroup) ;
	p_hand->create() ;
}
void VrScenario::doStep(BwStepper& stepper) {
#if VR_OPTION_DEBUG_MATH
	int i = _controlfp(0,0) ;
	//i &= ~(EM_ZERODIVIDE|EM_OVERFLOW|EM_INVALID) ;
	i &= ~(EM_ZERODIVIDE|EM_INVALID) ;
	_controlfp(i,MCW_EM) ;
#endif
	BwRunner::doStep(stepper) ;
}
bwPath VrScenario::getMediaPath() {
	bwPath path = VrApplet::singleton::get().getMediaPath() / 
		"scenario" /
		getName() ;
	return path ;
}
VrBuilder* VrScenario::getBuilder() {
	return VrBuilder::singleton::getPtr() ;
}