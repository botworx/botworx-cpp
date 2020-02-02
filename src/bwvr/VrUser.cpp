/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <bwcontrol/BwControllerEvent.h>

#include <bwvr/VrUser.h>
#include <bwvr/VrApplet.h>
#include <bwvr/VrScene.h>
#include <bwvr/VrScenario.h>
#include <bwvr/VrScenarioManager.h>

#include <bwvr/VrAvatarController.h>
#include <bwvr/VrCameraController.h>
#include <bwvr/VrHandController.h>
#include <bwvr/VrCamera.h>
#include <bwvr/VrHand.h>

VrUser::VrUser(VrScene *pScene) : VrController(NULL) {
	p_scene = pScene ;
	m_shutdownRequested = false ;
	p_toolController = NULL ;
	m_inputTimer.setAlarm(std::chrono::milliseconds(100)) ;
	p_avatar = NULL ;
	p_brain = NULL ;
	p_camera = NULL ;
	p_hand = NULL ;
}
void VrUser::doCreate(const BwPartInfo& info) {
	VrController::doCreate(info) ;

	createGui() ;

	p_avatarController = new VrAvatarController(this) ;
	p_avatarController->create() ;

	p_camCtrlr = new VrCameraController(this) ;
	p_camCtrlr->create() ;

	p_handCtrlr = new VrHandController(this) ;
	p_handCtrlr->create() ;

	setToolController(p_handCtrlr) ;

	createInjector() ;
}
void VrUser::bind() {
	VrController::bind() ;
	p_avatar = VrScenario::singleton::get().getAvatar() ;
	bwAssert(p_avatar) ;
	p_brain = p_avatar->getBrain() ;
	bwAssert( p_brain ) ;
	p_avatarController->bind() ;
	p_camCtrlr->bind() ;
	p_camera = static_cast<VrCamera*>(p_camCtrlr->getTool()) ;
	p_handCtrlr->bind() ;
	p_hand = static_cast<VrHand*>(p_handCtrlr->getTool()) ;
}
void VrUser::unbind() {
	VrController::unbind() ;
	p_avatar = NULL ;
	p_brain = NULL ;
	p_avatarController->unbind() ;
	p_camCtrlr->unbind() ;
	p_camera = NULL ;
	p_handCtrlr->unbind() ;
	p_hand = NULL ;
}
void VrUser::switchAvatar(VrModel *pAvatar) {
	scenario().switchAvatar(pAvatar) ;
	p_avatarController->bind() ;
}
void VrUser::doStep(BwStepper& stepper) {
	BwActor::doStep(stepper) ;
	if(isBound()) {
		p_avatarController->invokeStep(stepper) ;
		p_toolController->invokeStep(stepper) ;
	}
}
void VrUser::doPostStep(BwStepper& stepper) {
	BwActor::doPostStep(stepper) ;
	if(isBound()) {
		p_avatarController->invokePostStep(stepper) ;
		p_toolController->invokePostStep(stepper) ;
	}
}
bool VrUser::onPostStep(BwStepper& stepper) {
	bool success = !getShutdownRequested() ;
	return success & BwActor::onPostStep(stepper) ;
}
bool VrUser::processEvent(BwControllerEvent&& evt) {
	return true ;
}
void VrUser::loadScenario(const bwString& name) {
	VrApplet::singleton::get().loadScenario(VrScenarioManager::singleton::get().findFactory(name)) ;
}
