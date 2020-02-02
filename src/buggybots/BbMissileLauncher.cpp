/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <buggybots/BbMissileLauncher.h>
#include <buggybots/BbMissile.h>

#include <bwvr/VrPlace.h>
#include <bwvr/VrModelOps.h>
#include <bwvr/VrBody.h>

BbMissileLauncher::BbMissileLauncher(VrGroup *pGroup) : BbGun(pGroup) {
	m_inst_counter = 0 ;
}
void BbMissileLauncher::onTrigger() {
	BbMissileConfig config ;	

	config.m_quat = getQuat() ;

	config.m_pos = getRelPoint(*this, bwVector3(0, 0, 1)) ;

	config.m_linearVel = p_body->getLinearVel() ;

	BbMissile *pMissile = new BbMissile(getPlace());
	pMissile->setIndice(m_inst_counter++) ;
	pMissile->createEnabled(&config) ;
}