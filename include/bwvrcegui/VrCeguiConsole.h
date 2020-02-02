/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _VrCeguiConsole_H
#define _VrCeguiConsole_H

#include "VrCeguiWindow.h"
#include <CEGUI/widgets/FrameWindow.h>
#include <CEGUI/widgets/MultiLineEditbox.h>

class VrCeguiUserMode ;
class VrCeguiControlPanel ;
//
//VrCeguiConsole
//
class VrCeguiConsole : public VrCeguiWindow {
public:
    VrCeguiConsole(VrCeguiGui *pGui) ;
    virtual ~VrCeguiConsole() {
    }
    virtual void doCreate(const BwPartInfo& info) ;
	CEGUI::FrameWindow& peer() { return *static_cast<CEGUI::FrameWindow*>(p_peer) ; }
	void write(const bwString& string) ;
	void bindEditBox() ;
public:
	/////////////////
	class Edit : public CEGUI::MultiLineEditbox {
	public:
		Edit(const CEGUI::String& type, const CEGUI::String& name) 
			: CEGUI::MultiLineEditbox(type, name) {
		}
			void write(const bwString& string) {
				//d_text.append(string.c_str()) ;
				appendText(string.c_str()) ;
				//setCaratIndex(d_text.length() - 1) ;
				setCaretIndex(getText().length() - 1) ;
				CEGUI::WindowEventArgs args(this);
					onTextChanged(args);
			}
	} ;
	//Data Members
	Edit* p_edit ;
};
#endif //_VrCeguiConsole_H
