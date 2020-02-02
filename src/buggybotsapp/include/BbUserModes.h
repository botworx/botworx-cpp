/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _BbUserModes_H
#define _BbUserModes_H

#include <buggybots/BbScenarioFactories.h>

#include <bwvrcegui/VrCeguiUser.h>
#include <bwvrcegui/VrCeguiUserMode.h>
#include <bwvrcegui/VrCeguiFolderMode.h>

#include <bwvr/VrBuilder.h>
#include <bwvr/VrWorld.h>
#include <bwvr/VrCamera.h>
#include <bwvr/VrHand.h>
#include <bwvr/VrCameraVu.h>
#include <bwvr/VrScenario.h>
#include <bwvr/VrScenarioManager.h>
#include <bwvr/VrApplet.h>

#include <bwcore/BwKernel.h>
#include <bwcore/_BwKernel.h>
#include <bwmessaging/BwMailSlot.h>

#include <OGRE/OgreCamera.h> //TODO:wrap it up

class BbFileOpener : public VrCeguiUserMode {
public:
	BbFileOpener(VrCeguiUserMode* pParent, const bwString& name) : VrCeguiUserMode(pParent, name) {}
};
class BbFileSaver : public VrCeguiUserMode {
public:
	BbFileSaver(VrCeguiUserMode* pParent, const bwString& name) : VrCeguiUserMode(pParent, name) {}
};
class BbFileUser : public VrCeguiUserMode {
public:
	BbFileUser(VrCeguiUserMode* pParent, const bwString& name) : VrCeguiUserMode(pParent, name) {}
	virtual void doCreate(const BwPartInfo& info) {
		VrCeguiUserMode::doCreate(info) ;
		createMode(new BbFileOpener(this, "Open")) ;
		createMode(new BbFileSaver(this, "Save")) ;
	}
};
/*This acts like a warp button!*/
class BbCloner : public VrCeguiUserMode {
public:
	BbCloner(VrCeguiUserMode* pParent, const bwString& name) : VrCeguiUserMode(pParent, name) {}
	virtual void activate() {
		VrModel* pSelection = p_user->getSelection() ;
		if(pSelection == NULL)
			return ;
		VrCeguiUserMode* pMode = p_user->findMode("Buggy Bots/Object/" + pSelection->getClassName() + "/Create" ) ;
		if(pMode != NULL)
			pMode->activate() ;
	}
};
class BbSolidViewer : public VrCeguiUserMode {
public:
	BbSolidViewer(VrCeguiUserMode* pParent, const bwString& name) : VrCeguiUserMode(pParent, name) {}
	virtual void activate() {
		VrScenario::singleton::get().enableSky(true) ;
		Ogre::Camera *pOgreCam = static_cast<VrCameraVu*>(p_user->getCamera()->getVu())->getOgreCamera() ;
		pOgreCam->setPolygonMode(Ogre::PM_SOLID) ;
	}
};
class BbWireFrameViewer : public VrCeguiUserMode {
public:
	BbWireFrameViewer(VrCeguiUserMode* pParent, const bwString& name) : VrCeguiUserMode(pParent, name) {}
	virtual void activate() {
		//mWindow->getViewport(0)->setBackgroundColour(ColourValue::White);
		VrScenario::singleton::get().enableSky(false) ;
		Ogre::Camera *pOgreCam = static_cast<VrCameraVu*>(p_user->getCamera()->getVu())->getOgreCamera() ;
		pOgreCam->setPolygonMode(Ogre::PM_WIREFRAME) ;
	}
};
class BbViewer : public VrCeguiUserMode {
public:
	BbViewer(VrCeguiUserMode* pParent, const bwString& name) : VrCeguiUserMode(pParent, name) {}
	virtual void doCreate(const BwPartInfo& info) {
		VrCeguiUserMode::doCreate(info) ;
		createMode(new BbSolidViewer(this, "Solid")) ;
		createMode(new BbWireFrameViewer(this, "Wire Frame")) ;
	}
};
class BbObjectCreator : public VrCeguiUserMode {
public:
	BbObjectCreator(VrCeguiUserMode* pParent, const bwString& name) : VrCeguiUserMode(pParent, name) {}
	virtual void activate() ;
};
class BbSleepingObjectCreator : public VrCeguiUserMode {
public:
	BbSleepingObjectCreator(VrCeguiUserMode* pParent, const bwString& name) : VrCeguiUserMode(pParent, name) {
	}
	virtual void activate() {
		p_user->getHand()->buildEnabled(p_parent->getShortName(), bwPose(), true) ;
	}
};
class BbAvatarCreator : public VrCeguiUserMode {
public:
	BbAvatarCreator(VrCeguiUserMode* pParent, const bwString& name) : VrCeguiUserMode(pParent, name) {
	}
	virtual void activate() {
		bwString name = p_parent->getShortName() ;
		VrModel *pAvatar = p_user->getHand()->buildEnabled(name) ;
		p_user->switchAvatar(pAvatar) ;
		_BwKernel::Info evt("User built a " + name + "\n") ;
		BwKernel::singleton::get().getEventSlot()->send(evt) ;
	}
};
class BbObjectUser : public VrCeguiUserMode {
public:
	BbObjectUser(VrCeguiUserMode* pParent, const bwString& name) : VrCeguiUserMode(pParent, name) {}
	virtual void doCreate(const BwPartInfo& info) {
		VrCeguiUserMode::doCreate(info) ;
		createMode(new BbObjectCreator(this, "Create")) ;
		createMode(new BbSleepingObjectCreator(this, "Create Sleeper")) ;
		createMode(new BbAvatarCreator(this, "Create Avatar")) ;
		createMode(new BbCloner(this, "Clone")) ;
	}
};
class BbObjectManager : public VrCeguiUserMode {
public:
	BbObjectManager(VrCeguiUserMode* pParent, const bwString& name) : VrCeguiUserMode(pParent, name) {}
	virtual void doCreate(const BwPartInfo& info) {
		VrCeguiUserMode::doCreate(info) ;
		VrModelFactoryContainer *pFactories = VrBuilder::singleton::get().getFactories() ;
		VrModelFactory *pModelFactory = NULL ;
		bwString factoryName ;
		for(VrModelFactoryContainer::iterator iter = pFactories->begin();
			iter != pFactories->end(); ++iter)	{
			pModelFactory = (*iter) ;
			factoryName = pModelFactory->getName() ;
			VrCeguiUserMode *pMode = new BbObjectUser(this, factoryName) ;
			createMode(pMode) ;
		}
	}
};
class BbScenarioCreator : public VrCeguiUserMode {
public:
	BbScenarioCreator(VrCeguiUserMode* pParent, const bwString& name) : VrCeguiUserMode(pParent, name) {}
	virtual void activate() {
		bwString name = getShortName() ;
		p_user->loadScenario(name) ;
		_BwKernel::Info evt("User built a " + name + "\n") ;
		BwKernel::singleton::get().getEventSlot()->send(evt) ;
	}
};
class BbScenarioManager : public VrCeguiUserMode {
public:
	BbScenarioManager(VrCeguiUserMode* pParent, const bwString& name) : VrCeguiUserMode(pParent, name) {}
	virtual void doCreate(const BwPartInfo& info) {
		VrCeguiUserMode::doCreate(info) ;
		VrScenarioFactories& factories = VrScenarioManager::singleton::get().factories() ;
		VrScenarioFactory* pScenarioFactory = NULL ;
		bwString factoryName ;
		for(VrScenarioFactoryIter iter = factories.begin();
			iter != factories.end(); ++iter)	{
			pScenarioFactory = (*iter) ;
			factoryName = pScenarioFactory->getName() ;
			VrCeguiUserMode *pMode = new BbScenarioCreator(this, factoryName) ;
			createMode(pMode) ;
		}
	}
};

#if BB_OPTION_USE_COLLADA

/*class BbColladaCreator : public VrCeguiFileMode {
public:
	BbColladaCreator(VrCeguiUserMode* pParent, const bwPath& path) : VrCeguiFileMode(pParent, path) {}
	virtual void activate() {
		//VrCeguiFileMode::activate() ;
		bwString name = getShortName() ;
		VrScenarioFactory* pFactory = VrScenarioManager::singleton::get().findFactory(name) ;
		if(pFactory == NULL) {
			pFactory = new BbColladaScenarioFactory(this, m_path) ; //TODO:use singleton
			pFactory->create() ;
			VrScenarioManager::singleton::get().addFactory(pFactory) ;
		}
		p_user->loadScenario(name) ;
		_BwKernel::Info evt("User built a " + name + "\n") ;
		BwKernel::singleton::get().getEventSlot()->send(evt) ;
	}
};
class BbColladaManager : public VrCeguiFolderMode {
public:
	BbColladaManager(VrCeguiUserMode* pParent, const bwPath& path) : VrCeguiFolderMode(pParent, path) {}
	virtual void doCreate(const BwPartInfo& info) {
		VrCeguiFolderMode::doCreate(info) ;
	}
	virtual void createFileMode(const bwPath& path) {
		createMode(new BbColladaCreator(this, path)) ;
	}
	virtual void createFolderMode(const bwPath& path) {
		createMode(new BbColladaManager(this, path)) ;
	}
};*/

#endif //BB_OPTION_USE_COLLADA

class BbEditor : public VrCeguiUserMode {
public:
	BbEditor(VrCeguiUserMode* pParent, const bwString& name) : VrCeguiUserMode(pParent, name) {}
	virtual void activate() {
		VrModel* pSelection = p_user->getSelection() ;
		if(pSelection == NULL)
			return ;
		VrCeguiUserMode* pMode = p_user->findMode("Buggy Bots/Object/" + pSelection->getClassName() ) ;
		if(pMode != NULL)
			p_user->pushMode(pMode) ;
	}
};
class BbQuitter : public VrCeguiUserMode {
public:
	BbQuitter(VrCeguiUserMode* pParent, const bwString& name) : VrCeguiUserMode(pParent, name) {}
	virtual void activate() {
		p_user->requestShutdown() ;
	}
};
class BbMainMode : public VrCeguiUserMode {
public:
	BbMainMode(VrCeguiUser* pUser, const bwString& name) : VrCeguiUserMode(NULL, name) {
		p_user = pUser ;
	}
	virtual void doCreate(const BwPartInfo& info) {
		VrCeguiUserMode::doCreate(info) ;
		createMode(new BbScenarioManager(this, "Scenario")) ;
	#if BB_OPTION_USE_COLLADA
		//createMode(new BbColladaManager(this, VrApplet::singleton::get().getMediaPath() / "scenario")) ;
	#endif// BB_OPTION_USE_COLLADA
		createMode(new BbFileUser(this, "File")) ;
		createMode(new BbObjectManager(this, "Object")) ;
		createMode(new BbEditor(this, "Edit")) ;
		createMode(new BbViewer(this, "View")) ;
		createMode(new BbQuitter(this, "Quit")) ;
	}
};
#endif //_BbUserModes_H