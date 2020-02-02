/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _VrCeguiControlFrame_H
#define _VrCeguiControlFrame_H

#include "VrCeguiWindow.h"

class VrCeguiUserMode ;
class VrCeguiControlPanel ;

class VrCeguiControlFrame : public VrCeguiWindow {
public:
    VrCeguiControlFrame(VrCeguiGui *pGui) ;
    virtual ~VrCeguiControlFrame() {
    }
	void setControlPanel(VrCeguiUserMode *pMode) ;
	bool handleScrollChange(const CEGUI::EventArgs& e) ;
public:
	/*Data Members*/
	VrCeguiControlPanel *p_controlPanel ;
};
#endif //_VrCeguiControlFrame_H
