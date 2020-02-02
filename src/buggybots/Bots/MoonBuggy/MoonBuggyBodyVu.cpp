/*BuggyBots - A Botworx VR reference app and AI playground
Copyright (C) 2005  Kurtis Fields. See BuggyBots_License.txt for details.
*/
#include "stdafx.h"

#include <buggybots/bots/moonbuggy/MoonBuggyBodyVu.h>
#include <buggybots/bots/moonbuggy/MoonBuggyChassis.h>
#include <buggybots/bots/moonbuggy/MoonBuggy.h>

#include <bwvr/VrScene.h>
#include <bwvr/config/ogre.h>

namespace MoonBuggy {
BuggyChassisVu::BuggyChassisVu(BuggyChassis *pChassis) : VrVu (pChassis) {
	p_chassis = pChassis ;
}
void BuggyChassisVu::createSceneNode() {
	VrVu::createSceneNode() ;

	//Tranny Box
	Ogre::SceneNode *pTrannyNode = NULL ;
	pTrannyNode = p_sceneNode->createChildSceneNode(
		p_chassis->makeThingName("trannyNode"),
		Ogre::Vector3(0, -.35, 0)
		) ;

	Ogre::Entity *pTranny = VrScene::singleton::get().getManager()->createEntity(p_chassis->makeThingName("tranny"), "buggybot-tranny.mesh");
	pTrannyNode->attachObject(pTranny);
	pTrannyNode->scale(.75, .45, 2.5) ;

	//Front Axle
	Ogre::SceneNode *pAxleNode1 = NULL ;
	pAxleNode1 = p_sceneNode->createChildSceneNode(
		p_chassis->makeThingName("axleNode1"),
		Ogre::Vector3(0, -.45, -.95)
		) ;

	Ogre::Entity *pAxle1 = VrScene::singleton::get().getManager()->createEntity(p_chassis->makeThingName("axle1"), "buggybot-axle.mesh");
	pAxleNode1->attachObject(pAxle1);

	//Rear Axle
	Ogre::SceneNode *pAxleNode2 = NULL ;
	pAxleNode2 = p_sceneNode->createChildSceneNode(
		p_chassis->makeThingName("axleNode2"),
		Ogre::Vector3(0, -.45, .95)
		) ;

	Ogre::Entity *pAxle2 = VrScene::singleton::get().getManager()->createEntity(p_chassis->makeThingName("axle2"), "buggybot-axle.mesh");
	pAxleNode2->attachObject(pAxle2);

}
void BuggyChassisVu::createLight() {
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
}//end namespace MoonBuggy {