/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <buggybots/bots/character/CharacterBrain.h>
#include <buggybots/bots/character/Character.h>
#include <buggybots/bots/character/CharacterBody.h>
#include <buggybots/bots/character/CharacterPoser.h>

#include <buggybots/BbScanner.h>
#include <buggybots/BbPilot.h>

#include <bwvr/VrModelOps.h>
#include <bwvr/VrContactListener.h>

namespace Character {

CharacterBrain::CharacterBrain(Character *pCharacter) : BbPilotBrain(pCharacter) {
	p_animat = pCharacter ;
}
void CharacterBrain::doConfig() {
	p_poser = new CharacterPoser(p_animat->getChassis()) ;
	p_scanner = p_animat->getScanner() ;
}
bool CharacterBrain::onPostStep(BwStepper& stepper) {
	if(p_scanner == NULL) return BbPilotBrain::onPostStep(stepper) ;
	if(getPilot() == NULL) return BbPilotBrain::onPostStep(stepper) ;
	//else
	pilot().clearParticles() ; //TODO:wasteful?
	VrContactList *contacts = p_scanner->getCollector()->getContacts() ;
	
	for(VrContactList::iterator iter = contacts->begin() ; iter != contacts->end() ; ++iter) {
		VrContact& contact = *iter ;
		if(contact.getCollidee()->getMotionType() == MOTION_STATIC)
			pilot().addParticle(contact.getPos(), contact.getNormal()) ;
	}
	setRay(*p_scanner, getRelPoint(*p_model, bwVector3(0,0,.5f)), p_model->getQuat()) ;

	return BbPilotBrain::onPostStep(stepper) ;
}
void CharacterBrain::jump() {
	p_poser->jump() ;
}
void CharacterBrain::jumpNone() {
	p_poser->jumpNone() ;
}
void CharacterBrain::turnLeft() {
	p_poser->turnLeft(bwRealTraits::PiDiv180) ;
}
void CharacterBrain::turnRight() {
	p_poser->turnRight(bwRealTraits::PiDiv180) ;
}
void CharacterBrain::turnNone() {
}
void CharacterBrain::moveForward() {
	p_poser->moveForward(.1f) ;
}
void CharacterBrain::moveReverse() {
	p_poser->moveReverse(.1f) ;
}
void CharacterBrain::moveNone() {
	p_poser->moveNone() ;
}
void CharacterBrain::pitchUp() {
	p_poser->pitchUp(bwRealTraits::PiDiv180) ;
}
void CharacterBrain::pitchDown() {
	p_poser->pitchDown(bwRealTraits::PiDiv180) ;
}
void CharacterBrain::rollLeft() {
	p_poser->rollLeft(bwRealTraits::PiDiv180) ;
}
void CharacterBrain::rollRight() {
	p_poser->rollRight(bwRealTraits::PiDiv180) ;
}

} //namespace Character {
