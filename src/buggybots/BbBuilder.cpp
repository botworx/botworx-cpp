/*BuggyBots - A Botworx VR reference app and AI playground
Copyright (C) 2005  Kurtis Fields. See BuggyBots_License.txt for details.
*/
#include "stdafx.h"

#include <buggybots/BbBuilder.h>
#include <buggybots/BbMissile.h>
#include <buggybots/BbTile.h>
#include <buggybots/BbGem.h>
#include <buggybots/BbEnergy.h>
#include <buggybots/BbParkingL1.h>
#include <buggybots/BbParking.h>
#include <buggybots/BbBunny.h>
//
#include <buggybots/BbBotFactories.h>
#include <buggybots/BbPropFactories.h>
#include <buggybots/BbShapeFactories.h>
#include <buggybots/BbToyFactories.h>
//
#include <bwcore/BwFactory.h>
#include <bwvr/VrScenario.h>
#include <bwvr/VrSystem.h>

BbBuilder::BbBuilder(BwPart *pPart) : VrBuilder(pPart) {
	//Shape Factories
	createFactory(new BbBallFactory(this)) ;
	createFactory(new BbBoxFactory(this)) ;
	createFactory(new BbTetraFactory(this)) ;
	createFactory(new BbHexaFactory(this)) ;
	createFactory(new BbCylinderFactory(this)) ;
	createFactory(new BbCapsuleFactory(this)) ;
	createFactory(new BbConeFactory(this)) ;
	createFactory(new BbTorusFactory(this)) ;
	createFactory(new BbBunnyFactory(this)) ;
	createFactory(new BbSuzanneFactory(this)) ;

	//Prop Factories
	createFactory(new BbObstaclesFactory(this)) ;
	createFactory(new BbTileFactory(this)) ;
	createFactory(new BbParkingFactory(this)) ;
	createFactory(new BbParkingL1Factory(this)) ;
	createFactory(new BbTilesFactory(this)) ;
	createFactory(new BbSidewalkFactory(this)) ;
	createFactory(new BbRampFactory(this)) ;
	createFactory(new BbGemFactory(this)) ;
	createFactory(new BbEnergyFactory(this)) ;
	createFactory(new BbDuneFactory(this)) ;

	//Toy Factories
	createFactory(new BbToy1Factory(this)) ;
	createFactory(new BbToy2Factory(this)) ;
	createFactory(new BbToy3Factory(this)) ;
	createFactory(new BbToy4Factory(this)) ;
	createFactory(new BbToy5Factory(this)) ;

	//Bot Factories
	addFactory(MoonBuggy::BuggyFactory::singleton::getPtr()) ;
	addFactory(Bike::BikeFactory::singleton::getPtr()) ;
	addFactory(Crawler::CrawlerFactory::singleton::getPtr()) ;
	addFactory(Jr::JrFactory::singleton::getPtr()) ;
	createFactory(new BbUfoFactory(this)) ;

	createFactory(new BbMpDemoFactory(this)) ;
	createFactory(new BbPedestrianDemoFactory(this)) ;
	createFactory(new BbBoidDemoFactory(this)) ;
	createFactory(new BbOtDemoFactory(this)) ;
	createFactory(new BbLstDemoFactory(this)) ;
	createFactory(new BbBirdFactory(this)) ;
	createFactory(new BbRobotFactory(this)) ;
	createFactory(new BbNinjaFactory(this)) ;
	createFactory(new BbFrankieFactory(this)) ;
}