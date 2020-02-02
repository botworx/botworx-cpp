/*BikeBots - A Botworx VR reference app and AI playground
Copyright (C) 2005  Kurtis Fields. See BikeBots_License.txt for details.
*/
#include "stdafx.h"

#include <buggybots/bots/bike/BikeFactory.h>
#include <buggybots/bots/bike/Bike.h>
#include <buggybots/bots/bike/BikeEngine.h>

namespace Bike {
BikeEngine::BikeEngine(VrMech *pMech) : VrMotor(pMech, NULL, 1) {
}
void BikeEngine::setPower(bwReal power) {
	m_power = power ;
	if(m_power > 0) {
		setVelocity(m_power) ;
		setForceMax(m_power*.1) ;
	}
	else {
		setVelocity(m_power) ;
		setForceMax(-m_power*.1) ;
	}
}
}//end namespace Bike {
