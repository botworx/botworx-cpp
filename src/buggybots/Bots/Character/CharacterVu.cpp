/*CharacterBots - A Botworx VR reference app and AI playground
Copyright (C) 2005  Kurtis Fields. See botworx_license.txt for details.
*/
#include "stdafx.h"

#include <buggybots/bots/character/CharacterVu.h>
#include <buggybots/bots/character/Character.h>

#include <bwvr/VrScene.h>
#include <bwvr/VrBody.h>
#include <bwvr/VrPhysics.h>

#include <bwvr/config/ogre.h>
#include <OGRE/OgreLogManager.h>

using namespace bwmath ;

namespace Character {

CharacterVu::CharacterVu(Character *pCharacter) : VrVu(pCharacter) {
	p_animat = pCharacter ;
	p_animState = NULL ;
	p_skelNode = NULL ;
}
void CharacterVu::createSceneNode() {
	VrVu::createSceneNode() ;
	bwQuat quat = m_vuInfo.getMeshQuat() ;
	bwPoint3 pos = m_vuInfo.getMeshPos() ;
	p_skelNode = p_sceneNode->createChildSceneNode(
		p_animat->makeThingName("skelNode"),
		Ogre::Vector3(pos[0], pos[1], pos[2]),
		Ogre::Quaternion(quat[3], quat[0], quat[1], quat[2])
		) ;
}
void CharacterVu::createMeshInstance() {
	VrVu::createMeshInstance() ;
	//
	const Ogre::AnimationStateSet* states = p_meshInstance->getAllAnimationStates();
	if (states)	{
		Ogre::ConstAnimationStateIterator iter = states->getAnimationStateIterator();
		while (iter.hasMoreElements()) {
			Ogre::AnimationState* anim = iter.getNext();
			Ogre::LogManager::getSingleton().logMessage("Entity "+p_meshInstance->getName()+" has animation"+anim->getAnimationName());
		}
	}
	else {
		Ogre::LogManager::getSingleton().logMessage("Entity "+p_meshInstance->getName()+" has no state");
	}
	//
	p_animState = p_meshInstance->getAnimationState("Walk");
	p_animState->setEnabled(true);
}
void CharacterVu::attachMeshInstance() {
	p_skelNode->attachObject(p_meshInstance);
}
bool CharacterVu::onPostStep(BwStepper& stepper) {
	bwDT deltaTime = VrPhysics::singleton::get().getDeltaTime() ;
	VrModel *pModel = static_cast<VrGroup*>(p_model)->getMain() ;
	bwReal speed = fabs(mag(pModel->getBody()->getLinearVel())) ;
	p_animState->addTime(speed * deltaTime * .5) ;
	return VrVu::onPostStep(stepper) ;
}
void CharacterVu::validateNode() {
	bwVector3 pos ;
	bwQuat quat ;
	VrModel *pModel = static_cast<VrGroup*>(p_model)->getMain() ;
	pos = pModel->getPos() ;
	if(p_sceneNode != NULL)
		p_sceneNode->setPosition(pos[0], pos[1], pos[2]);

	quat = pModel->getQuat() ;
	if(p_sceneNode != NULL)
		p_sceneNode->setOrientation(quat[3],quat[0],quat[1],quat[2]);
}

} //namespace Character
