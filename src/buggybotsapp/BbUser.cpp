/*BuggyBots - A Botworx VR reference app and AI playground
Copyright (C) 2005  Kurtis Fields. See BuggyBots_License.txt for details.
*/
#include "stdafx.h"

#include "BbUser.h"
#include "BbUserModes.h"
#include "BbGui.h"

#include <buggybots/BbApplet.h>

#include <bwvr/VrScene.h>
#include <bwcontrol/BwControllerEvent.h>
#include <bwvr/VrAvatarController.h>
#include <bwvr/VrCameraController.h>
#include <bwvr/VrHandController.h>
#include <bwvrcegui/VrCeguiGuiController.h>

#include <bwvr/config/ogre.h>

//BbUser::BbUser(VrScene *pScene) : VrUser(pScene) {
BbUser::BbUser(VrScene *pScene) : VrCeguiUser(pScene) {
}
void BbUser::doCreate(const BwPartInfo& info) {
	VrUser::doCreate(info) ;
	VrCeguiUserMode *pMainMode = new BbMainMode(this, "Buggy Bots") ;
	pMainMode->create() ;
	//pushMode(pMainMode) ;
	pMainMode->activate() ;
	setToolController(getGuiController()) ;
}
void BbUser::createGui() { 
	p_gui = new BbGui(p_scene) ;
	p_gui->create() ;
	p_guiController = new VrCeguiGuiController(this, p_gui) ;
	p_guiController->create() ;
}
bool BbUser::processEvent(BwControllerEvent&& evt) {
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
	p_avatarController->processEvent(std::move(evt)) ;
	//
	p_toolController->processEvent(std::move(evt)) ;

	return true ;
}
void BbUser::keyPressed(BwControllerEvent& evt) {
	switch(evt.getKey()) {
		case BwControllerEvent::KC_P : {
			bwPath ssPath = BwKernel::singleton::get().getMediaPath() / bwPath("ScreenShots") ;
			ssPath = ssPath / VrApplet::singleton::get().getName() ;
			//p_scene->getRenderWindow()->writeContentsToTimestampedFile(ssPath.native_file_string(), ".screen.jpg");
			p_scene->getRenderWindow()->writeContentsToTimestampedFile(ssPath.string(), ".screen.jpg");
			}
			break ;
		case BwControllerEvent::KC_ESCAPE :
			popMode() ;
			if(m_modeStack.empty())
				requestShutdown() ; //TODO:?
			break ;
		case BwControllerEvent::KC_F1 :
			//TODO:move main guicontroller reference to VrUser???
			setToolController(getGuiController()) ;
			break ;
		case BwControllerEvent::KC_F2 :
			setToolController(this->p_handCtrlr) ;
			break ;
		case BwControllerEvent::KC_F3 :
			setToolController(this->p_camCtrlr) ;
			break ;
	}
}
void BbUser::keyReleased(BwControllerEvent& evt) {
}
void BbUser::keyClicked(BwControllerEvent& evt) {
}
void BbUser::mouseMoved (BwControllerEvent& evt) {
}
void BbUser::mouseDragged (BwControllerEvent& evt) { 
}
void BbUser::mousePressed (BwControllerEvent& evt) {
	if(evt.getButton() == BwControllerEvent::RightButton) {
	//Toggle between hand and gui
		if(p_toolController == p_handCtrlr) {
			setToolController(p_guiController) ;
		}
		else {
			setToolController(p_handCtrlr) ;
		}
	}
}
void BbUser::mouseReleased (BwControllerEvent& evt) {
}