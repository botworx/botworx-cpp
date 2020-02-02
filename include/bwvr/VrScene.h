/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _VrScene_H
#define _VrScene_H

namespace Ogre {
	class Root ;
	class SceneManager ;
	class RenderWindow ;
	class RenderSystem ;
	class Camera;
	class Overlay ;
}
#include <bwcore/BwRunner.h>

class VrUser ;
class VrScenario ;
//
//VrScene
//
class VrScene : public BwRunner {
public:
	VrScene(VrScenario *pScenario);
	virtual ~VrScene();
	virtual void doCreate(const BwPartInfo& info) ;
	virtual void doPostDisable(bool sleeping = true) ;
	//
	VrScenario& getScenario() { return *(VrScenario*)p_owner ; }
	void clear() ;
	void setRenderRoot(Ogre::Root* pRoot) { p_renderRoot = pRoot ; }
	void setRenderWindow(Ogre::RenderWindow *pRenderWindow) { p_renderWindow = pRenderWindow ; }
	virtual void createUser() {}
	void setUser(VrUser* pUser) { p_user = pUser ; }
	VrUser* getUser() { return p_user ; }
	virtual void doStep(BwStepper& stepper) ;
	virtual void doPostStep(BwStepper& stepper) ;
	bool startFrame() ;
	void endFrame() ;
	virtual void onFrameStart() {} //currently unused
	virtual void onFrameEnd() {}
	//
	Ogre::RenderWindow* getRenderWindow() { return p_renderWindow ; }
	//
	Ogre::SceneManager& manager() { return *getManager() ; }
	Ogre::SceneManager* getManager() { return p_sceneManager ; }
	virtual void createCamera() ;
	virtual void createWorldGeometry() {}
	Ogre::Camera* getCamera() { return p_camera ; }
	void bind() ;
	void unbind() ;
	//
	Ogre::Root* getRenderRoot() { return p_renderRoot ; }
protected:
	virtual void createManager() ;
	Ogre::SceneManager* p_sceneManager;
	Ogre::Root* p_renderRoot ;
	Ogre::RenderWindow* p_renderWindow;
	Ogre::Camera *p_camera ;
	Ogre::Overlay *p_overlay ;
	//
	VrUser *p_user ;
public:
	//Singleton support
	typedef BwSingletonT<VrScene> singleton ;
	singleton m_singleton ;

};

#endif //_VrScene_H