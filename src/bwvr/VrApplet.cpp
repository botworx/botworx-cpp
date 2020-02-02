/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <bwcore/BwKernel.h>
#include <bwcore/BwStage.h>

#include <bwvr/VrApplet.h>
#include <bwvr/VrScenario.h>
#include <bwvr/VrScenarioLoader.h>
#include <bwvr/VrSystem.h>

#include <bwvr/config/ogre.h>
/*#include <Direct3D9/OgreD3D9RenderSystem.h>
#include <Direct3D9/OgreD3D9RenderWindow.h>*/

VrApplet::VrApplet(void) : BwApplet() {
	m_name = "Applet" ;
	p_renderRoot = NULL ;
	p_scenario = NULL ;
	p_renderWindow = NULL ;
	p_viewport = NULL ;
	m_isEmbedded = false ;
	m_configMethod = CONFIG_DIALOG ;
	//
	p_nextScenarioFactory = NULL ;
}
VrApplet::~VrApplet() {
	//TODO:note:stage cleans up scenario and scene.
	if(p_renderRoot)
		delete p_renderRoot;
}
/*
void VrApplet::createEmbedded(HWND hwnd, const bwSize2& size) {
	m_isEmbedded = true ;
	m_configMethod = CONFIG_MANUAL ;
	m_hwnd = hwnd ;
	m_windowSize = size ;
	createEnabled() ;
}
*/
void VrApplet::createRenderRoot() {
	bwPath cfName = BwKernel::singleton::get().getMediaPath() ;
	cfName = cfName / getName() ; //name of the applet
#if _DEBUG
	cfName = cfName / "plugins_d.cfg";
#else
	cfName = cfName / "plugins.cfg" ;
#endif
	//Ogre::String pluginsFilename = "plugins.cfg";
    Ogre::String pluginsFilename = cfName.string();
	p_renderRoot = new Ogre::Root(pluginsFilename) ;
}
void VrApplet::destroyRenderRoot() {
	//p_scene->clear() ;
	using namespace Ogre;

	MeshManager::getSingletonPtr()->removeAll();
	SkeletonManager::getSingletonPtr()->removeAll();
	MaterialManager::getSingletonPtr()->removeAll();
	TextureManager::getSingletonPtr()->removeAll();
	GpuProgramManager::getSingletonPtr()->removeAll();

	// destroy / close OGRE
	delete p_renderRoot ;
	p_renderRoot = NULL ;
}
void VrApplet::createRenderSystem() {
	//TODO:fix for multi platform
	// Verify that we found the D3D9 Render system
	/*Ogre::RenderSystem *pRenderSys = Ogre::Root::getSingleton().getRenderSystemByName("Direct3D9 Rendering Subsystem") ;

	Ogre::Root::getSingleton().setRenderSystem (pRenderSys) ;
	p_renderSystem = Ogre::Root::getSingleton().getRenderSystem () ;
	Ogre::D3D9RenderSystem* pD3D9RenderSystem = static_cast<Ogre::D3D9RenderSystem*> (p_renderSystem) ;
	// Default options
	pD3D9RenderSystem->initConfigOptions();
	// Fixed options
	p_renderSystem->setConfigOption("Full Screen", "No");
	p_renderSystem->setConfigOption("VSync", "No");

	// Build up the resolution string
	char buffer [1024] ;

	sprintf (buffer, "%d x %d @ 32-bit colour", int(m_windowSize[0]), int(m_windowSize[1])) ;
	p_renderSystem->setConfigOption("Video Mode", buffer) ;
	p_renderSystem->setConfigOption("Anti aliasing", "None");*/
}
void VrApplet::createRenderWindow() {
	if(!m_isEmbedded) {
		p_renderWindow = p_renderRoot->initialise(true);
		p_renderSystem = Ogre::Root::getSingleton().getRenderSystem () ;
		return ;
	}
	//else
	//TODO:fix for multi platform
	/*createRenderSystem() ;
	p_renderWindow = p_renderRoot->initialise(false);
	Ogre::NameValuePairList miscParams;
	//miscParams["colourDepth"] = StringConverter::toString(32);
	//miscParams["FSAA"] = StringConverter::toString(0);
	//miscParams["FSAAQuality"] = StringConverter::toString(0);
	//miscParams["vsync"] = "false";
	miscParams["externalWindowHandle"] = Ogre::StringConverter::toString((size_t)m_hwnd);
	p_renderWindow = p_renderRoot->createRenderWindow(m_name,
		m_windowSize[0], m_windowSize[1], false, &miscParams ) ;*/
}
void VrApplet::createViewport(Ogre::Camera* pCamera) {
	//if(p_viewport != NULL)	return ; //TODO:how can we accomodate multiple?
	p_viewport = p_renderWindow->addViewport(pCamera);
	p_viewport->setBackgroundColour(Ogre::ColourValue(.5,.5,.5));
}
bool VrApplet::onCreate(const BwPartInfo& info) {
	createScenario() ;
	return BwApplet::onCreate(info) ;
}
void VrApplet::doPostEnable(bool sleeping) {
	BwApplet::doPostEnable(sleeping) ;
}
void VrApplet::onStop() {
//#if VR_OPTION_THREADING
	//p_scenario->stop() ;
//#endif
}
void VrApplet::onGo() {
//#if VR_OPTION_THREADING
	//p_scenario->go() ;
//#endif
}
bool VrApplet::setup(void) {

	createRenderRoot() ;

	setupResources() ;

	bool success = configure();
	if (!success)
		return false;

	Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);

	loadResources() ;

    return true;
}

bool VrApplet::configure(void) {
	bool success = true ;
	switch(m_configMethod) {
		case CONFIG_DIALOG :
			success = p_renderRoot->showConfigDialog() ;
			break ;
		case CONFIG_FILE :
			success = p_renderRoot->restoreConfig() ;
			break ;
		case CONFIG_MANUAL :
			break ;
	}
	createRenderWindow() ;
	return success ;
}
void VrApplet::loadScenario(VrScenarioFactory* pScenarioFactory) {
	if(VrScenario::singleton::getPtr() != NULL)
		unloadScenario(pScenarioFactory) ;
	else {
		VrScenarioLoader* pLoader = new VrScenarioLoader(this, pScenarioFactory) ;
		pLoader->create() ;
	}
}
void VrApplet::nextScenario() {
	if(p_nextScenarioFactory == NULL)
		return ;
	VrScenarioFactory* pScenarioFactory = p_nextScenarioFactory ;
	p_nextScenarioFactory = NULL ;
	VrScenarioLoader* pLoader = new VrScenarioLoader(this, pScenarioFactory, VrScenarioLoader::LOAD_ENABLED) ;
	pLoader->create() ;
}
void VrApplet::createScenario() {
}
void VrApplet::unloadScenario(VrScenarioFactory* pNextScenarioFactory) {
	if(VrScenario::singleton::getPtr() == NULL)
		return ;
	//else
	p_nextScenarioFactory = pNextScenarioFactory ;
	if(pNextScenarioFactory != NULL)
		VrScenario::singleton::get().die() ;
}
//
VrUser* VrApplet::produceUser(VrScene* pScene) {
	bwAssert(0) ;
	return NULL ;
}
//
void VrApplet::setupResources(void) {
    //Fonts
	bwString fontPath ;
	fontPath = getenv("SYSTEMROOT") ;
	fontPath = fontPath + "/Fonts" ;
	Ogre::ResourceGroupManager::getSingleton().addResourceLocation(fontPath , "FileSystem") ;

	// Load resource paths from config file
	Ogre::ConfigFile cf;

	// Load application configuration
	bwPath cfName = BwKernel::singleton::get().getMediaPath() ;
	cfName = cfName / getName() ; //name of the applet
	cfName = cfName / "resources.cfg" ;
	//cf.load(cfName.native_file_string());
    //cf.load(cfName.native());
    //cf.load(cfName.c_str());
    cf.load(cfName.string());

    // Go through all sections & settings in the file
    Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();

    Ogre::String secName, typeName, archName;
    while (seci.hasMoreElements())
    {
        secName = seci.peekNextKey();
        Ogre::ConfigFile::SettingsMultiMap *settings = seci.getNext();
        Ogre::ConfigFile::SettingsMultiMap::iterator i;
        for (i = settings->begin(); i != settings->end(); ++i)
        {
            typeName = i->first;
            archName = i->second;
            Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
                archName, typeName, secName);
        }
    }

}
void VrApplet::loadResources(void) {
		// Initialise, parse scripts etc
	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
}
//singleton support
template<> VrApplet::singleton::pointer VrApplet::singleton::g_singleton = 0 ;
