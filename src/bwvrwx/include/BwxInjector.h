/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _BwxInjector_H
#define _BwxInjector_H

#include <bwcontrol/BwControllerEvent.h>
#include <bwvr/VrUser.h>
#include <BwxVrCtrl.h>

class VrUser ;
class BwxInjector : public wxEvtHandler {
public:
	BwxInjector(BwxVrCtrl *pCtrl, VrController *pUser) : p_ctrl(pCtrl), p_user(pUser) {
		//VrScene *pScene = VrScene::singleton::getPtr() ;
		//p_user = dynamic_cast<User*>(pScene->getUser()) ;
		pCtrl->PushEventHandler(this) ;
	}
	~BwxInjector() {
		p_ctrl->PopEventHandler() ;
	}
	void captureMouse() {
		m_isCapturing = true ;
		p_ctrl->CaptureMouse() ;
		//::GetClipCursor(&rcOldClip) ; 
		//::GetWindowRect(HWND(p_ctrl->GetHandle()), &rcClip);
		//::ClipCursor(&rcClip) ; 
		::ShowCursor(false);
	}
	void releaseMouse() {
		m_isCapturing = false ;
		p_ctrl->ReleaseMouse() ;
		//::ClipCursor(&rcOldClip); 
		::ShowCursor(true);
	}
	//
	BwKeyboardState m_keyboard ;

	void encodeKeyboard(wxKeyEvent& e) {
		m_keyboard.code = BwControllerEvent::getCharKey(e.GetRawKeyCode()) ;
		m_keyboard.modifiers = 0 ;
		if(e.ShiftDown())
			m_keyboard.modifiers |= BwControllerEvent::SHIFT_MASK ;
		if(e.ControlDown())
			m_keyboard.modifiers |= BwControllerEvent::CTRL_MASK ;
		if(e.MetaDown())
			m_keyboard.modifiers |= BwControllerEvent::META_MASK ;
		if(e.AltDown())
			m_keyboard.modifiers |= BwControllerEvent::ALT_MASK ;
	}
	//
	BwMouseState m_mouse ;

	void encodeMouse(wxMouseEvent& e) {
		int modifiers = 0 ;
		int buttons = 0 ;
		int mouseX = e.GetX() ;
		int mouseY = e.GetY() ;
		int windowWidth = p_ctrl->getRenderWindowWidth() ; //f6:fixme:need to cache these values
		int windowHeight = p_ctrl->getRenderWindowHeight() ;
		//need to do a mouse warp during capture
		int warpBorder = 10 ;
		bool m_needsWarp = false ;
		if(m_isCapturing == true) {
			if(mouseX < warpBorder) {
				mouseX = windowWidth - warpBorder ;
				m_needsWarp = true ;
			}
			else
			if(mouseX > windowWidth - warpBorder) {
				mouseX = warpBorder ;
				m_needsWarp = true ;
			}
			if(mouseY < warpBorder) {
				mouseY = windowHeight - warpBorder ;
				m_needsWarp = true ;
			}
			else
			if(mouseY > windowHeight - warpBorder) {
				mouseY = warpBorder ;
				m_needsWarp = true ;
			}
			if(m_needsWarp) {
				p_ctrl->WarpPointer(mouseX, mouseY) ;
				//m_mouse.absX = ( float(mouseX) / windowWidth ) ;
				m_mouse.absX = mouseX ;
				//m_mouse.absY = ( float(mouseY - windowHeight ) / windowHeight ) ;
				m_mouse.absY = mouseY - windowHeight ;
			}
		}
		//new center equals old position
		m_mouse.centerX = m_mouse.absX ;
	    m_mouse.centerY = m_mouse.absY ;
		//calculate absolute in float 0 .. 1 terms
		//m_mouse.absX = ( float(mouseX) / windowWidth ) ;
		m_mouse.absX = mouseX ;
		m_mouse.absY = mouseY - windowHeight ;
		//calculate relative
		m_mouse.relX = m_mouse.absX - m_mouse.centerX ;
		m_mouse.relY = m_mouse.absY - m_mouse.centerY ;
		//
		/*******Buttons***************/
		m_mouse.buttons = 0 ;
		int button = e.GetButton() ;
		switch( button )
		{
			case wxMOUSE_BTN_LEFT :
				m_mouse.buttons = BwControllerEvent::BUTTON0_MASK ;
				break;
			case wxMOUSE_BTN_RIGHT :
				m_mouse.buttons = BwControllerEvent::BUTTON1_MASK;
				break;
			case wxMOUSE_BTN_MIDDLE :
				m_mouse.buttons = BwControllerEvent::BUTTON2_MASK;
				break;
		}
		/*******Modifiers***************/
		m_mouse.modifiers = 0 ;
		if(e.ShiftDown())
			m_mouse.modifiers |= BwControllerEvent::SHIFT_MASK ;
		if(e.ControlDown())
			m_mouse.modifiers |= BwControllerEvent::CTRL_MASK ;
		if(e.MetaDown())
			m_mouse.modifiers |= BwControllerEvent::META_MASK ;
		if(e.AltDown())
			m_mouse.modifiers |= BwControllerEvent::ALT_MASK ;
	}
	//////////
	void mouseMoved (wxMouseEvent& e) {
		encodeMouse(e) ;
		p_user->processEvent(
			BwMouseMovedEvent(m_mouse.modifiers, 
				m_mouse.buttons, m_mouse.getX(), m_mouse.getY(), m_mouse.getRelX(), m_mouse.getRelY())) ;
	}
	void mouseDragged (wxMouseEvent& e) {
		//p_user->processEvent(BwMouseDraggedEvent(e->getModifiers(), e->getButtonID(), e->getX(), e->getY(), e->getRelX(), e->getRelY())) ;
	}
	void mousePressed (wxMouseEvent& e) {
		encodeMouse(e) ;
		p_user->processEvent(
			BwMousePressedEvent(m_mouse.modifiers,
				m_mouse.buttons, m_mouse.getX(), m_mouse.getY(), m_mouse.getRelX(), m_mouse.getRelY())) ;
	}
	void mouseReleased (wxMouseEvent& e) {
		//p_user->processEvent(BwMouseReleasedEvent(e->getModifiers(), e->getButtonID(), e->getX(), e->getY(), e->getRelX(), e->getRelY())) ;
	}
	void mouseClicked(wxMouseEvent& e) {}
	void mouseEntered(wxMouseEvent& e) {}
	void mouseExited(wxMouseEvent& e) {}

	void keyPressed(wxKeyEvent& e) {
		encodeKeyboard(e) ;
		p_user->processEvent(BwKeyboardPressedEvent(m_keyboard.modifiers, m_keyboard.code)) ;
	}
	void keyReleased(wxKeyEvent& e) {
		encodeKeyboard(e) ;
		p_user->processEvent(BwKeyboardReleasedEvent(m_keyboard.modifiers, m_keyboard.code)) ;
	}
	void keyClicked(wxKeyEvent& e) {
		/*keyPressed(e) ;
		keyReleased(e) ;*/
	}
	//Data Members
	VrController *p_user ;
	BwxVrCtrl *p_ctrl ;
	//
	bool m_isCapturing ;
	//RECT rcClip;           // new area for ClipCursor
	//RECT rcOldClip;        // previous area for ClipCursor
	DECLARE_EVENT_TABLE()
} ;
/*
RECT rcClip;           // new area for ClipCursor
RECT rcOldClip;        // previous area for ClipCursor
 
// Record the area in which the cursor can move. 
 
GetClipCursor(&rcOldClip); 
 
// Get the dimensions of the application's window. 
 
GetWindowRect(hwnd, &rcClip); 
 
// Confine the cursor to the application's window. 
 
ClipCursor(&rcClip); 
 
   // 
   // Process input from the confined cursor. 
   // 
 
// Restore the cursor to its previous area. 
 
ClipCursor(&rcOldClip); 
*/

#endif //_BwxInjector_H