/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <bwvr/VrScene.h>
#include <bwvr/VrScenario.h>
#include <bwvr/VrApplet.h>
#include <bwvr/VrUser.h>

#include <bwcore/BwKernel.h>
#include <bwcore/_BwKernel.h>
#include <bwmessaging/BwMessaging.h>

#include <bwvr/config/ogre.h>
////////////////////////////
VrScene::VrScene(VrScenario *pScenario) : BwRunner(pScenario) {
	p_renderRoot = NULL ;
	p_renderWindow = NULL ;
	p_sceneManager = NULL ;
	p_overlay = NULL ;
	p_user = NULL ;
}
void VrScene::doCreate(const BwPartInfo& info) {
	BwActor::doCreate(info) ;
	VrApplet& applet = VrApplet::singleton::get() ;
	setRenderRoot(applet.getRenderRoot()) ;
	setRenderWindow(applet.getRenderWindow()) ;
	createManager() ;
	createCamera() ;
	//createWorldGeometry() ;
	createUser() ;
}
void VrScene::doPostDisable(bool sleeping) {
	if(!sleeping) {//ugh ... weird concept.
		clear() ;
	}
	BwRunner::doPostDisable(sleeping) ;
}
void VrScene::bind() {
	if(p_user != NULL)
		p_user->bind() ;
}
void VrScene::unbind() {
	p_user->unbind() ;
}
VrScene::~VrScene() {
}
void VrScene::clear() {
	using namespace Ogre;

	getManager()->destroyAllEntities();

	SceneNode *pRootNode = getManager()->getRootSceneNode();
	if (pRootNode) {
		if (pRootNode->numChildren())
			pRootNode->removeAllChildren();
	}
	//
	getRenderWindow()->removeAllViewports();
    getManager()->destroyAllCameras();
	getRenderRoot()->destroySceneManager(p_sceneManager) ;
}
void VrScene::createManager() {
	//p_sceneManager = p_renderRoot->getSceneManager(Ogre::ST_EXTERIOR_FAR) ;//What's up with Ogre?
	//p_sceneManager = p_renderRoot->getSceneManager(Ogre::ST_EXTERIOR_CLOSE) ;
	p_sceneManager = p_renderRoot->createSceneManager(Ogre::ST_EXTERIOR_CLOSE) ;

	//p_sceneManager = p_renderRoot->getSceneManager(Ogre::ST_GENERIC) ;
	//Lighting 
	//p_sceneManager->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);
	//p_sceneManager->setShadowTechnique(Ogre::SHADOWTYPE_TEXTURE_MODULATIVE);
	p_sceneManager->setShadowTechnique(Ogre::SHADOWTYPE_NONE);
}
void VrScene::createCamera() {
	p_camera = getManager()->createCamera("Camera1"); //need to fix this for multiple viewports...
	p_camera->setFixedYawAxis(true) ;
	p_camera->setPosition(0,0,5);
	p_camera->lookAt(1, 1, -1);

	p_camera->setNearClipDistance( 1 );
	if (getRenderRoot()->getRenderSystem()->getCapabilities()->hasCapability(Ogre::RSC_INFINITE_FAR_PLANE))
        p_camera->setFarClipDistance(0);
	else
		p_camera->setFarClipDistance( 1000 );

	VrApplet::singleton::get().createViewport(p_camera) ;
}
void VrScene::doStep(BwStepper& stepper) {
	bool success = startFrame() ;

	if(p_user != NULL)
		success = success & p_user->invokeStep(stepper) ;
}
void VrScene::doPostStep(BwStepper& stepper) {
	bool success = true ;
	endFrame() ;
	if(p_user != NULL)
		success = success & p_user->invokePostStep(stepper) ;

	if(!success) {
		_BwKernel::Event evt(_BwKernel::KERNEL_SHUTDOWN) ;
		BwKernel::singleton::get().getEventSlot()->send(evt) ;
	}
}
bool VrScene::startFrame() {
	onFrameStart() ;
	p_renderRoot->_fireFrameStarted() ;
	//p_renderWindow->update() ;
	bool success = p_renderRoot->_updateAllRenderTargets();
	return true ;
}
void VrScene::endFrame() {
	//bool success = p_renderRoot->_updateAllRenderTargets();
	p_renderRoot->_fireFrameEnded() ;
	onFrameEnd() ;
}
//singleton support
template<> VrScene::singleton::pointer VrScene::singleton::g_singleton = 0 ;
