/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <bwvrcegui/VrCeguiConsole.h>
#include <bwvrcegui/VrCeguiGuiController.h>
#include <bwvrcegui/VrCeguiControlPanel.h>
#include <bwvrcegui/VrCeguiUserMode.h>

#include <bwvr/VrScene.h>
#include <bwvr/VrSystem.h>
#include <CEGUI/CEGUI.h>

using namespace CEGUI ;

VrCeguiConsole::VrCeguiConsole(VrCeguiGui *pGui) : VrCeguiWindow(pGui) {
	m_name = "Sheet/Console" ;
}
void VrCeguiConsole::doCreate(const BwPartInfo& info) {
	VrCeguiWindow::doCreate(info) ;
	peer().setTitleBarEnabled(false) ;
	bindEditBox() ;
}
void VrCeguiConsole::bindEditBox() {
	p_edit = new Edit("BotworxLook/ConsoleEdit", "Sheet/Console/Client") ;
    CEGUI::Font* gfont = &CEGUI::FontManager::getSingleton().createFreeTypeFont(
			"Commonwealth-10.font", 10.0, true, "Commonwealth-10.font");
	//gfont->setNativeResolution(CEGUI::Size(1920, 1080));

	p_edit->setFont(gfont) ;

	p_edit->setWindowRenderer("Falagard/MultiLineEditbox") ;
	p_edit->setLookNFeel("BotworxLook/MultiLineEditbox") ;
	p_edit->setPosition(UVector2(cegui_reldim(0.02f), cegui_reldim(0.15f)));
	p_edit->setSize(USize(cegui_reldim(0.96f), cegui_reldim(0.8f)));
	p_edit->setAlpha(.75) ;
	//
	p_edit->setWordWrapping(true) ;
	p_edit->setText("Botworx v0.1\n") ;

	p_peer->addChild(p_edit) ;
}
void VrCeguiConsole::write(const bwString& string) {
	p_edit->write(string) ;
}