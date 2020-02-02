/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <bwcontrol/BwControllerEvent.h>

#include "BwxUser.h"
#include "BwxGui.h"
#include "BwxInjector.h"
#include "BwxDeckFrame.h"

#include <bwvr/VrApplet.h>
#include <bwvr/VrScene.h>
#include <bwvr/VrScenario.h>
#include <bwvr/VrAvatarController.h>
#include <bwvr/VrCameraController.h>
#include <bwvr/VrHandController.h>
#include <bwvr/VrCamera.h>
#include <bwvr/VrHand.h>

#include <bwvr/config/ogre.h>

BwxUser::BwxUser(VrScene *pScene, wxFrame *pFrame, BwxVrCtrl* pCtrl) : VrUser(pScene) {
	p_frame = pFrame ;
	p_ctrl = pCtrl ;
	m_useTool = false ; //f6:fixme:put in VrUser?
}
void BwxUser::createGui() { 
	p_gui = new BwxGui(this) ;
	p_gui->setSheet(p_frame) ;
	p_gui->create() ;
}
	//BwxInjector *pInjector = new BwxInjector(p_vrCtrl, p_user) ;
	//p_user->setInjector(pInjector) ;
void BwxUser::createInjector() {
	p_injector = new BwxInjector(p_ctrl, this) ;
}
void BwxUser::bind() {
	VrUser::bind() ;
}
void BwxUser::unbind() {
	VrUser::unbind() ;
	p_gui->unbind() ;
	delete p_gui ;
}
//f6:fixme:put in VrUser: why is CEGUI working?!!
bool BwxUser::processEvent(BwControllerEvent& evt) {
	p_avatarController->processEvent(evt) ;
	//
	if(m_useTool)
		p_toolController->processEvent(evt) ;
	return true ;
}
//
void BwxUser::pushMode(BwxUserMode* pMode) {
	m_modeStack.push(pMode) ;
	onPushMode(pMode) ;
}
void BwxUser::onPushMode(BwxUserMode* pMode) {
	p_gui->getControlFrame()->setControlPanel(pMode) ;
}
BwxUserMode* BwxUser::popMode() {
	m_modeStack.pop() ;
	if(m_modeStack.empty())
		return NULL ;
	BwxUserMode *pMode = m_modeStack.top() ;
	onPopMode(pMode) ;
	return pMode ;
}
void BwxUser::onPopMode(BwxUserMode* pMode) {
	p_gui->getControlFrame()->setControlPanel(pMode) ;
}