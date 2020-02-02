/*JrBots - A Botworx VR reference app and AI playground
Copyright (C) 2005  Kurtis Fields. See JrBots_License.txt for details.
*/
#include "stdafx.h"

#include <buggybots/bots/jr/JrFactory.h>
#include <buggybots/bots/jr/Jr.h>
#include <buggybots/bots/jr/JrBrain.h>
#include <buggybots/bots/jr/JrBody.h>
#include <buggybots/bots/jr/JrWheel.h>
#include <buggybots/bots/jr/JrEngine.h>
#include <buggybots/bots/jr/JrChassis.h>
//
#include <bwvr/VrPhysics.h>
#include <bwvr/VrSteering.h>
#include <bwvr/VrVu.h>
#include <bwvr/VrHinge2.h>
#include <bwvr/VrBody.h>
#include <bwvr/VrBall.h>
#include <bwvr/VrLay.h>

namespace Jr {

JrWheelMech::JrWheelMech(JrWheel *pWheel) : VrJointMech(pWheel) {
	p_wheel = pWheel ;
	p_engine = NULL ;
	m_power = 0 ;
	m_powerIncrement = .50 ;
	m_turnPower = 0 ;
	m_turnPowerIncrement = .25 ;
}
void JrWheelMech::doCreate(const BwPartInfo& info) {
	VrMech::doCreate(info) ;
	p_chassis = master().p_chassis ;

	p_engine = new JrEngine(this) ;
	p_engine->create() ;

	p_joint = VrPhysics::singleton::get().createJoint(JOINT_HINGE, p_wheel->getGroup()) ;
	p_joint->attachModels(p_chassis, p_wheel) ;

	p_rod_1 = p_joint->getRod1() ;

	setWheelPosition() ;
}
void JrWheelMech::doConfig() {
	VrMech::doConfig() ;
	p_engine->addGear(p_rod_1) ;
}
void JrWheelMech::doPostConfig() {
	JrWheelFactory& wheelFactory = p_wheel->factory() ; 

	p_rod_1->setAxis(1, 0, 0) ;

	p_joint->setJointERP(wheelFactory.m_wheelJointERP);
	p_joint->setJointCFM(wheelFactory.m_wheelJointCFM) ;

	VrMech::doPostConfig() ;
}
void JrWheelMech::doPostEnable(bool sleeping) {
	/*JrWheelFactory& wheelFactory = p_wheel->factory() ; 

	if(!sleeping) {
		p_rod_1->setAxis(1, 0, 0) ;

		p_joint->setJointERP(wheelFactory.m_wheelJointERP);
		p_joint->setJointCFM(wheelFactory.m_wheelJointCFM) ;
	}*/
	VrMech::doPostEnable(sleeping) ;
}
void JrWheelMech::setWheelPosition() {
	JrWheelFactory& wheelFactory = p_wheel->factory() ; 
	bwPoint3 point ;
	switch(p_wheel->getIndice()) {
		case 0 :
			point = bwPoint3(
					wheelFactory.m_followPos[0]/-2,
					wheelFactory.m_followPos[1],
					wheelFactory.m_followPos[2]/2) ;
			break ;
		case 1 :
			point = bwPoint3(
					wheelFactory.m_followPos[0]/2,
					wheelFactory.m_followPos[1],
					wheelFactory.m_followPos[2]/2) ;
			break ;
	}
	p_wheel->setLeader(static_cast<JrChassis*>(p_chassis)->getJrBody()) ;
	// VrFollowLay wheelLay ;
	// p_wheel->setLay(wheelLay) ;
	p_wheel->setLay(VrFollowLay()) ;
	p_wheel->setRelPos(point) ;

	getJoint()->setLeader(static_cast<JrChassis*>(p_chassis)->getJrBody()) ;
	// VrFollowLay jointLay ;
	// getJoint()->setLay(jointLay) ;
	getJoint()->setLay(VrFollowLay()) ;
	getJoint()->setRelPos(point) ;
}
void JrWheelMech::moveForward() {
	m_power += m_powerIncrement ;
	p_engine->setPower(m_power + m_turnPower) ;
}
void JrWheelMech::moveReverse() {
	m_power -= m_powerIncrement ;
	p_engine->setPower(m_power + -m_turnPower) ;
}
void JrWheelMech::moveNone() {
	if(m_power > 0)
		m_power -= m_powerIncrement ;
	else
		if(m_power < 0)
			m_power += m_powerIncrement ;
	//m_power = 0 ;
	p_engine->setPower(m_power + m_turnPower) ;
}
void JrWheelMech::turnLeft() {
	switch(p_wheel->getIndice()) {
		case Jr::WHEEL_RR :
			m_turnPower += m_turnPowerIncrement ;
			break ;
		case Jr::WHEEL_RL :
			m_turnPower = 0 ;
			break ;
	}
}
void JrWheelMech::turnRight() {
	switch(p_wheel->getIndice()) {
		case Jr::WHEEL_RR :
			m_turnPower = 0 ;
			break ;
		case Jr::WHEEL_RL :
			m_turnPower += m_turnPowerIncrement ;
			break ;
	}
}
void JrWheelMech::turnNone() {
	m_turnPower = 0 ;
}
/////////////////////
JrWheel::JrWheel(int indice, Jr *pJr) : VrBall(pJr) {
	p_jr = pJr ;
	m_indice = indice ;
	vuInfo().setMeshName("buggybot-wheel.mesh") ;
}
void JrWheel::doCreate(const BwPartInfo& info) {
	VrBall::doCreate(info) ;
	bodyInfo().setDensity(factory().m_wheelDensity) ;
	setRadius(factory().m_wheelRadius) ;
}
void JrWheel::createBrain() {
	VrModel::createBrain() ;
	/*p_brain = new JrWheelMech(this) ;
	p_brain->create() ;*/
}
}//end namespace BwVr::Bots::Jr 

