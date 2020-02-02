/*BikeBots - A Botworx VR reference app and AI playground
Copyright (C) 2005  Kurtis Fields. See BikeBots_License.txt for details.
*/
#include "stdafx.h"

#include <buggybots/bots/bike/BikeBrain.h>
#include <buggybots/bots/bike/Bike.h>
#include <buggybots/bots/bike/BikeFactory.h>
#include <buggybots/bots/bike/BikeEngine.h>

#include <bwvr/VrSteering.h>

namespace Bike {
void BikeBrain::turnLeft() {
	if(!m_steeringTimer.checkAlarm()) {
		return ;
	}
	m_steeringTimer.resetAlarm() ;
	p_steering->turnLeft() ;
}
 
void BikeBrain::turnRight() {
		if(!m_steeringTimer.checkAlarm()) {
		return ;
	}
	m_steeringTimer.resetAlarm() ;
	p_steering->turnRight() ;
}
void BikeBrain::turnNone() {
	if(!m_steeringTimer.checkAlarm()) {
		return ;
	}
	m_steeringTimer.resetAlarm() ;
	bwReal angle = p_steering->getAngle() ;
	if(angle < -bwRealTraits::PiDiv90)
		p_steering->turnRight() ;
	else
	if(angle > bwRealTraits::PiDiv90)
		p_steering->turnLeft() ;
	else
		p_steering->turnNone() ;
}
}//end namespace BwVr::Bots::Bike 