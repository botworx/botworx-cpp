/*BuggyBots - A Botworx VR reference app and AI playground
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <bwvr/VrSharedVu.h>
#include <bwvr/VrScene.h>
#include <bwvr/VrGroup.h>
#include <bwvr/VrPlace.h>

#include <bwvr/config/ogre.h>

VrSharedVu::VrSharedVu(VrPlace *pPlace) : VrVu (pPlace) {
	p_place = pPlace ;
}
VrSharedVu::~VrSharedVu() {
}
void VrSharedVu::doPostEnable(bool sleeping) {
	build() ;
	VrVu::doPostEnable(sleeping) ;
}
void VrSharedVu::doPostDisable(bool sleeping) {
	VrScene::singleton::get().getManager()->destroyStaticGeometry(p_geometry) ;
	VrVu::doPostDisable(sleeping) ;
}
void VrSharedVu::build() {
	p_geometry  = VrScene::singleton::get().getManager()->createStaticGeometry(p_model->getName());
	p_geometry->setRegionDimensions(
		Ogre::Vector3(p_model->getWidth(), p_model->getHeight(), p_model->getLength() ) ) ;

	bwVector3 groupPos = p_place->getPos() ;
	p_geometry->setOrigin(Ogre::Vector3(groupPos[0], groupPos[1], groupPos[2]));
	//
	VrModel *pModel = NULL ;
	VrPlace *pPlace = NULL ;
	bwVector3 spacePos ;
	bwQuat spaceQuat ;

	VrVu *pVu = NULL ;

	VrModelContainer *pStatics = p_place->collectStaticModels() ;
	if(pStatics == NULL)
		return ;
	for (VrModelContainer::iterator iter = pStatics->begin(); //copy
			iter != pStatics->end(); ++iter)	{
		pModel = (*iter) ;
		pVu = pModel->getVu() ;
		if(pVu == NULL)
			continue ;
		if(!pVu->isBatchable())
			continue ;
		spacePos = pModel->getPos() ;
		spaceQuat = pModel->getQuat() ;

		bwVector3 scale = pVu->getScale() ;
		Ogre::Entity *pEntity = pVu->getMeshInstance() ;
		if(pEntity == NULL)
			continue ;
		//bwAssert(scale[0] != 0 && scale[1] != 0 && scale[2] != 0) ;
		//
		pModel->setIsPlaceable(false) ; //so it can't be moved by the hand.
		//
		p_geometry->addEntity(
			pVu->getMeshInstance(),
			Ogre::Vector3(spacePos[0], spacePos[1], spacePos[2]),
			Ogre::Quaternion(spaceQuat[3], spaceQuat[0], spaceQuat[1], spaceQuat[2]),
			Ogre::Vector3(scale[0], scale[1], scale[2])
			);
	}
	p_geometry->build() ;
}
