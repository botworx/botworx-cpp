/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _VrHandController_H
#define _VrHandController_H

#include "VrToolController.h"

class VrHand ;
class VrWorld ;

class VrHandController : public VrToolController
{
public:
	VrHandController(VrController *pSuper) ;
	virtual void bind() ;
	virtual void unbind() ;
	virtual bool processEvent(BwControllerEvent&& evt) ;
	//
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
	/*Data Members*/
	VrHand *p_hand ;
	bool m_verticalMode ;
};

#endif //_VrHandController_H