/*BuggyBots - A Botworx VR reference app and AI playground
Copyright (C) 2005  Kurtis Fields. See BuggyBots_License.txt for details.
*/
#include "stdafx.h"

#include <buggybots/BbParking.h>
#include <buggybots/BbBuilder.h>

BbParking::BbParking(VrGroup *pGroup) : VrPlace(pGroup){
}
BbParking::~BbParking(){
}
bool BbParking::onCreate(const BwPartInfo& info) {
	VrModel* pLevel = BbBuilder::singleton::get().getFactory("ParkingL1")->produce(this) ;
	pLevel->setRelPos(0, 9, -26.5) ;

	addRamps() ;

	return VrPlace::onCreate(info) ;
}
void BbParking::addRamps() {
	VrModel* pRamp = BbBuilder::singleton::get().getFactory("Ramp")->produce(this) ;
	//pRamp->setRelPos(0,-4.5,-3.5) ;
	pRamp->setRelPos(0,-1.0,-9.5) ;
}