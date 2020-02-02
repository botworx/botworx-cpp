/*BuggyBots - A Botworx VR reference app and AI playground
Copyright (C) 2005  Kurtis Fields. See BuggyBots_License.txt for details.
*/
#include "stdafx.h"

#include <buggybots/bots/moonbuggy/MoonBuggyFactory.h>
#include <buggybots/bots/moonbuggy/MoonBuggy.h>
#include <buggybots/bots/moonbuggy/MoonBuggyWheel.h>

namespace MoonBuggy {

BuggyWheelFactory::BuggyWheelFactory(BwKit *pKit) : VrModelFactory(pKit) {
	setName("BuggyWheel") ;
	m_wheelRadius = 0.5f;
	m_followPos[0] = 1.85f ;
	m_followPos[1] = -m_wheelRadius ;
	//m_followPos[1] = - (m_wheelRadius + .5f) ;
	//m_followPos[2] = 1.75f ;
	m_followPos[2] = 2.0f ;

	//m_wheelDensity = .1 ;
	m_wheelDensity = VrBodyInfo::DENSITY_DEFAULT ;
	m_wheelJointERP = 0.2f ;
	//m_wheelJointCFM = 0.8 ;
	m_wheelJointCFM = 0.05f ;
}
VrModel* BuggyWheelFactory::rent(int indice, VrGroup *pGroup) {
	BuggyWheel *pPart = new BuggyWheel(indice, static_cast<Buggy*>(pGroup)) ;
	pPart->setFactory(this) ;
	pPart->create() ;
	return pPart ;
}
BuggyFactory::BuggyFactory(BwKit *pKit) : VrModelFactory(pKit) {
	setName("Buggy") ;
	m_chassisDensity = VrBodyInfo::DENSITY_DEFAULT ;
	m_chassisPos[0] = 0 ;
	m_chassisPos[1] = 1 ;
	m_chassisPos[2] = 0 ;
}

VrModel* BuggyFactory::produce(VrGroup *pGroup, bwPartStyle style) {
	Buggy *pPart = new Buggy(pGroup) ;
	pPart->setFactory(this) ;
	pPart->create(style) ;
	return pPart ;
}
Buggy* BuggyFactory::rentBuggy(VrGroup *pGroup) {
	Buggy *pPart = new Buggy(pGroup) ;
	pPart->setFactory(this) ;
	pPart->create() ;
	return pPart ;
}

} //namespace MoonBuggy

//TODO:?:weird ... can't be done within namespace ...???
using namespace MoonBuggy ;
//Singleton support
template<> BuggyFactory::singleton::pointer BuggyFactory::singleton::g_singleton = 0 ;
//
BuggyFactory* BuggyFactory::singleton_alloc::alloc() { 
	BuggyFactory* pPart = new BuggyFactory(NULL) ;
	pPart->create() ;
	return pPart ;
}

//Singleton support
template<> BuggyWheelFactory::singleton::pointer BuggyWheelFactory::singleton::g_singleton = 0 ;
//
BuggyWheelFactory* BuggyWheelFactory::singleton_alloc::alloc() { 
	BuggyWheelFactory* pPart = new BuggyWheelFactory(NULL) ;
	pPart->create() ;
	return pPart ;
}
