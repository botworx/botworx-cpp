/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <buggybots/bots/character/CharacterPoser.h>

#include <bwvr/VrVu.h>
#include <bwvr/VrBody.h>
#include <bwvr/VrModelOps.h>
#include <bwvr/VrPhysics.h>
//
using namespace bwmath ;

namespace Character {

CharacterPoser::CharacterPoser(VrModel* pModel) : VrPoser(pModel) {
}
void CharacterPoser::applyLinearForce() {
	VrBody *pBody = p_model->getBody() ;
	bwPoint3 bodyPos = pBody->getPos() ;
	bwReal linPower = pBody->bodyInfo().getMass() * 1000 ;
	bwVector3 linForce = getPos() - bodyPos  ;
	if(linForce != bwVector3()) {
		pBody->addForce(linForce * linPower) ;
	}
}
void CharacterPoser::applyAngularForce() {
	VrBody *pBody = p_model->getBody() ;
	if(pBody->getRotMode() == bwmath::ROTMODE_FIXED)
		return ;
	pBody->bodyInfo().setAngularDrag(-100) ;
	//
	//
	bwReal angPower = pBody->bodyInfo().getMass() * 1000 ;
	//else
	bwEuler e1 = getEuler() ;
	bwEuler e2 = ::getEuler(*p_model) ;
	bwVector3 angForce ;
	/////////////////////////////////////
	//falling forward
	e1[2] = e1[2] + bwRealTraits::Pi ;
	e2[2] = e2[2] + bwRealTraits::Pi ;
	
	if(e2[2] < e1[2]) {
		bwReal yawDelta1 = e1[2] - e2[2] ;
		bwReal yawDelta2 = (bwRealTraits::Pi2 - e1[2]) + e2[2] ;
		if(yawDelta1 < yawDelta2)
			angForce[0] = yawDelta1 ;
		else
			angForce[0] = -yawDelta2 ;
	}
	//falling backward
	else if(e2[2] > e1[2]) {
		bwReal yawDelta1 = e2[2] - e1[2] ;
		bwReal yawDelta2 = (bwRealTraits::Pi2 - e2[2]) + e1[2] ;
		if(yawDelta1 < yawDelta2)
			angForce[0] = -yawDelta1 ;
		else
			angForce[0] = yawDelta2 ;
	}
	//////////////////////////////
	//
	//spinning left
	e1[0] = e1[0] + bwRealTraits::Pi ;
	e2[0] = e2[0] + bwRealTraits::Pi ;
	
	if(e2[0] < e1[0]) {
		bwReal yawDelta1 = e1[0] - e2[0] ;
		bwReal yawDelta2 = (bwRealTraits::Pi2 - e1[0]) + e2[0] ;
		if(yawDelta1 < yawDelta2)
			angForce[1] = yawDelta1 ;
		else
			angForce[1] = -yawDelta2 ;
	}
	//spinning right
	else if(e2[0] > e1[0]) {
		bwReal yawDelta1 = e2[0] - e1[0] ;
		bwReal yawDelta2 = (bwRealTraits::Pi2 - e2[0]) + e1[0] ;
		if(yawDelta1 < yawDelta2)
			angForce[1] = -yawDelta1 ;
		else
			angForce[1] = yawDelta2 ;
	}

	//falling left
	e1[1] = e1[1] + bwRealTraits::Pi ;
	e2[1] = e2[1] + bwRealTraits::Pi ;
	
	if(e2[1] < e1[1]) {
		bwReal yawDelta1 = e1[1] - e2[1] ;
		bwReal yawDelta2 = (bwRealTraits::Pi2 - e1[1]) + e2[1] ;
		if(yawDelta1 < yawDelta2)
			angForce[2] = yawDelta1 ;
		else
			angForce[2] = -yawDelta2 ;
	}
	//spinning right
	else if(e2[1] > e1[1]) {
		bwReal yawDelta1 = e2[1] - e1[1] ;
		bwReal yawDelta2 = (bwRealTraits::Pi2 - e2[1]) + e1[1] ;
		if(yawDelta1 < yawDelta2)
			angForce[2] = -yawDelta1 ;
		else
			angForce[2] = yawDelta2 ;
	}
	pBody->addRelTorque(angForce * angPower) ;
}
bool CharacterPoser::onStep(BwStepper& stepper) {
	applyLinearForce() ;
	applyAngularForce() ;

	return VrPoser::onStep(stepper) ;
}

bool CharacterPoser::onPostStep(BwStepper& stepper) {
	setPos(p_model->getPos()) ;
	VrBody *pBody = p_model->getBody() ;
	if(pBody->getRotMode() == bwmath::ROTMODE_FIXED) {
		pBody->setAngularVel(bwVector3()) ;
		pBody->setQuat(getQuat()) ;
	}
	return VrPoser::onPostStep(stepper) ;
}

} //namespace Character
