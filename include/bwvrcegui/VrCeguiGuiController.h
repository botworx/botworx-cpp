/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _VrCeguiGuiController_H
#define _VrCeguiGuiController_H

#include "VrCeguiGui.h"

#include <bwvr/VrScene.h>
#include <bwvr/VrToolController.h>

//TODO:improveme:
class VrCeguiGuiController : public VrToolController
{
public:
	virtual void activate() ;
	virtual void deactivate() ;
	virtual bool processEvent(BwControllerEvent&& evt) ;
private:
	VrCeguiGui *p_gui ;
    CEGUI::Renderer* p_guiRenderer;
public:
	VrCeguiGuiController(VrController *pSuper, VrCeguiGui *pGui) ;
	virtual void doCreate(const BwPartInfo& info) ;

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
};
#endif //_VrCeguiGuiController_H