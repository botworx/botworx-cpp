/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"


#include <bwvrcegui/VrCeguiGuiController.h>
#include <bwvrcegui/VrCeguiControlFrame.h>
#include <bwvrcegui/VrCeguiConsole.h>

#include <bwvr/VrApplet.h>
#include <bwvr/VrUser.h>
#include <bwvr/VrWorld.h>

#include <bwvr/config/cegui.h>

CEGUI::MouseButton convertButtonToCegui(int buttonID) ;

VrCeguiGuiController::VrCeguiGuiController(VrController *pSuper, VrCeguiGui *pGui) : VrToolController(pSuper) {
	p_gui = pGui ;
}

void VrCeguiGuiController::doCreate(const BwPartInfo& info) {
	VrToolController::doCreate(info) ;
	p_guiRenderer = p_gui->getGuiRenderer() ;
}
void VrCeguiGuiController::activate() {
	VrController::activate() ;

	VrCeguiControlFrame *pCF = p_gui->getControlFrame() ;
	pCF->show() ;
	VrCeguiConsole *pConsole = p_gui->getConsole() ;
	pConsole->show() ;

	CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().show() ;
}
void VrCeguiGuiController::deactivate() {
	VrController::deactivate() ;

	VrCeguiControlFrame *pCF = p_gui->getControlFrame() ;
	pCF->hide() ;
	VrCeguiConsole *pConsole = p_gui->getConsole() ;
	pConsole->hide() ;

	CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().hide() ;
}
bool VrCeguiGuiController::processEvent(BwControllerEvent&& evt) {
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
void VrCeguiGuiController::keyPressed(BwControllerEvent& evt) {
	if(evt.getKey() == BwControllerEvent::KC_ESCAPE) {
        return;
    }
  CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyDown((CEGUI::Key::Scan)evt.getKey());
	CEGUI::System::getSingleton().getDefaultGUIContext().injectChar(evt.getKeyChar());
}

void VrCeguiGuiController::keyReleased(BwControllerEvent& evt) {
	CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyUp((CEGUI::Key::Scan)evt.getKey());
}
void VrCeguiGuiController::keyClicked(BwControllerEvent& evt) {
}
void VrCeguiGuiController::mouseMoved (BwControllerEvent& evt) {
    /*CEGUI::System::getSingleton().injectMouseMove(
            evt.getRelX() * p_guiRenderer->getWidth(), 
            evt.getRelY() * p_guiRenderer->getHeight());*/
	CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseMove(evt.getRelX(), evt.getRelY());
}
void VrCeguiGuiController::mouseDragged (BwControllerEvent& evt) { 
    mouseMoved(evt);
}
void VrCeguiGuiController::mousePressed (BwControllerEvent& evt) {
    CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonDown(
        convertButtonToCegui(evt.getButtonID()));
}

void VrCeguiGuiController::mouseReleased (BwControllerEvent& evt) {
    CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonUp(
        convertButtonToCegui(evt.getButtonID()));
}
CEGUI::MouseButton convertButtonToCegui(int buttonID) {
	switch (buttonID)
	{
	case BwControllerEvent::BUTTON0_MASK:
		return CEGUI::LeftButton;
	case BwControllerEvent::BUTTON1_MASK:
		return CEGUI::RightButton;
	case BwControllerEvent::BUTTON2_MASK:
		return CEGUI::MiddleButton;
	case BwControllerEvent::BUTTON3_MASK:
		return CEGUI::X1Button;
	default:
		return CEGUI::LeftButton;
	}
}