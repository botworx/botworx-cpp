/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _VrUser_H
#define _VrUser_H

#include "VrToolController.h"
#include <bwscheduling/BwTimer.h>

class VrApplet ;
class VrScenario ;
class BwBrain ;
class VrCamera ;
class VrHand ;
class VrAvatarController ;
class VrCameraController ;
class VrHandController ;
class VrScenario ;

class VrUser : public VrController {
public:
	VrUser(VrScene *pScene) ;
	virtual void doCreate(const BwPartInfo& info) ;
	virtual void createGui() {}
	virtual void createInjector() = 0 ;
	virtual void doStep(BwStepper& stepper) ;
	virtual void doPostStep(BwStepper& stepper) ;
	virtual bool onPostStep(BwStepper& stepper) ;
	bool getShutdownRequested() { return m_shutdownRequested ; }
    void requestShutdown(void) { m_shutdownRequested = true ; }
	virtual bool processEvent(BwControllerEvent&& evt) ;
	//
	VrScene* getScene() { return p_scene ; }
	VrModel* getTool() { return p_toolController->getTool() ; }
	VrModel* getAvatar() { return p_avatar ; }
	void switchAvatar(VrModel *pAvatar) ;
	VrModel* getSelection() { return NULL ; } //TODO:reimplement
	VrHand* getHand() { return p_hand ; }
	VrCamera* getCamera() { return p_camera ; }
	void setToolController(VrToolController *pToolCtrlr) {
		p_prevToolController = p_toolController ;
		if(p_toolController != NULL)
			p_toolController->deactivate() ; 
		p_toolController = pToolCtrlr ; 
		p_toolController->activate() ;
	}
	VrToolController* getPrevToolController() { return p_prevToolController ; }
	//newstuff
	void loadScenario(const bwString& name) ;
	virtual void bind() ;
	virtual void unbind() ;
	//
    bool m_shutdownRequested;
	
	VrAvatarController *p_avatarController ;
	VrToolController *p_toolController ;
	VrToolController *p_prevToolController ;
	BwLoTimer m_inputTimer ;

	VrCameraController *p_camCtrlr ;
	VrHandController *p_handCtrlr ;
	VrScene* p_scene ;
	VrModel *p_avatar ;
	VrCamera *p_camera ;
	VrHand *p_hand ;
	BwBrain *p_brain ;
};

#endif //_VrUser_H