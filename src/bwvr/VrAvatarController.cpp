/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <bwvr/VrAvatarController.h>
#include <bwvr/VrModel.h>
#include <bwvr/VrScenario.h>

#include <bwvr/VrBrain.h>
#include <bwvr/_VrBrain.h>

VrAvatarController::VrAvatarController(VrController *pSuper) : VrToolController(pSuper) {
	m_emitJump = false ;
	m_emitForward = false ;
	m_emitReverse  = false ;
	m_emitLeft = false ;
	m_emitRight = false ;
	m_emitPitchUp = false ;
	m_emitPitchDown = false ;
	m_emitRollLeft = false ;
	m_emitRollRight = false ;
}
void VrAvatarController::bind() {
	VrToolController::bind() ;
	p_tool = VrScenario::singleton::get().getAvatar() ;
	p_brain = static_cast<VrBrain*>(p_tool->getBrain()) ;
}
void VrAvatarController::unbind() {
	VrToolController::unbind() ;
	p_tool = NULL ;
	p_brain = NULL ;
}
void VrAvatarController::activate() {
	VrController::activate() ;
}
void VrAvatarController::deactivate() {
	VrController::deactivate() ;
}
void VrAvatarController::doStep(BwStepper& stepper) {
	if(m_emitJump)
		p_brain->processMessage(BwMessage(_VrBrain::COMMAND_JUMP)) ;
	else
		p_brain->jumpNone() ;
	//
	if(m_emitForward)
		p_brain->processMessage(BwMessage(_VrBrain::COMMAND_FORWARD)) ;
	else
	if(m_emitReverse)
		p_brain->processMessage(BwMessage(_VrBrain::COMMAND_REVERSE)) ;
	else
		p_brain->moveNone() ;
	//
	if(m_emitLeft)
		p_brain->processMessage(BwMessage(_VrBrain::COMMAND_LEFT)) ;
	else
	if(m_emitRight)
		p_brain->processMessage(BwMessage(_VrBrain::COMMAND_RIGHT)) ;
	else
		p_brain->turnNone() ;
	//
	if(m_emitRollLeft)
		p_brain->processMessage(BwMessage(_VrBrain::COMMAND_ROLL_LEFT)) ;
	else
	if(m_emitRollRight)
		p_brain->processMessage(BwMessage(_VrBrain::COMMAND_ROLL_RIGHT)) ;
	//
	if(m_emitPitchUp)
		p_brain->processMessage(BwMessage(_VrBrain::COMMAND_PITCH_UP)) ;
	else
	if(m_emitPitchDown)
		p_brain->processMessage(BwMessage(_VrBrain::COMMAND_PITCH_DOWN)) ;
}
bool VrAvatarController::processEvent(BwControllerEvent&& evt) {
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
void VrAvatarController::keyPressed(BwControllerEvent& evt) {
	switch(evt.getKey()) {
		case BwControllerEvent::KC_B :
			bwAssert(0) ;
			break ;
		case BwControllerEvent::KC_SPACE :
			p_brain->processMessage(BwMessage(_VrBrain::COMMAND_FIRE_MISSILE)) ;
			break ;
		case BwControllerEvent::KC_F :
			p_brain->processMessage(BwMessage(_VrBrain::COMMAND_FIRE_LASER)) ;
			break ;
		case BwControllerEvent::KC_V :
			m_emitJump = true ;
			break ;
		case BwControllerEvent::KC_W :
			if(evt.isControlDown())
				m_emitPitchDown = true ;
			else
				m_emitForward = true ;
			break ;
		case BwControllerEvent::KC_S :
			if(evt.isControlDown())
				m_emitPitchUp = true ;
			else
				m_emitReverse = true ;
			break ;
		case BwControllerEvent::KC_A :
			if(evt.isControlDown())
				m_emitRollLeft = true ;
			else
				m_emitLeft = true ;
			break ;
		case BwControllerEvent::KC_D :
			if(evt.isControlDown())
				m_emitRollRight = true ;
			else
				m_emitRight = true ;
			break ;
		case BwControllerEvent::KC_0 :
			p_brain->pose(0) ;
			break ;
		case BwControllerEvent::KC_2 :
			p_brain->pose(2) ;
			break ;
		case BwControllerEvent::KC_4 :
			p_brain->pose(4) ;
			break ;
		case BwControllerEvent::KC_6 :
			p_brain->pose(6) ;
			break ;
		case BwControllerEvent::KC_8 :
			p_brain->pose(8) ;
			break ;
		case BwControllerEvent::KC_9 :
			p_brain->pose(9) ;
			break ;
	}
}
void VrAvatarController::keyReleased(BwControllerEvent& evt) {
	switch(evt.getKey()) {
		case BwControllerEvent::KC_V :
			m_emitJump = false ;
			break ;
		case BwControllerEvent::KC_W :
			if(evt.isControlDown())
				m_emitPitchDown = false ;
			else
				m_emitForward = false ;
			break ;
		case BwControllerEvent::KC_S :
			if(evt.isControlDown())
				m_emitPitchUp = false ;
			else
				m_emitReverse = false ;
			break ;
		case BwControllerEvent::KC_A :
			if(evt.isControlDown())
				m_emitRollLeft = false ;
			else
				m_emitLeft = false ;
			break ;
		case BwControllerEvent::KC_D :
			if(evt.isControlDown())
				m_emitRollRight = false ;
			else
				m_emitRight = false ;
			break ;
	}
}
void VrAvatarController::keyClicked(BwControllerEvent& evt) {
}
void VrAvatarController::mouseMoved (BwControllerEvent& evt) {
}
void VrAvatarController::mouseDragged (BwControllerEvent& evt) {
}
void VrAvatarController::mousePressed (BwControllerEvent& evt) {
}
void VrAvatarController::mouseReleased (BwControllerEvent& evt) {
}
