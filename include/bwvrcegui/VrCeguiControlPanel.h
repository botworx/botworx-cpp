/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _VrCeguiControlPanel_H
#define _VrCeguiControlPanel_H

#include "VrCeguiWindow.h"

class VrCeguiUserMode ;

class VrCeguiControlPanel : public VrCeguiWindow {
public:
	VrCeguiControlPanel(VrCeguiGui *pGui) ;
	virtual void createPeer() ;
	void createButton(VrCeguiUserMode *pMode) ;
	bool handleButtonPress(const CEGUI::EventArgs& e) ;
	/*Data Members*/
	CEGUI::ScrollablePane *p_pane ;
	int m_buttonTtl ;
	std::map<CEGUI::ButtonBase*, VrCeguiUserMode*> m_buttonMap ;
};

#endif //_VrCeguiControlPanel_H