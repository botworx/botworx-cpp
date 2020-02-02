/*BuggyBots - A Botworx VR reference app and AI playground
Copyright (C) 2005  Kurtis Fields. See BuggyBots_License.txt for details.
*/
#include "stdafx.h"

#include <buggybots/bots/crawler/Crawler.h>
#include <buggybots/bots/crawler/CrawlerBrain.h>
#include <buggybots/bots/crawler/CrawlerChassis.h>
#include <buggybots/bots/crawler/CrawlerLeg.h>
#include <buggybots/bots/crawler/CrawlerLegSeg.h>
#include <buggybots/bots/crawler/CrawlerLegMotor.h>
//
#include <bwvr/VrPhysics.h>
#include <bwvr/VrVu.h>
#include <bwvr/VrHinge2.h>
#include <bwvr/VrBody.h>
#include <bwvr/VrMech.h>
#include <bwvr/VrUniversal.h>
////////////////////////////////////////////////////
namespace Crawler {
//////////////////////////
CrawlerLegSegMech::CrawlerLegSegMech(CrawlerLegSeg *pSeg) : VrMotorizedJointMech(pSeg) {
	p_seg = pSeg ;
}
void CrawlerLegSegMech::doCreate(const BwPartInfo& info) {
	VrMech::doCreate(info) ;
	switch(p_seg->m_segIndice) {
		case 0 :
			p_joint = VrPhysics::singleton::get().createJoint(JOINT_UNIVERSAL, p_seg->getGroup()) ;
			break ;
		case 1 :
			p_joint = VrPhysics::singleton::get().createJoint(JOINT_HINGE, p_seg->getGroup()) ;
			break ;
		default :
			p_joint = NULL ;
	}
	p_rod_1 = p_joint->getRod1() ;
	p_rod_2 = p_joint->getRod2() ;
}
void CrawlerLegSegMech::setSegPosition() {
	CrawlerLegSegFactory& factory = p_seg->factory() ;
	//bwReal height = p_seg->p_leg->p_crawler->getChassis()->getHeight() ;
	bwReal height = p_seg->p_leg->p_crawler->getMain()->getHeight() ;
	bwPoint3 point ;
	bwPoint3 anchorPoint ;
	int segIndice = p_seg->m_segIndice ;
	switch(p_seg->getIndice()) {
		case 0 :
			point = bwPoint3(
					factory.m_followPos[segIndice][0]*-1,
					factory.m_followPos[segIndice][1],
					factory.m_followPos[segIndice][2]) ;
			anchorPoint = bwPoint3(.6f, 0, 0) ;
			break ;
		case 1 :
			point = bwPoint3(
					factory.m_followPos[segIndice][0],
					factory.m_followPos[segIndice][1],
					factory.m_followPos[segIndice][2]) ;
			anchorPoint = bwPoint3(-.6f, 0, 0) ;
			break ;
		case 2 :
			point = bwPoint3(
					factory.m_followPos[segIndice][0]*-1,
					factory.m_followPos[segIndice][1],
					factory.m_followPos[segIndice][2]*-1) ;
			anchorPoint = bwPoint3(.6f, 0, 0) ;
			break ;
		case 3 :
			point = bwPoint3(
					factory.m_followPos[segIndice][0],
					factory.m_followPos[segIndice][1],
					factory.m_followPos[segIndice][2]*-1) ;
			anchorPoint = bwPoint3(-.6f, 0, 0) ;
			break ;
	}

	// VrFollowLay segLay ;
	// p_seg->setLay(segLay) ;
	p_seg->setLay(VrFollowLay()) ;
	p_seg->setRelPos(point) ;

	getJoint()->setLeader(p_seg) ;
	// VrFollowLay jointLay ;
	// getJoint()->setLay(jointLay) ;
	getJoint()->setLay(VrFollowLay()) ;
	getJoint()->setRelPos(anchorPoint) ;
}
void CrawlerLegSegMech::doConfig() {
	VrMech::doConfig() ;

	setSegPosition() ;

	switch(p_seg->m_segIndice) {
		case 0 :
			p_mech_2 = new CrawlerLegMotorBrain(this) ;
			p_motor_2 = new CrawlerLegMotor(p_mech_2) ;
			p_motor_2->setRod(p_rod_2) ;
			p_mech_2->setMotor(p_motor_2) ;
			addSlave(p_mech_2) ;
			p_mech_2->create() ;
			p_mech_2->doConfig() ; //TODO:since it's being creating here ...
		case 1 :
			p_mech_1 = new CrawlerLegMotorBrain(this) ;
			p_motor_1 = new CrawlerLegMotor(p_mech_1) ;
			p_motor_1->setRod(p_rod_1) ;
			p_mech_1->setMotor(p_motor_1) ;
			addSlave(p_mech_1) ;
			p_mech_1->create() ;
			p_mech_1->doConfig() ; //TODO:since it's being creating here ...
			break ;
	}

	p_joint->attachModels(p_seg->getLeader(), p_seg) ;

	p_rod_1->setHasAngleLimits(true) ;
	if(p_rod_2 != NULL) {
		p_rod_2->setHasAngleLimits(true) ;
	}
}
void CrawlerLegSegMech::doPostEnable(bool sleeping) {
	CrawlerLegSegFactory& factory = p_seg->factory() ;

	int legIndice = p_seg->getIndice() ;

	switch(p_seg->m_segIndice) {
		case 0 :
			if(legIndice == 0 || legIndice == 2)
				p_rod_1->setAxis(0, 0, -1) ;
			else
				p_rod_1->setAxis(0, 0, 1) ;

			//p_rod_1->setLoStop(-(bwRealTraits::PiDiv2)) ;
			//p_rod_1->setHiStop(bwRealTraits::PiDiv2) ;
		if(legIndice == 0 || legIndice == 2)
				p_rod_2->setAxis(0, -1, 0) ;
			else
				p_rod_2->setAxis(0, 1, 0) ;
			//p_rod_2->setLoStop(-(bwRealTraits::PiDiv2)) ;
			//p_rod_2->setHiStop(bwRealTraits::PiDiv2) ;
			break ;
		case 1 :
			if(legIndice == 0 || legIndice == 2)
				p_rod_1->setAxis(0, 0, -1) ;
			else
				p_rod_1->setAxis(0, 0, 1) ;

			//p_rod_1->setLoStop(0) ;
			//p_rod_1->setHiStop(bwRealTraits::Pi) ;
			break ;
	}
	p_joint->setJointERP(factory.m_legJointERP);
	p_joint->setJointCFM(factory.m_legJointCFM) ;

	VrMech::doPostEnable() ;
}
//////////////////////////
CrawlerLegSeg::CrawlerLegSeg(CrawlerLeg *pLeg, int indice, int segIndice) : VrBox(pLeg) {
	p_leg = pLeg ;
	m_indice = indice ;
	m_segIndice = segIndice;
	vuInfo().setMeshName("VrBox.mesh") ;
}
void CrawlerLegSeg::doCreate(const BwPartInfo& info) {
	VrBox::doCreate(info) ;
	bodyInfo().setDensity(factory().m_legDensity) ;
	//setSize(factory().m_legRadius*2, factory().m_legRadius*2, factory().m_legLength) ;
	setSize(factory().m_legLength, factory().m_legRadius*2, factory().m_legRadius*2) ;
}
void CrawlerLegSeg::createBrain() {
	CrawlerLegSegMech *pMech = new CrawlerLegSegMech(this) ;
	pMech->create() ;
	p_brain = pMech ;
}
void CrawlerLegSeg::createGeom() {
	/*bwQuat quat ;
	set(quat, bwAxisAngle(bwRealTraits::PiDiv2, bwVector3(0,1,0))) ;
	setQuat(quat) ;*/

	VrBox::createGeom() ;
	/*dMatrix3 rotMat;
	dRFromAxisAndAngle(rotMat,0,1,0,bwRealTraits::PiDiv2);
	dBodySetRotation(p_body->getBodyID(), rotMat) ;*/

	/*dMatrix3 rotMat;
	dRFromAxisAndAngle(rotMat,1,0,0,-bwRealTraits::PiDiv2);
	dGeomSetRotation(m_geomID, rotMat) ;*/

}
void CrawlerLegSeg::attachTo(VrModel *pLeader) {
	setLeader(pLeader) ;
}
bool CrawlerLegSeg::onCreate(const BwPartInfo& info) {
	setLeader(NULL) ;
	
	return VrShape::onCreate(info) ;
}
//
CrawlerLegSegFactory::CrawlerLegSegFactory(BwPart* pOwner, BwKit* pKit) : BwFactory(pOwner, pKit) {
	m_segIndice = 0 ;
	//m_legDensity = .1 ;
	m_legDensity = VrBodyInfo::DENSITY_DEFAULT ;
	m_legRadius = 0.15f ;
	m_legLength = 1 ;
	m_legJointERP = 0.2f ;
	m_legJointCFM= 0.05f ;
}
CrawlerLegSeg* CrawlerLegSegFactory::createLegSeg(CrawlerLeg *pLeg, int indice) {
	CrawlerLegSeg* pSeg = new CrawlerLegSeg(pLeg, indice, m_segIndice) ;
	pSeg->setFactory(this) ;
	pSeg->create() ;
	return pSeg ;
}
//
CrawlerLegSeg1Factory::CrawlerLegSeg1Factory(BwKit *pKit) : CrawlerLegSegFactory(pKit) {
	m_segIndice = 0 ;
	m_followPos[m_segIndice] = bwPoint3(1.1f, 0, 1.2f) ;
}
//
CrawlerLegSeg2Factory::CrawlerLegSeg2Factory(BwKit *pKit) : CrawlerLegSegFactory(pKit) {
	m_segIndice = 1 ;
	m_followPos[m_segIndice] = bwPoint3(1.2f, 0, 0) ;
}

} //namespace Crawler

//TODO:?:weird ... can't be done within namespace ...???
using namespace Crawler ;
//Singleton support
template<> CrawlerLegSeg1Factory::singleton::pointer CrawlerLegSeg1Factory::singleton::g_singleton = 0 ;
//
CrawlerLegSeg1Factory* CrawlerLegSeg1Factory::singleton_alloc::alloc() { 
	CrawlerLegSeg1Factory* pPart = new CrawlerLegSeg1Factory(NULL) ;
	pPart->create() ;
	return pPart ;
}
//
template<> CrawlerLegSeg2Factory::singleton::pointer CrawlerLegSeg2Factory::singleton::g_singleton = 0 ;
//
CrawlerLegSeg2Factory* CrawlerLegSeg2Factory::singleton_alloc::alloc() { 
	CrawlerLegSeg2Factory* pPart = new CrawlerLegSeg2Factory(NULL) ;
	pPart->create() ;
	return pPart ;
}


