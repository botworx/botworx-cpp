/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <buggybots/BbEnergy.h>

#include <bwvr/VrCollider.h>

BbEnergy::BbEnergy(VrGroup *pGroup) : VrBall(pGroup) {
	setMotionType(MOTION_QUASISTATIC) ;
	setIsGhost(true) ;
	vuInfo().setMeshName("Energy.mesh") ;
}
///////////
VrModel* BbEnergyFactory::produce(VrGroup *pGroup, bwPartStyle style) {
	BbEnergy *pEnergy = new BbEnergy(pGroup) ;
	pEnergy->setFactory(this) ;
	pEnergy->setSize(.5, .5, .5) ;
	pEnergy->create(style) ;
	return pEnergy ; 
}
