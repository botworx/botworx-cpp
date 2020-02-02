/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <buggybots/bots/character/CharacterBody.h>
#include <buggybots/bots/character/CharacterVu.h>

#include <bwvr/VrVu.h>
#include <bwvr/VrBody.h>

namespace Character {

CharacterBody::CharacterBody(VrGroup *pGroup) : VrBox(pGroup) {
	m_isAutoSleeper = false ;
	_setSize(bwSize3(1, 2, .5)) ;
	m_isViewable = false ;
}
void CharacterBody::createBody() {
	VrBox::createBody() ;
	p_body->setRotMode(bwmath::ROTMODE_FIXED) ;
}
} //namespace Character
