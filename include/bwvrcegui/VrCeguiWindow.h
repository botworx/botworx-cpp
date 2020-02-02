/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _VrCeguiWindow_H
#define _VrCeguiWindow_H

#include "VrCeguiGui.h"

class VrCeguiWindow : public BwPart {
public:
	VrCeguiWindow(VrCeguiGui *pGui) ;
	virtual void doCreate(const BwPartInfo& info) ;
	virtual void createPeer() ;
	CEGUI::Window* getPeer() { return p_peer ; }
	void setName(const bwString& name) { m_name = name ; }
	bwString getName() { return m_name ; }
	void show() ;
	void hide() ;
	bool isVisible() ;
	void setIsManuallyCreated(bool val) { m_isManuallyCreated = val ; }
	void createDefaultWindow() ;
	/*Data Members*/
	bool m_isManuallyCreated ;
	bwString m_name ;
	VrCeguiGui *p_gui ;
	CEGUI::Window* p_peer ;
	bwString m_layoutFileName ;
};

#endif //_VrCeguiWindow_H