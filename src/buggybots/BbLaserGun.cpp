/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <buggybots/BbLaserGun.h>
#include <buggybots/BbLaser.h>

#include <bwvr/VrPlace.h>
#include <bwvr/VrModelOps.h>

BbLaserGun::BbLaserGun(VrGroup *pGroup) : BbGun(pGroup) {
	p_laser = NULL ;
}
void BbLaserGun::onTrigger() {
	if(m_triggerState) {
		p_laser = new BbLaser(getPlace()) ;
		p_laser->setLength(20) ;
		setRay(*p_laser, getRelPoint(*this, bwVector3(0,0,1)), getQuat()) ;
		p_laser->createEnabled() ;
	}
	else {
		p_laser->die() ;
		p_laser = NULL ;
	}
}
void BbLaserGun::doStep(BwStepper& stepper) {
	VrShape::doStep(stepper) ;
	if(p_laser == NULL)
		return ;
	setRay(*p_laser, getRelPoint(*this, bwVector3(0,0,1)), getQuat()) ;
}