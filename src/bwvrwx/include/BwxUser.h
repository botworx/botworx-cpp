/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _BwxUser_H
#define _BwxUser_H

#include <bwvr/VrUser.h>

#include <bwscheduling/BwTimer.h>
#include "BwxUserMode.h"

class BwxVrCtrl ;
class BwxGui ;
class BwxInjector ;

class VrApplet ;
class VrUniverse ;
class VrWorld ;
class VrScene ;
class BwBrain ;
class VrCamera ;
class VrHand ;
class VrToolController ;
class VrAvatarController ;
class VrCameraController ;
class VrHandController ;
class VrCeguiGuiController ;

class wxFrame ;

class BwxUser : public VrUser {
public:
	BwxUser(VrScene *pScene, wxFrame *pFrame, BwxVrCtrl* pCtrl) ;
//
	virtual void createGui() ;
	virtual bool processEvent(BwControllerEvent& evt) ; //f6:move to VrUser
	//
	virtual void bind() ;
	virtual void unbind() ;
	//
	BwxGui* getGui() { return p_gui ; }
	//
	void pushMode(BwxUserMode* pMode) ;
	virtual void onPushMode(BwxUserMode* pMode) ;
	BwxUserMode* popMode() ;
	virtual void onPopMode(BwxUserMode* pMode) ;
	BwxUserMode* getMode() { return m_modeStack.top() ; }
	//newstuff
	void addMode(BwxUserMode *pMode) { m_modes[pMode->getName()] = pMode ; }
	BwxUserMode* findMode(bwString name) { return m_modes[name] ; }
	/*Data Members*/
	std::map<bwString, BwxUserMode*> m_modes ;
	std::stack<BwxUserMode*> m_modeStack ;
	//
	virtual void createInjector() ;
	void setInjector(BwxInjector* pInjector) { p_injector = pInjector ; }
	BwxInjector* getInjector() { return p_injector ; }
	BwxInjector *p_injector ;

	wxFrame *p_frame ;
	BwxVrCtrl* p_ctrl ;
	BwxGui *p_gui ;
	bool m_useTool ; //f6:fixme:put in VrUser?
};

#endif //_BwxUser_H