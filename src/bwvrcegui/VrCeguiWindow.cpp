/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <bwvrcegui/VrCeguiWindow.h>

#include <bwvr/config/cegui.h>

VrCeguiWindow::VrCeguiWindow(VrCeguiGui *pGui) : BwPart(pGui) {
	p_gui = pGui ;
	p_peer = NULL ;
	m_isManuallyCreated = false ;
}
void VrCeguiWindow::doCreate(const BwPartInfo& info) {
	BwPart::doCreate(info) ;
	/*CEGUI::Window* pSheet = CEGUI::System::getSingleton().getGUISheet();
    p_peer = CEGUI::WindowManager::getSingleton().loadWindowLayout(m_layoutFileName);
    p_peer->hide();
    pSheet->addChildWindow(p_peer);
    this->subscribeEvents(default_event_handler);*/
	createPeer() ;
}
void VrCeguiWindow::createPeer() {
	if(!m_layoutFileName.empty())
		p_peer = CEGUI::WindowManager::getSingleton().loadLayoutFromFile(m_layoutFileName);
	else
		if(!m_name.empty() && !m_isManuallyCreated )
			//p_peer = CEGUI::WindowManager::getSingleton().getWindow(m_name);
			throw BwException();
}
void VrCeguiWindow::createDefaultWindow() {
	setIsManuallyCreated(true) ;
	p_peer = CEGUI::WindowManager::getSingleton().createWindow("DefaultWindow", m_name) ;
}
void VrCeguiWindow::show() { p_peer->show() ; }
void VrCeguiWindow::hide() { p_peer->hide() ; }
bool VrCeguiWindow::isVisible() { return p_peer->isVisible() ; }

