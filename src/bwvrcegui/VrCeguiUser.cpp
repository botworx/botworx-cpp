/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <bwvrcegui/VrCeguiUser.h>
#include <bwvrcegui/VrCeguiGui.h>
#include <bwvrcegui/VrCeguiControlFrame.h>
#include <bwvrcegui/VrCeguiControlFrame.h>
#include <bwvrcegui/VrCeguiControlPanel.h>
#include <bwvrcegui/VrCeguiGuiController.h>

#include <bwvr/VrScene.h>
//
#include <bwvr/config/ogre.h>
//
#include <OIS/OIS.h>
//
#include <boost/filesystem/operations.hpp>
using namespace boost::filesystem;

namespace _VrCeguiUser {
	class OisInjector : public BwInjector, public OIS::MouseListener, public OIS::KeyListener {
	public:
		OisInjector(VrCeguiUser *pUser) : p_user(pUser) {
			using namespace OIS;
			ParamList pl;
			size_t windowHnd = 0;
			std::ostringstream windowHndStr;

			//
			Ogre::RenderWindow* win = p_user->getScene()->getRenderWindow() ;
			//
			win->getCustomAttribute("WINDOW", &windowHnd);
			windowHndStr << windowHnd;
			pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));

			m_inputManager = InputManager::createInputSystem( pl );

			//Create all devices (We only catch joystick exceptions here, as, most people have Key/Mouse)
			//m_keyboard = static_cast<Keyboard*>(mInputManager->createInputObject( OISKeyboard, bufferedKeys ));
			m_keyboard = static_cast<Keyboard*>(m_inputManager->createInputObject( OISKeyboard, true ));
			//m_mouse = static_cast<Mouse*>(mInputManager->createInputObject( OISMouse, bufferedMouse ));
			m_mouse = static_cast<Mouse*>(m_inputManager->createInputObject( OISMouse, true ));
			//
			m_mouse->setEventCallback(this);
			m_keyboard->setEventCallback(this);
		}
		//
		virtual void capture() {
			m_keyboard->capture();
			m_mouse->capture();
		}
		//////////
		virtual bool keyPressed( const OIS::KeyEvent &arg ) {
			encodeKeyboard(arg) ;
			//p_user->processEvent(BwKeyboardPressedEvent(0, arg.key)) ;
			p_user->processEvent(BwKeyboardPressedEvent(m_keyboardState.modifiers, m_keyboardState.code)) ;
			return true;
		}
		virtual bool keyReleased( const OIS::KeyEvent &arg ) {
			//p_user->processEvent(BwKeyboardReleasedEvent(0, arg.key)) ;
			encodeKeyboard(arg) ;
			p_user->processEvent(BwKeyboardReleasedEvent(m_keyboardState.modifiers, m_keyboardState.code)) ;
			return true;
		}
		virtual bool mouseMoved (const OIS::MouseEvent& arg) {
			//p_user->processEvent(BwMouseMovedEvent(e->getModifiers(), e->getButtonID(), e->getX(), e->getY(), e->getRelX(), e->getRelY())) ;
			encodeMouse(arg) ;
			//p_user->processEvent(BwMouseMovedEvent(0, 0, arg.state.X.abs, arg.state.Y.abs, arg.state.X.rel, arg.state.Y.rel)) ;
			p_user->processEvent(BwMouseMovedEvent(m_mouseState.modifiers, m_mouseState.buttons, arg.state.X.abs, arg.state.Y.abs, arg.state.X.rel, arg.state.Y.rel)) ;
			return true;
		}
		virtual bool mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id ) {
			//p_user->processEvent(BwMousePressedEvent(0, id, arg.state.X.abs, arg.state.Y.abs, arg.state.X.rel, arg.state.Y.rel)) ;
			encodeMouse(arg) ;
			p_user->processEvent(BwMousePressedEvent(m_mouseState.modifiers, m_mouseState.buttons, arg.state.X.abs, arg.state.Y.abs, arg.state.X.rel, arg.state.Y.rel)) ;

			return true;
		}
		virtual bool mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id ) {
			//p_user->processEvent(BwMouseReleasedEvent(0, id, arg.state.X.abs, arg.state.Y.abs, arg.state.X.rel, arg.state.Y.rel)) ;
			encodeMouse(arg) ;
			p_user->processEvent(BwMouseReleasedEvent(m_mouseState.modifiers, m_mouseState.buttons, arg.state.X.abs, arg.state.Y.abs, arg.state.X.rel, arg.state.Y.rel)) ;
			return true;
		}
		//
		void encodeKeyboard(const OIS::KeyEvent &arg) {
			m_keyboardState.modifiers = getModifiers() ;
			m_keyboardState.code = arg.key ;
		}
		void encodeMouse(const OIS::MouseEvent &arg) {
			m_mouseState.modifiers = getModifiers() ;
			//m_mouseState.buttons = arg.state.buttons ;
			/*******Buttons***************/
			m_mouseState.buttons = getButtons(arg) ;
		}
		int getButtons(const OIS::MouseEvent &arg) {
			int buttons = 0 ;
			if(arg.state.buttonDown(OIS::MB_Left))
				buttons |= BwControllerEvent::BUTTON0_MASK ;
			if(arg.state.buttonDown(OIS::MB_Right))
				buttons |= BwControllerEvent::BUTTON1_MASK ;
			if(arg.state.buttonDown(OIS::MB_Middle))
				buttons |= BwControllerEvent::BUTTON2_MASK ;
			return buttons ;
		}
		int getModifiers() {
			int modifiers = 0 ;
			if(m_keyboard->isModifierDown(OIS::Keyboard::Shift))
				modifiers |= BwControllerEvent::SHIFT_MASK ;
			if(m_keyboard->isModifierDown(OIS::Keyboard::Ctrl))
				modifiers |= BwControllerEvent::CTRL_MASK ;
			/*if(e.MetaDown())
				m_keyboardState.modifiers |= BwControllerEvent::META_MASK ;*/
			if(m_keyboard->isModifierDown(OIS::Keyboard::Alt))
				modifiers |= BwControllerEvent::ALT_MASK ;
			//
			return modifiers ;
		}
		//Data Members
		VrCeguiUser *p_user ;
		//
		BwKeyboardState m_keyboardState ;
		BwMouseState m_mouseState ;
		//
		OIS::Mouse *m_mouse;
		OIS::Keyboard *m_keyboard;
		OIS::InputManager *m_inputManager;
	} ;
} ;

using namespace _VrCeguiUser ;

VrCeguiUser::VrCeguiUser(VrScene *pScene) : VrUser(pScene) {
	p_gui = NULL ;
	p_injector = NULL ;
	p_guiController = NULL ;
}
void VrCeguiUser::createInjector() {
	p_injector = new OisInjector(this) ;
}
void VrCeguiUser::doPostDisable(bool sleeping) {
	if(!sleeping) {//ugh ... weird concept.
		delete p_gui ;
	}
	VrUser::doPostDisable(sleeping) ;
}
//
void VrCeguiUser::doStep(BwStepper& stepper) {
	VrUser::doStep(stepper) ;
	p_injector->capture() ;
}
//
void VrCeguiUser::pushMode(VrCeguiUserMode* pMode) {
	m_modeStack.push(pMode) ;
	onPushMode(pMode) ;
}
void VrCeguiUser::onPushMode(VrCeguiUserMode* pMode) {
	p_gui->getControlFrame()->setControlPanel(pMode) ;
}
VrCeguiUserMode* VrCeguiUser::popMode() {
	VrCeguiUserMode *pOldMode = m_modeStack.top() ;
	pOldMode->deactivate() ;
	m_modeStack.pop() ;
	if(m_modeStack.empty())
		return NULL ;
	VrCeguiUserMode *pMode = m_modeStack.top() ;
	onPopMode(pMode) ;
	return pMode ;
}
void VrCeguiUser::onPopMode(VrCeguiUserMode* pMode) {
	p_gui->getControlFrame()->setControlPanel(pMode) ;
}
//
void VrCeguiUser::bind() {
	VrUser::bind() ;
	p_guiController->bind() ;
}
void VrCeguiUser::unbind() {
	VrUser::unbind() ;
	p_guiController->unbind() ;
	delete p_gui ;
}
