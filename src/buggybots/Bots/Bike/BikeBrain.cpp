/*BikeBots - A Botworx VR reference app and AI playground
Copyright (C) 2005  Kurtis Fields. See BikeBots_License.txt for details.
*/
#include "stdafx.h"

#include <buggybots/bots/bike/BikeBrain.h>
#include <buggybots/bots/bike/Bike.h>
#include <buggybots/bots/bike/BikeFactory.h>
#include <buggybots/bots/bike/BikeWheel.h>
#include <buggybots/bots/bike/BikeChassis.h>
#include <buggybots/bots/bike/BikePrimary.h>
#include <buggybots/bots/bike/BikeEngine.h>

#include <bwvr/VrSteering.h>

namespace Bike {
BikeBrain::BikeBrain(Bike *pBike) : 
		m_firingTimer(std::chrono::seconds(1)),
		m_drivingTimer(std::chrono::milliseconds(16)),
		m_steeringTimer(std::chrono::milliseconds(16)),
		VrBrain(pBike) {
	p_bike = pBike ;
	p_bikeFactory = BikeFactory::singleton::getPtr() ;
	p_wheelFactory = BikeWheelFactory::singleton::getPtr() ;
	p_engine = NULL ;
	p_steering = NULL ;
	m_powerIncrement = .50 ;
}
void BikeBrain::doCreate(const BwPartInfo& info) {
	BwBrain::doCreate(info) ;

	p_chassis = static_cast<BikeChassis*>(p_bike->getChassis()) ;
	p_primary = static_cast<BikePrimary*>(p_bike->getPrimary()) ;
	p_engine = new BikeEngine(this) ;
	p_engine->create() ;
	p_steering = new VrSteering(this) ;
	p_steering->create() ;

	BikeWheelMech *pMech ;
	for(int i = 0 ; i < Bike::WHEEL_TTL ; ++i) {
		pMech = new BikeWheelMech(p_bike->getWheelAt(i)) ;
		addSlave(pMech) ;
		pMech->create() ;
	}
	BikePrimaryMech *pMainMech = new BikePrimaryMech(p_primary) ;
	addSlave(pMainMech) ;
	pMainMech->create() ;
}
void BikeBrain::fireMissile() {
 	if(m_firingTimer.checkAlarm()) {
		p_bike->fireMissile() ;
		m_firingTimer.resetAlarm() ;
	}
}
void BikeBrain::fireLaser() {
 	if(m_firingTimer.checkAlarm()) {
		p_bike->fireLaser() ;
		m_firingTimer.resetAlarm() ;
	}
}
void BikeBrain::rollLeft() {
	p_bike->rollLeft(bwRealTraits::PiDiv180) ;
}
void BikeBrain::rollRight() {
	p_bike->rollRight(bwRealTraits::PiDiv180) ;
}

} //end namespace BwVr::Bots::Bike 