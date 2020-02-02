/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <buggybots/BbExplosion.h>
#include <bwvr/VrVu.h>
#include <bwvr/VrShapeCollider.h>
#include <bwvr/VrBody.h>
#include <bwvr/VrOdeCollision.h>
#include <bwvr/VrContact.h>
#include <bwvr/VrPhysics.h>
#include <bwvr/VrNode.h>
#include <bwvr/VrModelOps.h>

class BbExplosionCollider : public VrShapeCollider {
public:
	BbExplosionCollider(BbExplosion *pExplosion) : VrShapeCollider(pExplosion) {
		p_explosion = pExplosion ;
	}
	virtual bool canCollide(VrNode* pCollider, VrNode* pCollidee) { return false ; } //no one collides with us
	virtual void addCollisionPair(VrNode* pCollider, VrNode* pCollidee) {
		if(pCollidee->getCollider()->getModel()->hasBody())
			VrShapeCollider::addCollisionPair(pCollider, pCollidee) ;
	}
	virtual void processContact(VrCollisionRecord& record, VrSurfaceInfo& surfaceInfo, VrContact *contact) ;
	//
	BbExplosion *p_explosion ;
};

BbExplosion::BbExplosion(VrGroup *pGroup) : VrBall(pGroup) {
	setMotionType(MOTION_KINEMATIC) ;
	setIsAutoSleeper(false) ;
	m_power = 1 ;
	setMaxSize(bwSize3(5,5,5)) ;
	this->setSize(.1f, .1f, .1f) ;
	vuInfo().setMeshName("BbExplosion.mesh") ;
}
void BbExplosion::createCollider() {
	p_collider = new BbExplosionCollider(this) ;
}
void BbExplosion::doStep(BwStepper& stepper) {
	bwDT deltaTime = VrPhysics::singleton::get().getDeltaTime() ;
	expand(10 * deltaTime) ;
	//TODO:anomaly?  must change size before calling parent doStep
	VrShape::doStep(stepper) ;
}
bool BbExplosion::onPostStep(BwStepper& stepper) {
	if(m_size[0] > m_maxSize[0])
		die() ;
	bwReal radius = getRadius() ;
	dGeomSphereSetRadius(m_geomID, radius ) ;
	p_vu->setScale(m_size) ;
	return VrShape::onPostStep(stepper) ; ;
}
void BbExplosion::setParticleVel(bwParticle& particle, const bwVector3& velocity) {
	bwVector3 vector ;

	vector = velocity * ( (m_power * static_cast<bwReal>(50)) / gmtl::Math::sqr(getRadius())) ;

	particle.setDir(vector) ;
	return ;
}

/*****************************/
void BbExplosionCollider::processContact(VrCollisionRecord& record, VrSurfaceInfo& surfaceInfo, VrContact *contact) {
	VrShape *pShape = static_cast<VrShape*>(record.p_collidee->getModel()) ;
	bwParticle particle ;
	bwPoint3 point ;
	bwVector3 normal ;

	point = contact->getPos() ;

	normal = contact->getNormal() ;

	particle.setOrigin(point) ;

	bwVector3 unit = getUnitVector(*p_explosion, point) ;
	p_explosion->setParticleVel(particle, unit - normal) ;
	bwVector3 force = particle.getDir() ;

	pShape->getBody()->addForceAtPos(force, point) ;

}