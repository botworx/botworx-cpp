/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <buggybots/bots/character/Character.h>
#include <buggybots/bots/character/CharacterVu.h>
#include <buggybots/bots/character/CharacterBrain.h>
#include <buggybots/bots/character/CharacterBody.h>

#include <buggybots/BbScanner.h>
#include <buggybots/BbProjection.h>

#include <bwvr/VrVu.h>
#include <bwvr/VrBody.h>
#include <bwvr/VrPlace.h>

namespace Character {
//
//CharacterFactory
//
CharacterFactory::CharacterFactory(BwKit *pKit) : VrModelFactory(pKit) {
	setName("Character") ;
	m_vuInfo.setMeshName("robot.mesh") ;
}
VrModel* CharacterFactory::produce(VrGroup *pGroup, bwPartStyle style) {
	Character *pPart = new Character(pGroup) ;
	pPart->setFactory(this) ;
	pPart->create(style) ;
	return pPart ;
}
//
//Character
//
Character::Character(VrGroup *pGroup) : VrDynamicAssembly(pGroup) {
	m_isEntity = true ;
	m_isAutoSleeper = false ;
	setTestInternal(false) ;
	//m_usesScanner = false ;
	m_usesScanner = true ;
	p_scanner = NULL ;
	//
	m_isViewable = true ;
}
void Character::doCreate(const BwPartInfo& info) {
	VrDynamicAssembly::doCreate(info) ;
	//TODO:need macro or something for casting!
	CharacterFactory& factory = static_cast<CharacterFactory&>(*getFactory()) ;
	setVuInfo(factory.m_vuInfo) ;

	p_chassis = new CharacterBody(this) ;
	p_chassis->create() ;
	setMain(p_chassis) ;
	//
	if(m_usesScanner) {
		p_scanner = new BbScanner(getPlace()) ;
		p_scanner->create() ;
	}
}
void Character::createBrain() {
	p_brain = new CharacterBrain(this) ;
	p_brain->create() ;
}
void Character::createVu() {
	p_vu = new CharacterVu(this) ;
	p_vu->create() ;
}

} //namespace Character {