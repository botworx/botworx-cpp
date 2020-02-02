/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <buggybots/BbScanner.h>

#include <bwvr/VrVu.h>
#include <bwvr/VrRayCollider.h>
#include <bwvr/VrContactListener.h>
#include <bwvr/VrBuilder.h>
#include <bwvr/VrPlace.h>
#include <bwvr/VrModelOps.h>
////////////
#include <bwvr/VrVu.h>
#include <bwvr/VrDynamicLines.h>
#include <bwvr/config/ogre.h>

using namespace Ogre ;
////////////
class BbScannerCollider : public VrRayCollider {
public:
	BbScannerCollider(BbScanner *pCollider) : VrRayCollider(pCollider) {
		p_collider = pCollider ;
	}
	virtual void processContact(VrCollisionRecord& record, VrSurfaceInfo& surfaceInfo, VrContact *contact) {
		return VrRayCollider::processContact(record, surfaceInfo, contact) ;
	}
	//this is the best place to do this.
	virtual int processCollision(VrCollisionRecord& record) {
		int n = 0 ;
		for(bwReal deg = -bwRealTraits::PiDiv2 ; deg < bwRealTraits::PiDiv2 ; deg += bwRealTraits::PiDiv8) {
			bwQuat rayQuat ;
			//set(rayQuat, bwAxisAngle(deg, bwVector3(0,1,0))) ;
            rayQuat = gmtl::make<bwQuat>(bwAxisAngle(deg, bwVector3(0,1,0))) ;
			bwPoint3 start = getStart(*p_collider) ;
			bwVector3 dir = (p_collider->getQuat() * rayQuat) * bwVector3(0,0,p_collider->getLength()) ;
			dGeomRaySet (p_collider->getGeomID(), start[0], start[1], start[2],
						dir[0], dir[1], dir[2]);
			//
			n += VrRayCollider::processCollision(record) ;
		}
		return n ;
	}
	//
	BbScanner *p_collider ;
};
//////////
class BbScannerVu : public VrVu {
public:
	BbScannerVu(BbScanner* pModel) : VrVu(pModel) {
		p_scanner = pModel ;
	}
	virtual void createAssets() ;
	virtual bool onPostStep(BwStepper& stepper) ;
	void drawLine(const bwPoint3& start, const bwPoint3& end) ;
	/*Data Members*/
public:
	BbScanner* p_scanner ;
	VrDynamicLines* p_lines ;
};
bool BbScannerVu::onPostStep(BwStepper& stepper) {
	p_lines->clear() ;
	//
	bwPoint3 scannerPos = p_scanner->getPos() ;
	bwSize3 contactSize = bwSize3(.1,.1,.1) ;

	VrContactList *contacts = p_scanner->getCollector()->getContacts() ;
	
	for(VrContactList::iterator iter = contacts->begin() ; iter != contacts->end() ; ++iter) {
		VrContact& contact = *iter ;
		drawLine(getStart(*p_scanner), contact.getPos()) ;
	}
	p_lines->update() ;
	return VrVu::onPostStep(stepper) ;
}
void BbScannerVu::createAssets() {
	createSceneNode() ;
    p_lines = new VrDynamicLines(RenderOperation::OT_LINE_LIST);	
    p_sceneNode->attachObject(p_lines);
}
void BbScannerVu::drawLine(const bwPoint3& start, const bwPoint3& end) {
	bwQuat invQuat = p_model->getQuat() ;
	invert(invQuat) ;
	bwPoint3 relStart = invQuat * bwVector3(start - p_model->getPos()) ;
	bwPoint3 relEnd = invQuat * bwVector3(end - p_model->getPos()) ;

	p_lines->addPoint(relStart[0], relStart[1], relStart[2]) ;
	p_lines->addPoint(relEnd[0], relEnd[1], relEnd[2]) ;
}
//////////
BbScanner::BbScanner(VrGroup *pGroup) : VrRay(pGroup) {
	setNodeType(NODE_BOX) ; //need to collide as a box first.
	setSize(6, .1f, 6) ;
	setIsAutoSleeper(false) ;
	setMotionType(MOTION_KINEMATIC) ;
	vuInfo().setIsAutoScaler(false) ;
}
bool BbScanner::onPostStep(BwStepper& stepper) {
	return VrRay::onPostStep(stepper) ;
}
void BbScanner::createCollider() {
	p_collector = new VrContactCollector() ;
	p_collider = new BbScannerCollider(this) ;
	p_collider->setListener(p_collector) ;
}
void BbScanner::createVu() {
	p_vu = new BbScannerVu(this) ;
	p_vu->create() ;
}