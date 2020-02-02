/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <bwvr/VrCameraController.h>
#include <bwvr/VrApplet.h>
#include <bwvr/VrScenario.h>
#include <bwvr/VrScene.h>
#include <bwvr/VrCamera.h>
#include <bwvr/VrScenario.h>
//
#include <bwcontrol/BwBrain.h>

VrCameraController::VrCameraController(VrController *pSuper) : VrToolController(pSuper) {
}
void VrCameraController::bind() {
	VrToolController::bind() ;
	p_tool = p_camera = VrScenario::singleton::get().getCamera() ;
}
void VrCameraController::unbind() {
	VrToolController::unbind() ;
	p_tool = p_camera = NULL ;
}
bool VrCameraController::processEvent(BwControllerEvent&& evt) {
	switch(evt.what()) {
		case BwControllerEvent::EVENT_KEYBOARD_PRESSED :
			keyPressed(evt) ;
			break ;
		case BwControllerEvent::EVENT_KEYBOARD_RELEASED :
			keyReleased(evt) ;
			break ;
		case BwControllerEvent::EVENT_MOUSE_MOVED :
			mouseMoved(evt) ;
			break ;
		case BwControllerEvent::EVENT_MOUSE_DRAGGED :
			mouseDragged(evt) ;
			break ;
		case BwControllerEvent::EVENT_MOUSE_PRESSED :
			mousePressed(evt) ;
			break ;
		case BwControllerEvent::EVENT_MOUSE_RELEASED :
			mouseReleased(evt) ;
			break ;
	}
	return true ;
}
void VrCameraController::keyPressed(BwControllerEvent& evt) {
	switch(evt.getKey()) {
		case BwControllerEvent::KC_1 :
			p_camera->getBrain()->useTask("FOLLOW_FOLLOW") ;
			break ;
		case BwControllerEvent::KC_2 :
			p_camera->getBrain()->useTask("FOLLOW_LOOK") ;
			break ;
		case BwControllerEvent::KC_3 :
			p_camera->getBrain()->useTask("LOOK_LOOK") ;
			break ;
	}
}
void VrCameraController::keyReleased(BwControllerEvent& evt) {
}
void VrCameraController::keyClicked(BwControllerEvent& evt) {
}
void VrCameraController::mouseMoved (BwControllerEvent& evt) {
	//bwReal scale = 50 ;
	bwReal scale = .1f ;

	bwReal rotX = -evt.getRelX() * scale ;
	bwReal rotY = -evt.getRelY() * scale ;

	bwEuler followEuler = p_camera->getFollowEuler() ;
	followEuler[1] += rotX / 10 ;
	followEuler[0] += rotY / 10 ;
	//pitch(followEuler, rotY / 10) ;

	p_camera->setFollowEuler(followEuler) ;
}
void VrCameraController::mouseDragged (BwControllerEvent& evt) { 
}
void VrCameraController::mousePressed (BwControllerEvent& evt) {
}
void VrCameraController::mouseReleased (BwControllerEvent& evt) {
}

