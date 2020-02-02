/*BuggyBots - A Botworx VR reference app and AI playground
Copyright (C) 2005  Kurtis Fields. See BuggyBots_License.txt for details.
*/
#include "stdafx.h"

#include <buggybots/bots/moonbuggy/MoonBuggyFactory.h>
#include <buggybots/bots/moonbuggy/MoonBuggy.h>
#include <buggybots/bots/moonbuggy/MoonBuggyBrain.h>
#include <buggybots/bots/moonbuggy/MoonBuggyBody.h>
#include <buggybots/bots/moonbuggy/MoonBuggyWheel.h>
#include <buggybots/bots/moonbuggy/MoonBuggyEngine.h>
#include <buggybots/bots/moonbuggy/MoonBuggyChassis.h>

#include <bwvr/VrPhysics.h>
#include <bwvr/VrSteering.h>
#include <bwvr/VrVu.h>
#include <bwvr/VrHinge2.h>
#include <bwvr/VrBody.h>
#include <bwvr/VrLay.h>

namespace MoonBuggy {

BuggyWheelMech::BuggyWheelMech(BuggyWheel *pWheel) : VrJointMech(pWheel) {
	p_wheel = pWheel ;
}
void BuggyWheelMech::doCreate(const BwPartInfo& info) {
	VrMech::doCreate(info) ;
	p_chassis = master().p_chassis ;
	p_joint = VrPhysics::singleton::get().createJoint(JOINT_HINGE2, p_wheel->getGroup()) ;
	p_joint->attachModels(p_chassis, p_wheel) ;

	p_rod_1 = p_joint->getRod1() ;
	p_rod_2 = p_joint->getRod2() ;

	setWheelPosition() ;
}
void BuggyWheelMech::doConfig() {
	VrMech::doConfig() ;

	master().p_engine->addGear(p_rod_2) ;
	switch(p_wheel->getIndice()) {
		case Buggy::WHEEL_RL :
		case Buggy::WHEEL_RR :
			break ;
		case Buggy::WHEEL_FL :
		case Buggy::WHEEL_FR :
			master().p_steering->addGear(p_rod_1) ;
			break ;
	}
}
void BuggyWheelMech::doEnable(bool sleeping) {
	BuggyWheelFactory& wheelFactory = p_wheel->factory() ; 

	p_rod_1->setAngle(0) ;  //constrain angle

	VrMech::doEnable(sleeping) ;
}
void BuggyWheelMech::doPostEnable(bool sleeping) {
	BuggyWheelFactory& wheelFactory = p_wheel->factory() ; 

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
void BuggyWheelMech::setWheelPosition() {
	BuggyWheelFactory& wheelFactory = p_wheel->factory() ; 
	bwPoint3 point ;
	switch(p_wheel->getIndice()) {
		case 0 :
			point = bwPoint3(
					wheelFactory.m_followPos[0]*-.5f,
					wheelFactory.m_followPos[1],
					wheelFactory.m_followPos[2]*-.5f) ;
			break ;
		case 1 :
			point = bwPoint3(
					wheelFactory.m_followPos[0]*.5f,
					wheelFactory.m_followPos[1],
					wheelFactory.m_followPos[2]*-.5f) ;
			break ;
		case 2 :
			point = bwPoint3(
					wheelFactory.m_followPos[0]*-.5f,
					wheelFactory.m_followPos[1],
					wheelFactory.m_followPos[2]*.5f) ;
			break ;
		case 3 :
			point = bwPoint3(
					wheelFactory.m_followPos[0]*.5f,
					wheelFactory.m_followPos[1],
					wheelFactory.m_followPos[2]*.5f) ;
			break ;
	}
	p_wheel->setLeader(static_cast<BuggyChassis*>(p_chassis)->getBuggyBody()) ;
	// VrFollowLay wheelLay ;
	// p_wheel->setLay(wheelLay) ;
	p_wheel->setLay(VrFollowLay()) ;
	p_wheel->setRelPos(point) ;

	getJoint()->setLeader(static_cast<BuggyChassis*>(p_chassis)->getBuggyBody()) ;
	// VrFollowLay jointLay ;
	// getJoint()->setLay(jointLay) ;
	getJoint()->setLay(VrFollowLay()) ;
	getJoint()->setRelPos(point) ;
}
/////////////////////
BuggyWheel::BuggyWheel(int indice, Buggy *pBuggy) : VrBall(pBuggy) {
//BuggyWheel::BuggyWheel(int indice, Buggy *pBuggy) : VrCylinder(pBuggy) {
	p_buggy = pBuggy ;
	m_indice = indice ;
	vuInfo().setMeshName("buggybot-wheel.mesh") ;
	//
	/*setUpAxis(VrModel::AXIS_X) ;
	setSize(.25, 1, 1) ;
	setTestInternal(false) ;*/
}
void BuggyWheel::doCreate(const BwPartInfo& info) {
	VrBall::doCreate(info) ;
	//VrCylinder::doCreate() ;
	bodyInfo().setDensity(factory().m_wheelDensity) ;
	setRadius(factory().m_wheelRadius) ;
}
}//end namespace BwVr::Bots::MoonBuggy 

