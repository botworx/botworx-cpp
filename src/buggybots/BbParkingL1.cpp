/*BuggyBots - A Botworx VR reference app and AI playground
Copyright (C) 2005  Kurtis Fields. See BuggyBots_License.txt for details.
*/
#include "stdafx.h"

#include <buggybots/BbParkingL1.h>
#include <buggybots/BbBuilder.h>

BbParkingL1::BbParkingL1(VrGroup *pGroup) : VrPlace(pGroup){
}
BbParkingL1::~BbParkingL1(){
}
bool BbParkingL1::onCreate(const BwPartInfo& info) {
	addTiles() ;

	VrBuilderConfig config(BbBuilder::singleton::get().getFactory("Box"),
		bwSize3(20,5,0),
		bwSize3(.5, 0, 0)) ;
	VrModel* pBlocks = BbBuilder::singleton::get().buildWall(&config, this) ;
	pBlocks->setLay(VrOriginRelLay(bwPoint3(0, 1.01f, -45))) ;
	pBlocks->doze() ;
	return VrPlace::onCreate(info) ;
}
void BbParkingL1::addTiles() {
	VrModelFactory *pFactory = BbBuilder::singleton::get().getFactory("Tile") ;
	VrBuilderConfig config(pFactory, bwSize3(10, 0, 10), bwSize3(.1f, 0, .1f)) ;
	BbBuilder::singleton::get().buildGrid(&config, this) ;
}