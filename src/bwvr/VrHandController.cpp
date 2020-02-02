/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <bwvr/VrHandController.h>
#include <bwvr/VrApplet.h>
#include <bwvr/VrScene.h>
#include <bwvr/VrHand.h>
#include <bwvr/VrScenario.h>

VrHandController::VrHandController(VrController *pSuper) : VrToolController(pSuper) {
	m_verticalMode = false ;
}
void VrHandController::bind() {
	VrToolController::bind() ;
	p_tool = p_hand = VrScenario::singleton::get().getHand() ;
}
void VrHandController::unbind() {
	VrToolController::unbind() ;
	p_tool = p_hand = NULL ;
}
bool VrHandController::processEvent(BwControllerEvent&& evt) {
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
void VrHandController::keyPressed(BwControllerEvent& evt) {
	switch(evt.getKey()) {
		case BwControllerEvent::KC_1 :
			p_hand->toggleMotionMode() ;
			break ;
	}
}
void VrHandController::keyReleased(BwControllerEvent& evt) {
}
void VrHandController::keyClicked(BwControllerEvent& evt) {
}
void VrHandController::mouseMoved (BwControllerEvent& evt) {
	//bwReal scale = 50 ;
	bwReal scale = .1f ;
	bwReal relX = evt.getRelX() ;
	bwReal relY = evt.getRelY() ;
	bwReal rotX = -relX * scale ;
	bwReal rotY = -relY * scale ;

	bwEuler followEuler = p_hand->getFollowEuler() ;
	followEuler[1] += rotX / bwReal(10) ;
	//followEuler[0] += rotY / 10 ;
	//pitch(followEuler, rotY / 10) ;
	//if(m_verticalMode) {
	if(evt.isControlDown()) {
		bwReal followHeight = p_hand->getFollowHeight() +  - (relY * scale) ;
		p_hand->setFollowHeight(followHeight) ;
	}
	else {
	bwReal followDist = p_hand->getFollowDistance() +  - (relY * scale) ;
	p_hand->setFollowDistance(followDist) ;
	}

	p_hand->setFollowEuler(followEuler) ;
}
void VrHandController::mouseDragged (BwControllerEvent& evt) { 
}
void VrHandController::mousePressed (BwControllerEvent& evt) {
	if(evt.getButton() == BwControllerEvent::LeftButton) {
			int grabMode = p_hand->getGrabMode() ;
			if(grabMode == VrHand::GM_NONE)
				p_hand->setGrabMode(VrHand::GM_GRAB) ;
			else
				p_hand->setGrabMode(VrHand::GM_NONE) ;
		//}
	}
}
void VrHandController::mouseReleased (BwControllerEvent& evt) {
}
