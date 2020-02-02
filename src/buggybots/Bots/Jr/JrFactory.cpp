/*JrBots - A Botworx VR reference app and AI playground
Copyright (C) 2005  Kurtis Fields. See JrBots_License.txt for details.
*/
#include "stdafx.h"

#include <buggybots/bots/jr/JrFactory.h>
#include <buggybots/bots/jr/Jr.h>
#include <buggybots/bots/jr/JrWheel.h>

namespace Jr {
JrWheelFactory::JrWheelFactory(BwKit *pKit) : VrModelFactory(pKit) {
	setName("Jr::Wheel") ;
	m_wheelRadius = 0.5f;
	m_followPos[0] = 1.85f ;
	m_followPos[1] = -m_wheelRadius ;
	m_followPos[2] = 0 ;

	//m_wheelDensity = .1 ;
	m_wheelDensity = VrBodyInfo::DENSITY_DEFAULT ;
	m_wheelJointERP = 0.2f ;
	m_wheelJointCFM = 0.05f ;
}
VrModel* JrWheelFactory::rent(int indice, VrGroup *pGroup) {
	JrWheel *pPart = new JrWheel(indice, static_cast<Jr*>(pGroup)) ;
	pPart->setFactory(this) ;
	pPart->create() ;
	return pPart ;
}

JrFactory::JrFactory(BwKit *pKit) : VrModelFactory(pKit) {
	setName("Jr") ;
	//m_chassisDensity = .1 ;
	m_chassisDensity = VrBodyInfo::DENSITY_DEFAULT ;
	m_chassisPos[0] = 0 ;
	m_chassisPos[1] = 0 ;
	m_chassisPos[2] = 0 ;
}

VrModel* JrFactory::produce(VrGroup *pGroup, bwPartStyle style) {
	Jr *pPart = new Jr(pGroup) ;
	pPart->setFactory(this) ;
	pPart->create(style) ;
	return pPart ;
}

}//end namespace Jr {

//TODO:?:weird ... can't be done within namespace ...???
using namespace Jr ;
//Singleton support
template<> JrWheelFactory::singleton::pointer JrWheelFactory::singleton::g_singleton = 0 ;
//
JrWheelFactory* JrWheelFactory::singleton_alloc::alloc() { 
	JrWheelFactory* pPart = new JrWheelFactory(NULL) ;
	pPart->create() ;
	return pPart ;
}
//
//Singleton support
template<> JrFactory::singleton::pointer JrFactory::singleton::g_singleton = 0 ;
//
JrFactory* JrFactory::singleton_alloc::alloc() { 
	JrFactory* pPart = new JrFactory(NULL) ;
	pPart->create() ;
	return pPart ;
}
