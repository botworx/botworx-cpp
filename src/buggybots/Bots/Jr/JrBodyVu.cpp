/*JrBots - A Botworx VR reference app and AI playground
Copyright (C) 2005  Kurtis Fields. See JrBots_License.txt for details.
*/
#include "stdafx.h"

#include <buggybots/bots/jr/JrBodyVu.h>
#include <buggybots/bots/jr/JrBody.h>
#include <buggybots/bots/jr/Jr.h>

#include <bwvr/VrScene.h>
#include <bwvr/config/ogre.h>

namespace Jr {
JrBodyVu::JrBodyVu(JrBody *pChassis) : VrVu (pChassis) {
	p_chassis = pChassis ;
	m_vuInfo.m_meshName = "VrBox.mesh" ;
}
void JrBodyVu::createSceneNode() {
	VrVu::createSceneNode() ;

	//Rear Axle
	Ogre::SceneNode *pAxleNode2 = NULL ;
	pAxleNode2 = p_sceneNode->createChildSceneNode(
		p_chassis->makeThingName("axleNode2"),
		Ogre::Vector3(0, -.45, 0)
		) ;

	Ogre::Entity *pAxle2 = VrScene::singleton::get().getManager()->createEntity(p_chassis->makeThingName("axle2"), "buggybot-axle.mesh");
	pAxleNode2->attachObject(pAxle2);

}
/*void JrBodyVu::createMeshInstance() {
	p_meshInstance = p_scene->getManager()->createEntity(p_chassis->getName(), "VrBox.mesh");
	//createLight() ;
}*/
void JrBodyVu::createLight() {
	p_light = VrScene::singleton::get().getManager()->createLight(p_chassis->makeThingName("light"));
	p_light->setType(Ogre::Light::LT_SPOTLIGHT);
	p_light->setPosition(0, 0, -2);
	p_light->setDirection(0, 0, -1);
	p_light->setSpotlightRange(Ogre::Radian(30), Ogre::Radian(40));
	p_light->setAttenuation(10, 1, 0, 0);
	p_light->setDiffuseColour(Ogre::ColourValue(1.0, 1.0, 1.0));
	p_light->setSpecularColour(Ogre::ColourValue(0.0, 0.0, 0.0));
	p_sceneNode->attachObject(p_light);
}
}//end namespace Jr {
