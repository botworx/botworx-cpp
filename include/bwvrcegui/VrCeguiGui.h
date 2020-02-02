/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _VrCeguiGui_H
#define _VrCeguiGui_H

#include <bwcore/BwPart.h>

namespace CEGUI {
	class OgreRenderer ;
	class System ;
	class Window ;
	class Scrollbar ;
	class ScrollablePane ;
	class EventArgs ;
	class ButtonBase ;
	class Renderer ;
}
class VrScene ;
class VrCeguiWindow ;
class VrCeguiControlFrame ;
class VrCeguiConsole ;
//
//VrCeguiGui
//
class VrCeguiGui : public BwPart {
public:
    VrCeguiGui(VrScene *pScene) ;
    virtual ~VrCeguiGui() ;
    virtual void doCreate(const BwPartInfo& info) ;
	//
	CEGUI::OgreRenderer* getGuiRenderer() { return p_guiRenderer ; }
	void setSheet(VrCeguiWindow* pWindow) ;
	VrCeguiWindow* getSheet() { return p_sheet ; }
	VrCeguiControlFrame* getControlFrame() { return p_controlFrame ; }
	VrCeguiConsole* getConsole() { return p_console ; }
	//////////////////
	/*Data Members*/
	VrScene *p_scene ;
protected:
    CEGUI::OgreRenderer* p_guiRenderer;
    CEGUI::System* p_guiSystem;
	//
	VrCeguiWindow* p_sheet ;
	VrCeguiControlFrame *p_controlFrame ;
	VrCeguiConsole *p_console ;
};

#endif //_VrCeguiGui_H