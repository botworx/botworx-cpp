/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <bwvrcegui/VrCeguiControlFrame.h>
#include <bwvrcegui/VrCeguiGuiController.h>
#include <bwvrcegui/VrCeguiControlPanel.h>
#include <bwvrcegui/VrCeguiUserMode.h>

#include <bwvr/VrScene.h>

#include <bwvr/config/cegui.h>

using namespace CEGUI ;
/////////////////////////////////////////
VrCeguiControlFrame::VrCeguiControlFrame(VrCeguiGui *pGui) : VrCeguiWindow(pGui) {
	m_name = "Sheet/ControlFrame" ;
	p_controlPanel = NULL ;
}
void VrCeguiControlFrame::setControlPanel(VrCeguiUserMode *pMode) {
	if(p_controlPanel != NULL)
		p_peer->getChild("Sheet/ControlFrame/Client")->removeChild(p_controlPanel->getPeer()) ;

	p_peer->setText(pMode->getShortName()) ;
	p_controlPanel = pMode->getControlPanel() ;
	CEGUI::Window* pCpPeer = p_controlPanel->getPeer() ;
	p_peer->getChild("Sheet/ControlFrame/Client")->addChild(pCpPeer) ;
}