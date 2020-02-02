/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _VrCeguiUser_H
#define _VrCeguiUser_H

#include <bwvr/VrUser.h>

#include "VrCeguiUserMode.h"
class VrCeguiGui ;
class VrCeguiGuiController ;

class VrCeguiUser : public VrUser {
public:
	VrCeguiUser(VrScene *pScene) ;
	virtual void createInjector() ;
	virtual void doStep(BwStepper& stepper) ;
	virtual void doPostDisable(bool sleeping = true) ;
	//
	virtual void bind() ;
	virtual void unbind() ;
	//
	void pushMode(VrCeguiUserMode* pMode) ;
	virtual void onPushMode(VrCeguiUserMode* pMode) ;
	VrCeguiUserMode* popMode() ;
	virtual void onPopMode(VrCeguiUserMode* pMode) ;
	VrCeguiUserMode* getMode() { return m_modeStack.top() ; }
	//newstuff
	void addMode(VrCeguiUserMode *pMode) { m_modes[pMode->getName()] = pMode ; }
	VrCeguiUserMode* findMode(const bwString& name) { return m_modes[name] ; }
	//
	VrCeguiGui* getGui() { return p_gui ; }
	VrCeguiGuiController* getGuiController() { return p_guiController ; }
	//
	VrCeguiGui *p_gui ;
	VrCeguiGuiController *p_guiController ;
	BwInjector *p_injector ;
	//
	std::map<bwString, VrCeguiUserMode*> m_modes ;
	std::stack<VrCeguiUserMode*> m_modeStack ;
};

#endif //_VrUser_H