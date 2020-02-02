/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _VrVu_H
#define _VrVu_H

#include <bwcore/BwActor.h>
#include "VrVuInfo.h"

class VrModel ;
class VrScene ;

namespace Ogre {
	class SceneNode ;
	class Entity ;
}
//
//VrVu
//
class VrVu : public BwActor {
public:
	VrVu(VrModel *pModel) ;
	virtual ~VrVu() ;
	virtual void doCreate(const BwPartInfo& info) ;
	virtual bool onCreate(const BwPartInfo& info) ;
	virtual void doEnable(bool sleeping = false) ;
	virtual void doPostEnable(bool sleeping = false) ;
	virtual void doDisable(bool sleeping = true) ;
	virtual void doPostDisable(bool sleeping = true) ;
	virtual void build() {}
	virtual bool onPostStep(BwStepper& stepper) ;
	virtual void updateScene() ;
	virtual void validateNode() ;
	VrModel* getModel() { return p_model ; }
	Ogre::SceneNode* getSceneNode() { return p_sceneNode ; }
	Ogre::Entity* getMeshInstance() { return p_meshInstance ; }
	virtual void createAssets() ;
	virtual void createMeshInstance() ;
	virtual void createSceneNode() ;
	virtual void attachMeshInstance() ;
	void setScale(const bwSize3& scale) ;
	const bwSize3 getScale() { return m_scale ; }
	void setShowBoundingBox(bool flag) ;
	void setIsBatchable(bool val) { m_isBatchable = val ; }
	bool isBatchable() { return m_isBatchable ; }
	//
	void setVuInfo(const VrVuInfo& vuInfo) { m_vuInfo = vuInfo ; }
	const VrVuInfo* getVuInfo() { return &m_vuInfo ; }
	VrVuInfo& vuInfo() { return m_vuInfo ; }
	/*Data Members*/
public:
	VrModel *p_model ;
	bwSize3 m_scale ;
	bool m_isBatchable ;
	//
	VrVuInfo m_vuInfo ;
	/*Ogre*/
	Ogre::Entity* p_meshInstance ;
	Ogre::SceneNode* p_sceneNode ;
	Ogre::SceneNode* p_boundingNode ;
};

#endif //_VrVu_H