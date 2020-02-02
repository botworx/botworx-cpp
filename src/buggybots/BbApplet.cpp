/*BuggyBots - A Botworx VR reference app and AI playground
Copyright (C) 2005  Kurtis Fields. See BuggyBots_License.txt for details.
*/
#include "stdafx.h"

#include <buggybots/BbApplet.h>
#include <buggybots/BbScenario.h>
#include <buggybots/BbScenarioFactories.h>
#include <bwvr/VrScenarioManager.h>
#include <buggybots/BbWorld.h>
#include <buggybots/BbScene.h>
#include <buggybots/BbBuilder.h>

BbApplet::BbApplet(void) {
	m_name = "BuggyBots" ;
	new BbBuilder(this) ; //registers itself as VrBuilder singleton...
	//
	VrScenarioFactory *pFactory = NULL ;
	VrScenarioManager& scenarioManager = VrScenarioManager::singleton::get() ;
	//
	pFactory = new BbSimpleScenarioFactory(this) ;
	pFactory->create() ;
	scenarioManager.addFactory(pFactory) ;
	//
	pFactory = new BbDefaultScenarioFactory(this) ;
	pFactory->create() ;
	scenarioManager.addFactory(pFactory) ;
	//
	pFactory = new BbTerrainScenarioFactory(this) ;
	pFactory->create() ;
	scenarioManager.addFactory(pFactory) ;
	//
	pFactory = new BbTestScenarioFactory(this) ;
	pFactory->create() ;
	scenarioManager.addFactory(pFactory) ;
	//
	/*pFactory = new BbTsmDemoFactory(this) ;
	pFactory->create() ;
	scenarioManager.addFactory(pFactory) ;*/
	//
	pFactory = new BbSoccerScenarioFactory(this) ;
	pFactory->create() ;
	scenarioManager.addFactory(pFactory) ;
	//
	pFactory = new MpScenarioFactory(this) ;
	pFactory->create() ;
	scenarioManager.addFactory(pFactory) ;
	//
	/*pFactory = new CtfScenarioFactory(this) ;
	pFactory->create() ;
	scenarioManager.addFactory(pFactory) ;*/
}

BbApplet::~BbApplet() {
}
void BbApplet::createScenario() {
	VrScenarioFactory* pScenarioFactory = VrScenarioManager::singleton::get().findFactory("SimpleScenario") ;
	loadScenario(pScenarioFactory) ;
}