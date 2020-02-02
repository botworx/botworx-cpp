/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _VrScenario_H
#define _VrScenario_H

#include <bwcore/BwRunner.h>
#include "VrPhysics.h"

class VrApplet ;
class VrScenario ;
class VrPlace ;
class VrGroup ;
class VrCamera ;
class VrHand ;
class VrBuilder ;
class VrScene ;
//
//VrScenario
//
class VrScenario : public BwRunner {
public:
	VrScenario(VrApplet* pApplet) ;
	virtual ~VrScenario() ;
	virtual void doCreate(const BwPartInfo& info) ;
	virtual bool onCreate(const BwPartInfo& info) ;
	virtual void doPostDisable(bool sleeping = true) ;
	virtual void doStep(BwStepper& stepper) ;
	virtual bool die() ;
	//
	virtual void createPhysics() ;
	//
	virtual void createScene() ;
	VrScene* getScene() { return p_scene ; }
	//
	virtual void createWorld() ;
	virtual void createGround() {}
	virtual void createProps() {}
	virtual void createAvatar() {}
	virtual void createCamera(VrGroup *pGroup) ;
	virtual void createHand(VrGroup *pGroup) ;
	//
	virtual void enableSky(bool val) {}
	virtual void onLoad() ;
	//
	bwPath getMediaPath() ;
	//
	VrBuilder& builder() { return *getBuilder() ; }
	VrBuilder* getBuilder() ;
	void switchAvatar(VrModel *pAvatar) ;
	//
	VrModel* getAvatar() { return p_avatar ; }
	VrCamera* getCamera() { return p_camera ; }
	VrHand* getHand() { return p_hand ; }
	VrPlace* getWorld() { return p_world ; }
	//
	virtual void bind() ;
	virtual void unbind() ;
	bool isLoaded() { return m_isLoaded ; }
	//Data Members
	VrApplet* p_applet ;
	VrScene *p_scene ;
	VrPlace* p_world ;
	VrModel *p_avatar ;
	VrCamera *p_camera ;
	VrHand *p_hand ;
	//
	bool m_usesGround ;
	bool m_usesProps ;
	//
	bool m_isLoaded ;
	//Singleton support
	typedef BwSingletonT<VrScenario> singleton ;
	singleton m_singleton ;
} ;

#endif //_VrScenario_H
