/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _VrCameraController_H
#define _VrCameraController_H

#include "VrToolController.h"

class VrCamera ;

class VrCameraController : public VrToolController
{
public:
	VrCameraController(VrController *pSuper) ;
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
	VrCamera *p_camera ;
};

#endif //_VrCameraController_H