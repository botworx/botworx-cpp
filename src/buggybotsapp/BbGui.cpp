/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <CEGUI/widgets/FrameWindow.h>

#include "BbGui.h"
#include <bwvrcegui/VrCeguiUser.h>
#include <bwvrcegui/VrCeguiUserMode.h>
#include "BbSheet.h"
#include "BbControlFrame.h"
#include <bwvrcegui/VrCeguiEventConsole.h>
/////////////////////////////////////////
BbGui::BbGui(VrScene *pScene) : VrCeguiGui(pScene) {
}
BbGui::~BbGui() {
}
void BbGui::doCreate(const BwPartInfo& info) {
	VrCeguiGui::doCreate(info) ;

	VrCeguiWindow *pSheet = new BbSheet(this) ;
	pSheet->create() ;
	setSheet(pSheet) ;

	p_controlFrame = new BbControlFrame(this) ;
	p_controlFrame->create() ;

	p_console = new VrCeguiEventConsole(this) ;
	p_console->create() ;
}