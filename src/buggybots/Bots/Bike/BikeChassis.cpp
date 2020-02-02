/*BikeBots - A Botworx VR reference app and AI playground
Copyright (C) 2005  Kurtis Fields. See BikeBots_License.txt for details.
*/
#include "stdafx.h"

#include <buggybots/bots/bike/Bike.h>
#include <buggybots/bots/bike/BikeChassis.h>
#include <buggybots/bots/bike/BikePrimary.h>

#include <bwvr/VrBox.h>

namespace Bike {

BikeChassis::BikeChassis(Bike *pBike) : VrFixedAssembly(pBike) {
	p_bike = pBike ;
	p_bikePrimary = NULL ;
}
void BikeChassis::doCreate(const BwPartInfo& info) {
	VrFixedAssembly::doCreate(info) ;
	p_bikePrimary = new BikePrimary(this, p_bike) ;
	p_bikePrimary->create() ;
	setMain(p_bikePrimary) ;
	VrBox *pBox = new VrBox(this) ;
	pBox->create() ;
	pBox->setSize(.7f,.7f,.7f) ;
	pBox->setRelPos(bwPoint3(0,0,-.5f)) ;
}

}//end namespace Bike