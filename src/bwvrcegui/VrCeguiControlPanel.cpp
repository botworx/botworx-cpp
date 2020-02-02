/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <bwvrcegui/VrCeguiControlPanel.h>
#include <bwvrcegui/VrCeguiUserMode.h>

#include <CEGUI/Window.h>
#include <CEGUI/WindowManager.h>
#include <CEGUI/widgets/ScrolledContainer.h>
#include <CEGUI/widgets/ScrollablePane.h>
#include <CEGUI/widgets/Scrollbar.h>

#include <CEGUI/widgets/ButtonBase.h>
#include <CEGUI/widgets/PushButton.h>

using namespace CEGUI ;

VrCeguiControlPanel::VrCeguiControlPanel(VrCeguiGui *pGui) :VrCeguiWindow(pGui) {
	m_buttonTtl = 0 ;
}
void VrCeguiControlPanel::createPeer() {
	p_peer = p_pane = static_cast<ScrollablePane*>(
		WindowManager::getSingleton().createWindow("BotworxLook/ScrollablePane", m_name) 
		) ;

	p_pane->setContentPaneArea(CEGUI::Rect(0.1f,0.1f,.9f,.9f)) ;
	p_peer->setSize(USize(cegui_reldim(1), cegui_reldim(1))) ;
}
void VrCeguiControlPanel::createButton(VrCeguiUserMode *pMode) {
	bwString buttonName = pMode->getName() + "Button" ;

	ButtonBase *pButton = static_cast<ButtonBase*>( 
		WindowManager::getSingleton().createWindow("BotworxLook/Button", buttonName) 
		) ;
	pButton->setText(pMode->getShortName()) ;
	pButton->setSize(USize(cegui_reldim(.9f), cegui_reldim(.05f))) ;
	//
	getPeer()->addChild(pButton) ;
	pButton->setPosition(UVector2(cegui_reldim(.0075f), cegui_reldim(m_buttonTtl*.06f + .025f))) ;
	m_buttonTtl++ ;
	//
	pButton->subscribeEvent(
				CEGUI::PushButton::EventClicked, 
				CEGUI::Event::Subscriber(&VrCeguiControlPanel::handleButtonPress, this));

	m_buttonMap[pButton] = pMode ;
}
bool VrCeguiControlPanel::handleButtonPress(const CEGUI::EventArgs& e) {
	const CEGUI::WindowEventArgs& windowEventArgs = static_cast<const CEGUI::WindowEventArgs&>(e);
	CEGUI::ButtonBase *pButton = static_cast<CEGUI::ButtonBase*>(windowEventArgs.window) ;
	VrCeguiUserMode *pMode = m_buttonMap[pButton] ;
	pMode->activate() ;
	return true ;
}