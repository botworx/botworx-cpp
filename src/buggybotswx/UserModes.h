/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _BbxUserModes_H
#define _BbxUserModes_H

#include <bwkernel/BwKernel.h>
#include <bwmessaging/BwMessaging.h>

#include <BwxUserMode.h>
#include <bwvr/VrBuilder.h>
#include <bwvr/VrWorld.h>
#include <bwvr/VrCameraVu.h> //f6:fixme:out of place?
#include <bwvr/VrScenarioManager.h>
#include <bwvr/VrScenario.h>

#include "BbScenarioFactories.h"


#include <bwvr/config/ogre.h>

class BbxFileOpener : public BwxUserMode {
public:
	BbxFileOpener(BwxUserMode* pParent, bwString name) : BwxUserMode(pParent, name) {}
};
class BbxFileSaver : public BwxUserMode {
public:
	BbxFileSaver(BwxUserMode* pParent, bwString name) : BwxUserMode(pParent, name) {}
};
class BbxFileUser : public BwxUserMode {
public:
	BbxFileUser(BwxUserMode* pParent, bwString name) : BwxUserMode(pParent, name) {}
	virtual void doCreate(const BwPartInfo& info) {
		BwxUserMode::doCreate(info) ;
		createMode(new BbxFileOpener(this, "Open")) ;
		createMode(new BbxFileSaver(this, "Save")) ;
	}
};
/*This acts like a warp button!*/
class BbxCloner : public BwxUserMode {
public:
	BbxCloner(BwxUserMode* pParent, bwString name) : BwxUserMode(pParent, name) {}
	virtual void activate() {
		VrSpace* pSelection = p_user->getSelection() ;
		if(pSelection == NULL)
			return ;
		BwxUserMode* pMode = p_user->findMode("Buggy Bots/Object/" + pSelection->getClassName() + "/Create" ) ;
		if(pMode != NULL)
			pMode->activate() ;
	}
};
class BbxSolidViewer : public BwxUserMode {
public:
	BbxSolidViewer(BwxUserMode* pParent, bwString name) : BwxUserMode(pParent, name) {}
	virtual void activate() {
		VrScenario::singleton::get().enableSky(true) ;
		Ogre::Camera *pOgreCam = static_cast<VrCameraVu*>(p_user->getCamera()->getVu())->getOgreCamera() ;
		pOgreCam->setPolygonMode(Ogre::PM_SOLID) ;
	}
};
class BbxWireFrameViewer : public BwxUserMode {
public:
	BbxWireFrameViewer(BwxUserMode* pParent, bwString name) : BwxUserMode(pParent, name) {}
	virtual void activate() {
		//mWindow->getViewport(0)->setBackgroundColour(ColourValue::White);
		VrScenario::singleton::get().enableSky(false) ;
		Ogre::Camera *pOgreCam = static_cast<VrCameraVu*>(p_user->getCamera()->getVu())->getOgreCamera() ;
		pOgreCam->setPolygonMode(Ogre::PM_WIREFRAME) ;
	}
};
class BbxViewer : public BwxUserMode {
public:
	BbxViewer(BwxUserMode* pParent, bwString name) : BwxUserMode(pParent, name) {}
	virtual void doCreate(const BwPartInfo& info) {
		BwxUserMode::doCreate(info) ;
		createMode(new BbxSolidViewer(this, "Solid")) ;
		createMode(new BbxWireFrameViewer(this, "Wire Frame")) ;
	}
};
class BbxObjectCreator : public BwxUserMode {
public:
	BbxObjectCreator(BwxUserMode* pParent, bwString name) : BwxUserMode(pParent, name) {}
	virtual void activate() {
		bwString name = p_parent->getShortName() ;
		p_user->getHand()->buildEnabled(name) ;
		BwKernel::Info evt("User built a " + name + "\n") ;
		BwKernel::singleton::get().getEventSlot()->send(evt) ;
	}
};
class BbxSleepingObjectCreator : public BwxUserMode {
public:
	BbxSleepingObjectCreator(BwxUserMode* pParent, bwString name) : BwxUserMode(pParent, name) {
	}
	virtual void activate() {
		p_user->getHand()->buildEnabled(p_parent->getShortName(), bwPose(), true) ;
	}
};
class BbxObjectUser : public BwxUserMode {
public:
	BbxObjectUser(BwxUserMode* pParent, bwString name) : BwxUserMode(pParent, name) {}
	virtual void doCreate(const BwPartInfo& info) {
		BwxUserMode::doCreate(info) ;
		createMode(new BbxObjectCreator(this, "Create")) ;
		createMode(new BbxSleepingObjectCreator(this, "Create Sleeper")) ;
		createMode(new BbxCloner(this, "Clone")) ;
	}
};
class BbxObjectManager : public BwxUserMode {
public:
	BbxObjectManager(BwxUserMode* pParent, bwString name) : BwxUserMode(pParent, name) {}
	virtual void doCreate(const BwPartInfo& info) {
		BwxUserMode::doCreate(info) ;
		VrSpaceFactoryContainer *pFactories = VrBuilder::singleton::get().getFactories() ;
		VrSpaceFactory *pSpaceFactory = NULL ;
		bwString factoryName ;
		for(VrSpaceFactoryContainer::iterator iter = pFactories->begin();
			iter != pFactories->end(); iter++)	{
			pSpaceFactory = (*iter) ;
			factoryName = pSpaceFactory->getName() ;
			BwxUserMode *pMode = new BbxObjectUser(this, factoryName) ;
			createMode(pMode) ;
		}
	}
};
class BbxEditor : public BwxUserMode {
public:
	BbxEditor(BwxUserMode* pParent, bwString name) : BwxUserMode(pParent, name) {}
	virtual void activate() {
		VrSpace* pSelection = p_user->getSelection() ;
		if(pSelection == NULL)
			return ;
		BwxUserMode* pMode = p_user->findMode("Buggy Bots/Object/" + pSelection->getClassName() ) ;
		if(pMode != NULL)
			p_user->pushMode(pMode) ;
	}
};
class BbxQuitter : public BwxUserMode {
public:
	BbxQuitter(BwxUserMode* pParent, bwString name) : BwxUserMode(pParent, name) {}
	virtual void activate() {
		p_user->requestShutdown() ;
	}
};
//
class BbxScenarioCreator : public BwxUserMode {
public:
	BbxScenarioCreator(BwxUserMode* pParent, bwString name) : BwxUserMode(pParent, name) {}
	virtual void activate() {
		bwString name = getShortName() ;
		VrApplet::singleton::get().loadScenario(VrScenarioManager::singleton::get().findFactory(name)) ;
		BwKernel::Info evt("User built a " + name + "\n") ;
		BwKernel::singleton::get().getEventSlot()->send(evt) ;
	}
};
class BbxScenarioManager : public BwxUserMode {
public:
	BbxScenarioManager(BwxUserMode* pParent, bwString name) : BwxUserMode(pParent, name) {}
	virtual void doCreate(const BwPartInfo& info) {
		BwxUserMode::doCreate(info) ;
		VrScenarioFactories& factories = VrScenarioManager::singleton::get().factories() ;
		VrScenarioFactory* pScenarioFactory = NULL ;
		bwString factoryName ;
		for(VrScenarioFactoryIter iter = factories.begin();
			iter != factories.end(); iter++)	{
			pScenarioFactory = (*iter) ;
			factoryName = pScenarioFactory->getName() ;
			BwxUserMode *pMode = new BbxScenarioCreator(this, factoryName) ;
			createMode(pMode) ;
		}
	}
};

//
class BbxMainMode : public BwxUserMode {
public:
	BbxMainMode(BwxUser* pUser, bwString name) : BwxUserMode(NULL, name) {
		p_user = pUser ;
	}
	virtual void doCreate(const BwPartInfo& info) {
		BwxUserMode::doCreate(info) ;
		createMode(new BbxFileUser(this, "File")) ;
		createMode(new BbxScenarioManager(this, "Scenario")) ;
		createMode(new BbxObjectManager(this, "Object")) ;
		createMode(new BbxEditor(this, "Edit")) ;
		createMode(new BbxViewer(this, "View")) ;
		createMode(new BbxQuitter(this, "Quit")) ;
	}
};
#endif //_BbxUserModes_H