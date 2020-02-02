/*BikeBots - A Botworx VR reference app and AI playground
Copyright (C) 2005  Kurtis Fields. See BikeBots_License.txt for details.
*/
#include "stdafx.h"

#include <buggybots/bots/bike/BikeFactory.h>
#include <buggybots/bots/bike/Bike.h>
#include <buggybots/bots/bike/BikeWheel.h>

#include <bwvr/VrBuilder.h>

namespace Bike {
BikeWheelFactory::BikeWheelFactory(BwKit *pKit) : VrModelFactory(pKit) {
	setName("Bike::Wheel") ;
	m_wheelRadius = 0.5f;
	//m_followPos[0] = 1.85f ;
	m_followPos[0] = 0 ;
	m_followPos[1] = -m_wheelRadius ;
	m_followPos[2] = 1.75f ;

	//m_wheelDensity = .1 ;
	m_wheelDensity = VrBodyInfo::DENSITY_DEFAULT ;
	m_wheelJointERP = 0.2f ;
	//m_wheelJointCFM = 0.8 ;
	m_wheelJointCFM = 0.05f ;
}
VrModel* BikeWheelFactory::rent(int indice, VrGroup *pGroup) {
	BikeWheel *pPart = new BikeWheel(indice, static_cast<Bike*>(pGroup)) ;
	pPart->setFactory(this) ;
	pPart->create() ;
	return pPart ;
}

BikeFactory::BikeFactory(BwKit *pKit) : VrModelFactory(pKit) {
	setName("Bike") ;
	//m_chassisDensity = .1 ;
	m_chassisDensity = VrBodyInfo::DENSITY_DEFAULT ;
	m_chassisPos[0] = 0 ;
	m_chassisPos[1] = 1 ;
	//m_chassisPos[1] = 2 ;
	m_chassisPos[2] = 0 ;
}

VrModel* BikeFactory::produce(VrGroup *pGroup, bwPartStyle style) {
	Bike *pPart = new Bike(pGroup) ;
	pPart->setFactory(this) ;
	pPart->create(style) ;
	return pPart ;
}
Bike* BikeFactory::rentBike(VrGroup *pGroup) {
	Bike *pPart = new Bike(pGroup) ;
	pPart->setFactory(this) ;
	pPart->create() ;
	return pPart ;
}

} //namespace Bike

//TODO:?:weird ... can't be done within namespace ...???
using namespace Bike ;
//Singleton support
template<> BikeWheelFactory::singleton::pointer BikeWheelFactory::singleton::g_singleton = 0 ;
//
BikeWheelFactory* BikeWheelFactory::singleton_alloc::alloc() { 
	BikeWheelFactory* pPart = new BikeWheelFactory(NULL) ;
	pPart->create() ;
	return pPart ;
}
//
//Singleton support
template<> BikeFactory::singleton::pointer BikeFactory::singleton::g_singleton = 0 ;
//
BikeFactory* BikeFactory::singleton_alloc::alloc() { 
	BikeFactory* pPart = new BikeFactory(NULL) ;
	pPart->create() ;
	return pPart ;
}

