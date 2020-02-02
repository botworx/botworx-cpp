/*BikeBots - A Botworx VR reference app and AI playground
Copyright (C) 2005  Kurtis Fields. See BikeBots_License.txt for details.
*/
#include "stdafx.h"

#include <buggybots/bots/bike/BikeFactory.h>
#include <buggybots/bots/bike/Bike.h>
#include <buggybots/bots/bike/BikeBrain.h>
#include <buggybots/bots/bike/BikePrimary.h>
#include <buggybots/bots/bike/BikeWheel.h>
#include <buggybots/bots/bike/BikeEngine.h>
#include <buggybots/bots/bike/BikeChassis.h>

#include <bwvr/VrPhysics.h>
#include <bwvr/VrSteering.h>
#include <bwvr/VrVu.h>
#include <bwvr/VrHinge2.h>
#include <bwvr/VrBody.h>
#include <bwvr/VrBall.h>
#include <bwvr/VrLay.h>

namespace Bike {

BikeWheelMech::BikeWheelMech(BikeWheel *pWheel) : VrJointMech(pWheel) {
	p_wheel = pWheel ;
}
void BikeWheelMech::doCreate(const BwPartInfo& info) {
	VrMech::doCreate(info) ;
	p_chassis = master().p_chassis ;

	p_joint = VrPhysics::singleton::get().createJoint(JOINT_HINGE2, p_wheel->getGroup()) ;
	p_joint->attachModels(p_chassis, p_wheel) ;

	p_rod_1 = p_joint->getRod1() ;
	p_rod_2 = p_joint->getRod2() ;

	setWheelPosition() ;
}
void BikeWheelMech::doConfig() {
	VrMech::doConfig() ;

	switch(p_wheel->getIndice()) {
		case Bike::WHEEL_REAR :
			master().p_engine->addGear(p_rod_2) ;
			break ;
		case Bike::WHEEL_FRONT :
			master().p_steering->addGear(p_rod_1) ;
			break ;
	}

}
void BikeWheelMech::doEnable(bool sleeping) {
	BikeWheelFactory& wheelFactory = p_wheel->factory() ; 

	p_rod_1->setAngle(0) ;  //constrain angle

	VrMech::doEnable(sleeping) ;
}
void BikeWheelMech::doPostEnable(bool sleeping) {
	BikeWheelFactory& wheelFactory = p_wheel->factory() ; 

	p_rod_1->setHasAngleLimits(true) ;

	p_rod_1->setAngleMin(-(bwRealTraits::PiDiv8)) ;
	p_rod_1->setAngleMax(bwRealTraits::PiDiv8) ;

	p_rod_1->setAxis(0, 1, 0) ;
	//p_rod_2->setAxis(1, 0, 0) ;
	p_rod_2->setAxis(-1, 0, 0) ;

	p_joint->setJointERP(wheelFactory.m_wheelJointERP);
	p_joint->setJointCFM(wheelFactory.m_wheelJointCFM) ;
	VrMech::doPostEnable(sleeping) ;
}
void BikeWheelMech::setWheelPosition() {
	BikeWheelFactory& wheelFactory = p_wheel->factory() ; 
	bwPoint3 point ;
	switch(p_wheel->getIndice()) {
		case Bike::WHEEL_REAR :
			point = bwPoint3(
					wheelFactory.m_followPos[0]*.5f,
					wheelFactory.m_followPos[1],
					wheelFactory.m_followPos[2]*-.5f) ;
			break ;
		case Bike::WHEEL_FRONT :
			point = bwPoint3(
					wheelFactory.m_followPos[0]*.5f,
					wheelFactory.m_followPos[1],
					wheelFactory.m_followPos[2]*.5f) ;
			break ;
	}
	p_wheel->setLeader(static_cast<BikeChassis*>(p_chassis)->getBikePrimary()) ;
	// VrFollowLay wheelLay ;
	// p_wheel->setLay(wheelLay) ;
	p_wheel->setLay(VrFollowLay()) ;
	p_wheel->setRelPos(point) ;

	getJoint()->setLeader(static_cast<BikeChassis*>(p_chassis)->getBikePrimary()) ;
	//VrFollowLay jointLay ;
	//getJoint()->setLay(jointLay) ;
	getJoint()->setLay(VrFollowLay()) ;
	getJoint()->setRelPos(point) ;
}
/////////////////////
BikeWheel::BikeWheel(int indice, Bike *pBike) : VrBall(pBike) {
	p_bike = pBike ;
	m_indice = indice ;
	vuInfo().setMeshName("buggybot-wheel.mesh") ;
}
void BikeWheel::doCreate(const BwPartInfo& info) {
	VrBall::doCreate(info) ;
	bodyInfo().setDensity(factory().m_wheelDensity) ;
	setRadius(factory().m_wheelRadius) ;
}
void BikeWheel::createBrain() {
	VrModel::createBrain() ;
	/*p_brain = new BikeWheelMech(this) ;
	p_brain->create() ;*/
}
}//end namespace BwVr::Bots::Bike 
