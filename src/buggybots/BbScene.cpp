/*BuggyBots - A Botworx VR reference app and AI playground
Copyright (C) 2005  Kurtis Fields. See BuggyBots_License.txt for details.
*/
#include "stdafx.h"

#include <buggybots/BbScene.h>

#include <bwvr/VrApplet.h>
#include <bwvr/VrScenario.h>
#include <bwvr/VrPhysics.h>

#include <bwvr/config/ogre.h>

BbScene::BbScene(VrScenario *pScenario) : VrScene(pScenario){
	m_displayUpdateTimer.setAlarm(std::chrono::seconds(1)) ;
}
BbScene::~BbScene(){
}
void BbScene::doStep(BwStepper& stepper) {
	VrScene::doStep(stepper) ;
	if(m_displayUpdateTimer.checkAlarm()) {
		m_displayUpdateTimer.resetAlarm() ;

		char buffer[64] ;
		sprintf(buffer, "%f", static_cast<float>(stepper.getDeltaTime())) ;
		/*Ogre::OverlayElement* thisTextArea;
		thisTextArea = Ogre::OverlayManager::getSingleton().getOverlayElement("BuggyBots/StepSize");
		thisTextArea->setCaption(buffer);*/
	}
}
void BbScene::createUser() {
	p_user = VrApplet::singleton::get().produceUser(this) ;
}
void BbScene::doCreate(const BwPartInfo& info) {
	VrScene::doCreate(info) ;
	//Animation
	Ogre::Animation::setDefaultInterpolationMode(Ogre::Animation::IM_LINEAR);
    Ogre::Animation::setDefaultRotationInterpolationMode(Ogre::Animation::RIM_LINEAR);
	//Ambient Lighting
	p_sceneManager->setAmbientLight(Ogre::ColourValue(1, 1, 1));
	//Fog
	Ogre::ColourValue fogColour(0.5, 0.5, 0.5);
	p_sceneManager->setFog(Ogre::FOG_LINEAR, fogColour, 0.02, 50, 500);
	//Overlay
	/*p_overlay = static_cast<Ogre::Overlay*>
		(Ogre::OverlayManager::getSingleton().getByName("BuggyBots/Overlay"));
	p_overlay->show();*/
}