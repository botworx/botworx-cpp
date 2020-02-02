/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _VrAvatarController_H
#define _VrAvatarController_H

#include "VrToolController.h"

class VrBrain ;

class VrAvatarController : 	public VrToolController {
public:
	virtual void doStep(BwStepper& stepper) ;
	virtual void activate() ;
	virtual void deactivate() ;
	virtual void bind() ;
	virtual void unbind() ;
	virtual bool processEvent(BwControllerEvent&& evt) ;
private:
public:
	VrAvatarController(VrController *pSuper) ;

	void mouseMoved (BwControllerEvent& evt) ;
	void mouseDragged (BwControllerEvent& evt) ;
    void mousePressed (BwControllerEvent& evt) ;
    void mouseReleased (BwControllerEvent& evt) ;
	void mouseClicked(BwControllerEvent& evt) {}
	void mouseEntered(BwControllerEvent& evt) {}
	void mouseExited(BwControllerEvent& evt) {}

    void keyPressed(BwControllerEvent& evt) ;
	void keyReleased(BwControllerEvent& evt) ;
	void keyClicked(BwControllerEvent& evt) ;
	//Data Members
	//BwBrain *p_brain ;
	VrBrain *p_brain ;
	//
	bool m_emitJump ;
	bool m_emitForward ;
	bool m_emitReverse ;
	bool m_emitLeft ;
	bool m_emitRight ;
	bool m_emitPitchUp ;
	bool m_emitPitchDown ;
	bool m_emitRollLeft ;
	bool m_emitRollRight ;
};
#endif //_VrAvatarController_H
