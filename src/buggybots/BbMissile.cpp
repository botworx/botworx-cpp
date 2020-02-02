/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <buggybots/BbMissile.h>
#include <buggybots/BbExplosion.h>

#include <bwvr/VrShapeCollider.h>
#include <bwvr/VrBody.h>
#include <bwvr/VrPhysics.h>
#include <bwvr/VrContact.h>

///
#include <bwvr/VrVu.h>
#include <bwvr/VrScene.h>
#include <bwvr/config/ogre.h>

class BbMissile ;

class BbMissileVu : public VrVu {
public:
	BbMissileVu(BbMissile *pMissile) : VrVu (pMissile) {
		p_missile = pMissile ;
		m_vuInfo.m_meshName = "BbMissile.mesh" ;
	}
	virtual void doPostDisable(bool sleeping) {
		if(!sleeping) {
			p_sceneNode->detachAllObjects() ;
			VrScene::singleton::get().getManager()->destroyParticleSystem(p_particleSys) ;
		}
		VrVu::doPostDisable(sleeping) ;
	}
	virtual ~BbMissileVu() {
	}
	virtual void createSceneNode() {
		VrVu::createSceneNode() ;
		p_particleSys = VrScene::singleton::get().getManager()->createParticleSystem
					(p_missile->makeThingName("emitter"), "BuggyBots/MissileFlame") ;

		p_sceneNode->attachObject(p_particleSys) ;
	}
	//Data Members
public:
	BbMissile *p_missile ;
private:
	Ogre::ParticleSystem* p_particleSys ;
};

///

class BbMissileCollider : public VrShapeCollider {
public:
	BbMissileCollider(BbMissile *pCollider) : VrShapeCollider(pCollider) {
		p_collider = pCollider ;
	}
	virtual void processContact(VrCollisionRecord& record, VrSurfaceInfo& surfaceInfo, VrContact *contact) {
		VrShapeCollider::processContact(record, surfaceInfo, contact) ;
		p_collider->m_impactPos = contact->getPos() ;
	}
	virtual bool canCollide(VrNode* pCollider, VrNode* pCollidee) { return false ; }
	//
	BbMissile *p_collider ;
};

const bwReal BbMissile::diameter = .15f ;

BbMissile::BbMissile(VrGroup *pGroup) : VrBall(pGroup) {
	setSize(diameter, diameter, diameter) ;
	setIsAutoSleeper(false) ;
	bodyInfo().setDrag(0) ;
	m_lifeTimer.setAlarm(std::chrono::seconds(10)) ;
}
BbMissile::~BbMissile() {
}
void BbMissile::createEnabled(BbMissileConfig *pConfig) {
	setLay(VrAbsLay(pConfig->m_pos)) ;
	create() ;
	setQuat(pConfig->m_quat) ;
	config() ;
	p_body->setGravityMode(0) ;
	p_body->setLinearVel(pConfig->m_linearVel) ;
	enable() ;
}
void BbMissile::createCollider() {
	p_collider = new BbMissileCollider(this) ;
}
void BbMissile::createVu() {
	p_vu = new BbMissileVu(this) ;
	p_vu->create() ;
}
void BbMissile::doStep(BwStepper& stepper) {
	VrShape::doStep(stepper) ;
	p_body->addRelForce(bwVector3(0, 0, .1)) ;
}
bool BbMissile::onPostStep(BwStepper& stepper) {
	if(p_collider->isContacting() == true) {
		BbExplosion *pBang = new BbExplosion(getGroup()) ;
		pBang->setPower(10) ;
		pBang->setLay(VrAbsLay(m_impactPos)) ;
		pBang->setSize(diameter, diameter, diameter) ;
		//pBang->setMaxWidth(4) ;
		pBang->createEnabled() ;
		die() ;
	}
	if(m_lifeTimer.checkAlarm())
		die() ;
	return VrShape::onPostStep(stepper) ;
}