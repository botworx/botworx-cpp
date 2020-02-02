/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <bwvr/VrCameraVu.h>
#include <bwvr/VrCamera.h>
#include <bwvr/VrScene.h>

#include <bwvr/config/ogre.h>

VrCameraVu::VrCameraVu(VrCamera *pCamera) : VrVu(pCamera) {
	p_camera = pCamera ;
	createCamera() ;
}
void VrCameraVu::createCamera() {
	p_ogreCamera = VrScene::singleton::get().getCamera() ;
/*	p_ogreCamera = p_scene->getManager()->createCamera(p_camera->getName());
	p_ogreCamera->setPosition(0,0,5);
	p_ogreCamera->lookAt(1, 1, -1);

	p_ogreCamera->setNearClipDistance( 1 );
	if (p_scene->getRenderRoot()->getRenderSystem()->getCapabilities()->hasCapability(Ogre::RSC_INFINITE_FAR_PLANE))
        p_ogreCamera->setFarClipDistance(0);
	else
		p_ogreCamera->setFarClipDistance( 1000 );

	p_scene->createViewport(p_ogreCamera) ;
*/
}
void VrCameraVu::doPostConfig() {
	bwVector3 camPos = p_camera->getPos() ;
	bwPoint3 focusPos = p_camera->getFocalPos() ;
	p_ogreCamera->setPosition(camPos[0], camPos[1], camPos[2]);
	p_ogreCamera->lookAt(focusPos[0], focusPos[1]+0.8, focusPos[2]);
}
bool VrCameraVu::onPostStep(BwStepper& stepper) {
	bwVector3 camPos = p_camera->getPos() ;
	bwPoint3 focusPos = p_camera->getFocalPos() ;
	p_ogreCamera->setPosition(camPos[0], camPos[1], camPos[2]);
	p_ogreCamera->lookAt(focusPos[0], focusPos[1]+0.8, focusPos[2]);
	return VrVu::onPostStep(stepper) ;
}