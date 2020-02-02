/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <bwvrcegui/VrCeguiGui.h>
#include <bwvrcegui/VrCeguiGuiController.h>
#include <bwvrcegui/VrCeguiControlFrame.h>
#include <bwvrcegui/VrCeguiConsole.h>
#include <bwvrcegui/VrCeguiWindow.h>

#include <bwvr/VrScene.h>

#include <bwvr/config/ogre.h>
#include <bwvr/config/cegui.h>

using namespace CEGUI ;

VrCeguiGui::VrCeguiGui(VrScene *pScene) : BwPart(pScene) {
	p_scene = pScene ;
	p_guiRenderer = NULL ;
	p_guiSystem = NULL ;
	p_sheet = NULL ;
	//
	p_controlFrame = NULL ;
	p_console = NULL ;
}
VrCeguiGui::~VrCeguiGui() {
	delete p_controlFrame ;
	delete p_console ;
	delete p_sheet ;
	//delete p_guiSystem;
    p_guiSystem->destroy();
	//delete p_guiRenderer;
    p_guiRenderer->destroy(*p_guiRenderer);
}
void VrCeguiGui::doCreate(const BwPartInfo& info) {
	BwPart::doCreate(info) ;
    p_guiRenderer = &CEGUI::OgreRenderer::create(*p_scene->getRenderWindow());    
    CEGUI::OgreResourceProvider* pResourceProvider = &p_guiRenderer->createOgreResourceProvider();
    p_guiSystem = &CEGUI::System::create(*p_guiRenderer, pResourceProvider);

    CEGUI::Logger::getSingleton().setLoggingLevel(CEGUI::Informative);

   //TODO:virtual load_scheme?
    CEGUI::SchemeManager::getSingleton().createFromFile(
            "BotworxLook.scheme");
    //p_guiSystem->setDefaultMouseCursor("BotworxLook", "MouseArrow");
 		p_guiSystem->getDefaultGUIContext().getMouseCursor().setDefaultImage("BotworxLook/MouseArrow");
    //p_guiSystem->setDefaultFont("Tahoma-12");
}
void VrCeguiGui::setSheet(VrCeguiWindow* pWindow) {
	p_sheet = pWindow ;
	Window *pPeer = pWindow->getPeer() ;
    // set area rectangle
    pPeer->setArea(URect(cegui_reldim(0), cegui_reldim(0), cegui_reldim(1), cegui_reldim(1)));

	// p_guiSystem->setGUISheet(pPeer) ;
	p_guiSystem->getDefaultGUIContext().setRootWindow(pPeer);
}