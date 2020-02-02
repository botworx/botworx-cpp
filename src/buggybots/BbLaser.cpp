/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <buggybots/BbLaser.h>
#include <buggybots/BbExplosion.h>

#include <bwvr/VrVu.h>
#include <bwvr/VrContactListener.h>
#include <bwvr/VrModelOps.h>
//
BbLaser::BbLaser(VrGroup *pGroup) : VrRay(pGroup) {
	setNodeType(NODE_LINESEG) ;
	setSize(.1f, .1f, .1f) ;
	m_isAutoSleeper = false ;
	setMotionType(MOTION_KINEMATIC) ;
	vuInfo().setMeshName("BbLaser.mesh") ;
}
bool BbLaser::onPostStep(BwStepper& stepper) {
	if(!p_collector->empty()) {
		bwPoint3 contactPoint = p_collector->getClosest(getStart(*this))->getPos() ;
		BbExplosion *pBang = new BbExplosion(getGroup()) ;
		pBang->setLay(VrAbsLay(contactPoint)) ;
		pBang->setSize(.1f, .1f, .1f) ;
		pBang->setMaxSize(bwSize3(1,1,1)) ;
		pBang->createEnabled() ;

		p_collector->clear() ;
	}
	return VrShape::onPostStep(stepper) ;
}