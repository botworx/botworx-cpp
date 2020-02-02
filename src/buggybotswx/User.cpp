/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include "User.h"

#include <bwvr/VrApplet.h>
#include <bwvr/VrScene.h>
#include <bwvr/VrWorld.h>
#include <bwvr/VrCameraController.h>
#include <bwvr/VrHandController.h>
#include <bwvr/VrAvatarController.h>
#include <bwvr/VrCamera.h>
#include <bwvr/VrHand.h>

#include "UserModes.h"
#include "BwxInjector.h"

User::User(VrScene *pScene, wxFrame *pFrame, BwxVrCtrl* pCtrl) : BwxUser(pScene, pFrame, pCtrl) {
}
void User::doCreate(const BwPartInfo& info) {
	BwxUser::doCreate(info) ;
	BwxUserMode *pMainMode = new BbxMainMode(this, "Buggy Bots") ;
	pMainMode->create() ;
	pushMode(pMainMode) ;
}
bool User::processEvent(BwControllerEvent&& evt) {
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
	return BwxUser::processEvent(evt) ;
}
void User::keyPressed(BwControllerEvent& evt) {
	switch(evt.getKey()) {
		case BwControllerEvent::KC_C : {
			bwString ssPath ;
			ssPath = "../ScreenShots/" ;
			ssPath = ssPath + p_scene->getApplet()->getName() ;
			p_scene->getRenderWindow()->writeContentsToTimestampedFile(ssPath, ".screen.jpg");
			}
			break ;
		case BwControllerEvent::KC_ESCAPE :
			popMode() ;
			if(m_modeStack.empty())
				requestShutdown() ; //f6:fixme!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			break ;
		case BwControllerEvent::KC_F1 :
			//f6:fixme:move main guicontroller reference to VrUser???
			//setToolController(getGuiController()) ;
			break ;
		case BwControllerEvent::KC_F2 :
			//setToolController(this->p_handCtrlr) ;
			break ;
		case BwControllerEvent::KC_F3 :
			setToolController(this->p_camCtrlr) ;
			break ;
	}
}
void User::keyReleased(BwControllerEvent& evt) {
}
void User::keyClicked(BwControllerEvent& evt) {
}
void User::mouseMoved (BwControllerEvent& evt) {
}
void User::mouseDragged (BwControllerEvent& evt) { 
}
void User::mousePressed (BwControllerEvent& evt) {
	if(evt.getButton() == BwControllerEvent::RightButton) {
	//Toggle between tool and gui
		if(m_useTool)
			m_useTool = false ;
		else
			m_useTool = true ;

		if(m_useTool)
			p_injector->captureMouse() ;
		else
			p_injector->releaseMouse() ;
		/*if(p_toolController == p_handCtrlr) {
			//setToolController(p_guiController) ;
		}
		else {
			setToolController(p_handCtrlr) ;
		}*/
	}
}
void User::mouseReleased (BwControllerEvent& evt) {
}