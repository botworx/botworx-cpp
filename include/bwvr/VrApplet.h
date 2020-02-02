/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _VrApplet_H
#define _VrApplet_H

class VrSystem ;
class VrScenario ;
class VrScenarioFactory ;
class VrScene ;
class VrUser ;

namespace Ogre {
	class Root ;
	class SceneManager ;
	class RenderWindow ;
	class RenderSystem ;
	class Camera;
	class Viewport ;
}

#include <bwapplet/BwApplet.h>

class VrApplet : public BwApplet
{
public:
	VrApplet();
	virtual ~VrApplet();
	// void createEmbedded(HWND hwnd, const bwSize2& size) ;
	virtual bool onCreate(const BwPartInfo& info);
	virtual void doPostEnable(bool sleeping = false);
	//
	//
	VrScenario* getScenario() { return p_scenario ; }
	//
	Ogre::Root* getRenderRoot() { return p_renderRoot ; }
	Ogre::RenderWindow* getRenderWindow() { return p_renderWindow ; }
	bool isEmbedded() { return m_isEmbedded ; }
	//
	virtual void createViewport(Ogre::Camera* pCamera) ;
	Ogre::Viewport* getViewport() { return p_viewport ; }
	//
	void loadScenario(VrScenarioFactory* pScenarioFactory) ;
	virtual void nextScenario() ; //called by VrScenario on destruction ... hmmm...
	//
	virtual VrUser* produceUser(VrScene* pScene) ;
protected:
	virtual void createRenderRoot() ;
	virtual void createRenderWindow() ;
	virtual void createRenderSystem() ;
	virtual void destroyRenderRoot() ;
	//
	virtual void createScenario() ;
	void unloadScenario(VrScenarioFactory* pNextScenarioFactory = NULL) ;
	/*Data Members*/
	VrScenario *p_scenario ;
	VrScenarioFactory* p_nextScenarioFactory ;
	//
	Ogre::Root* p_renderRoot;
	Ogre::RenderSystem *p_renderSystem ;
	Ogre::RenderWindow* p_renderWindow;
	Ogre::Viewport* p_viewport ;
	//
	bool m_isEmbedded ;
	// HWND m_hwnd ;
	bwSize2 m_windowSize ;
	bool m_showConfigDialog ;
	enum configMethods {
		CONFIG_DIALOG = 0,
		CONFIG_FILE,
		CONFIG_MANUAL
	} ;
	typedef configMethods configMethod ;
	configMethod m_configMethod ;
private:
	virtual void onGo() ;
	virtual void onStop() ;
	bool setup(void);
	bool configure(void);
	virtual void setupResources(void) ;
	virtual void loadResources(void) ;
public:
	//Singleton support
	typedef BwSingletonT<VrApplet> singleton ;
	singleton m_singleton ;
};

#endif //_VrApplet_H

