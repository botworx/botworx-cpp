/*BuggyBots - A Botworx VR reference app and AI playground
Copyright (C) 2005  Kurtis Fields. See BuggyBots_License.txt for details.
*/
#ifndef _BbBotFactories_H
#define _BbBotFactories_H


#include <buggybots/bots/moonbuggy/MoonBuggyFactory.h>
#include <buggybots/bots/bike/BikeFactory.h>
#include <buggybots/bots/crawler/CrawlerFactory.h>
#include <buggybots/bots/ufo/Ufo.h>
#include <buggybots/bots/jr/Jr.h>
#include <buggybots/bots/character/Character.h>
#include <buggybots/bots/bird/Bird.h>
//Pilots
#include <bwsteer/Proximity.h>
#include <buggybots/pilots/LowSpeedTurn.h>
#include <buggybots/pilots/OneTurning.h>
#include <buggybots/pilots/Boid.h>
#include <buggybots/pilots/Pedestrian.h>
#include <buggybots/pilots/MultiplePursuit.h>

#include <bwvr/VrScenario.h>
#include <bwvr/VrBody.h>
//
//BbBoidDemoFactory
//
class BbBoidDemoFactory : public VrModelFactory {
public:
	BbBoidDemoFactory(BwKit *pKit) : VrModelFactory(pKit) {
		setName("BoidDemo") ;
	}
	virtual VrModel* produce(VrGroup *pGroup, bwPartStyle style = PS_DEFAULT) {
		Bird *pPart = new Bird(pGroup) ;
		pPart->setFactory(this) ;
		pPart->create(style) ;
		Boid* pPilot = new Boid(pd) ;
		static_cast<BbPilotBrain*>(pPart->getBrain())->setPilot(pPilot) ;
		return pPart ;
	}
	//Data Members
	OpenSteer::BruteForceProximityDatabase<AbstractVehicle*> pd ;
} ;
//
//BbMpDemoFactory
//
class BbMpDemoFactory : public VrModelFactory {
public:
	BbMpDemoFactory(BwKit *pKit) : VrModelFactory(pKit) {
		setName("MultiplePursuerDemo") ;
		p_wanderer = NULL ;
	}
	virtual VrModel* produce(VrGroup *pGroup, bwPartStyle style = PS_DEFAULT) {
		Character::Character *pPart = new Character::Character(pGroup) ;
		pPart->setFactory(this) ;
		pPart->create(style) ;
		BbPilot* pPilot = NULL ;
		if(p_wanderer == NULL) 
			pPilot = p_wanderer = new MpWanderer() ;
		else
			pPilot = new MpPursuer(p_wanderer) ;
		pPart->brain().setPilot(pPilot) ;
		return pPart ;
	}
	//Data Members
	MpWanderer* p_wanderer ;
} ;
//
//BbPedestrianDemoFactory
//
class BbPedestrianDemoFactory : public VrModelFactory {
public:
	BbPedestrianDemoFactory(BwKit *pKit) : VrModelFactory(pKit) {
		setName("PedestrianDemo") ;
	}
	virtual VrModel* produce(VrGroup *pGroup, bwPartStyle style = PS_DEFAULT) {
		Character::Character *pPart = new Character::Character(pGroup) ;
		pPart->setFactory(this) ;
		pPart->create(style) ;
		Pedestrian* pPilot = new Pedestrian(pd) ;
		pPart->brain().setPilot(pPilot) ;
		return pPart ;
	}
	//
	OpenSteer::BruteForceProximityDatabase<AbstractVehicle*> pd ;
} ;
//
//BbOtDemoFactory
//
class BbOtDemoFactory : public VrModelFactory {
public:
	BbOtDemoFactory(BwKit *pKit) : VrModelFactory(pKit) {
		setName("OneTurningDemo") ;
	}
	virtual VrModel* produce(VrGroup *pGroup, bwPartStyle style = PS_DEFAULT) {
		Character::Character *pPart = new Character::Character(pGroup) ;
		pPart->setFactory(this) ;
		pPart->create(style) ;
		OneTurning* pPilot = new OneTurning() ;
		pPart->brain().setPilot(pPilot) ;
		return pPart ;
	}
} ;
//
//BbLstDemoFactory
//
class BbLstDemoFactory : public VrModelFactory {
public:
	BbLstDemoFactory(BwKit *pKit) : VrModelFactory(pKit) {
		setName("LowSpeedTurnDemo") ;
	}
	virtual VrModel* produce(VrGroup *pGroup, bwPartStyle style = PS_DEFAULT) {
		Character::Character *pPart = new Character::Character(pGroup) ;
		pPart->setFactory(this) ;
		pPart->create(style) ;
		LowSpeedTurn* pPilot = new LowSpeedTurn() ;
		pPart->brain().setPilot(pPilot) ;
		return pPart ;
	}
} ;
//
//BbBirdFactory
//
class BbBirdFactory : public VrModelFactory {
public:
	BbBirdFactory(BwKit *pKit) : VrModelFactory(pKit) {
		setName("Bird") ;
	}
	virtual VrModel* produce(VrGroup *pGroup, bwPartStyle style = PS_DEFAULT) {
		Bird *pBird = new Bird(pGroup) ;
		pBird->create(style) ;
		return pBird ;
	}
} ;
//
//BbRobotFactory
//
class BbRobotFactory : public Character::CharacterFactory {
public:
	BbRobotFactory(BwKit *pKit) ;
} ;
//
//BbRobotFactory
//
class BbNinjaFactory : public Character::CharacterFactory {
public:
	BbNinjaFactory(BwKit *pKit) ;
} ;
//
//BbFrankieFactory
//
class BbFrankieFactory : public Character::CharacterFactory {
public:
	BbFrankieFactory(BwKit *pKit) ;
} ;
//
//BbUfoFactory
//
class BbUfoFactory : public VrModelFactory {
public:
	BbUfoFactory(BwKit *pKit) : VrModelFactory(pKit) {
		setName("Ufo") ;
	}
	virtual VrModel* produce(VrGroup *pGroup, bwPartStyle style = PS_DEFAULT) {
		Ufo *pUfo = new Ufo(pGroup) ;
		pUfo->create(style) ;
		pUfo->setSize(1, 3, 3) ;
		return pUfo ;
	}
} ;

#endif //_BbBotFactories_H