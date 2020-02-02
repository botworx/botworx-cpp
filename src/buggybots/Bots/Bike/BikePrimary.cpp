/*BikeBots - A Botworx VR reference app and AI playground
Copyright (C) 2005  Kurtis Fields. See BikeBots_License.txt for details.
*/
#include "stdafx.h"

#include <buggybots/bots/bike/BikeFactory.h>
#include <buggybots/bots/bike/Bike.h>
#include <buggybots/bots/bike/BikeBrain.h>
#include <buggybots/bots/bike/BikePrimary.h>
#include <buggybots/bots/bike/BikePrimaryVu.h>
#include <buggybots/bots/bike/BikePrimary.h>
#include <buggybots/bots/bike/BikeChassis.h>
//
#include <bwmath/BwMath.h>
#include <bwvr/VrBody.h>
#include <bwvr/VrSteering.h>

using namespace bwmath ;

namespace Bike {
	BikePrimaryMech::BikePrimaryMech(BikePrimary *pPrimary) : VrMech(pPrimary) {
	p_primary = pPrimary ;
}
void BikePrimaryMech::doCreate(const BwPartInfo& info) {
	VrMech::doCreate(info) ;
	p_chassis = master().p_chassis ;
}
void BikePrimaryMech::doConfig() {
	VrMech::doConfig() ;
}
void BikePrimaryMech::doEnable(bool sleeping) {
	VrMech::doEnable(sleeping) ;
}
void BikePrimaryMech::doPostEnable(bool sleeping) {
	VrMech::doPostEnable(sleeping) ;
}
void BikePrimaryMech::doStep(BwStepper& stepper) {
	VrMech::doStep(stepper) ;
	VrBody *pBody = primary().getBody() ;
	bwReal speed = fabs(mag(pBody->getLinearVel())) ;
	bwReal angPower = pBody->bodyInfo().getMass() * speed * 10 ;

	bwQuat quat = makePure(bwVector3(0,1,0)) ;
	bwReal angle = master().getSteering()->getAngle() ;
	bwQuat rotQuat ;
	set(rotQuat, bwAxisAngle(angle,0,0,1)) ;
	quat = quat * rotQuat ;
	bwEuler e1 = makeEulerFromQuaternion(quat) ;
	bwQuat q2 = primary().getQuat() ;
	bwEuler e2 = makeEulerFromQuaternion(q2) ;

	bwVector3 angForce ;
	//falling left	
	if(e2[1] < e1[1]) {
		bwReal yawDelta1 = e1[1] - e2[1] ;
		bwReal yawDelta2 = (bwRealTraits::Pi2 - e1[1]) + e2[1] ;
		if(yawDelta1 < yawDelta2)
			angForce[2] = yawDelta1 ;
		else
			angForce[2] = -yawDelta2 ;
	}
	//falling right
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
/////////////////////
BikePrimary::BikePrimary(VrGroup *pGroup, Bike *pBike) : VrCapsule(pGroup) {
	p_buggy = pBike ;
	_setSize(bwSize3(.5,1,2)) ;
	vuInfo().setMeshName("buggybot-body.mesh") ;
	vuInfo().setMeshSize(bwSize3(1,1,2)) ;
}
void BikePrimary::doCreate(const BwPartInfo& info) {
	VrShape::doCreate(info) ;
	bodyInfo().setDensity(p_buggy->factory().m_chassisDensity) ;
}
void BikePrimary::createVu() {
	p_vu = new BikePrimaryVu(this) ;
	p_vu->create() ;
}
void BikePrimary::createGeom() {
	VrCapsule::createGeom() ;
}
}//end namespace Bike {
