/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <buggybots/scenarios/mpscenario/MpScenario.h>
#include <buggybots/scenarios/mpscenario/MpHuman.h>
#include <buggybots/scenarios/mpscenario/MpDroid.h>
//
#include <buggybots/bots/character/Character.h>
#include <buggybots/bots/mapper/Mapper.h>

#include <buggybots/BbWorld.h>
#include <buggybots/BbBuilder.h>
#include <buggybots/BbSector.h>
#include <buggybots/BbTracer.h>

//
#define FIELD_WIDTH 100
#define HALF_FIELD_WIDTH (FIELD_WIDTH/2)
#define QUARTER_FIELD_WIDTH (FIELD_WIDTH/4)
#define FIELD_DEPTH 100
#define HALF_FIELD_DEPTH (FIELD_DEPTH/2)
#define QUARTER_FIELD_DEPTH (FIELD_DEPTH/4)


namespace MpScenario {
//////////////
typedef Character::Character BbCharacter ;
#define YPOS 1
bwVector3 MpPersonality::playerPosition[9] = {
    bwVector3(HALF_FIELD_WIDTH-8,YPOS,0),
    bwVector3(HALF_FIELD_WIDTH-10,YPOS,-10),
    bwVector3(HALF_FIELD_WIDTH-10,YPOS,10),
    bwVector3(HALF_FIELD_WIDTH-12,YPOS,-6),
    bwVector3(HALF_FIELD_WIDTH-12,YPOS,6),
    bwVector3(HALF_FIELD_WIDTH-14,YPOS, -16),
    bwVector3(HALF_FIELD_WIDTH-14,YPOS,0),
    bwVector3(HALF_FIELD_WIDTH-14,YPOS,16),
    bwVector3(HALF_FIELD_WIDTH-8,YPOS,0)
};
//
MpScenario::MpScenario(VrApplet* pApplet) : BbScenario(pApplet) {
	m_usesMap = true ;
	avatarInfo().setAvatarType(AVATAR_UFO) ;
	avatarInfo().setPos(bwPoint3(0,1,0)) ;
}
void MpScenario::createWorld() {
	p_world = new BbWorld(NULL) ;
	p_world->setOwner(this) ; //TODO:this looks stupid. construct with scenario as owner?
	p_world->setMinSize(bwSize3(125, 125, 125)) ;
	p_world->setSize(bwSize3(125, 125, 125)) ;
	p_world->create() ;
	//build the field	
	VrGroup* pField = p_world ;

	buildProps(p_world) ;
    // Build team A
    m_PlayerCountA = 1 ;
    for(unsigned int i=0; i < m_PlayerCountA ; ++i)
    {
		bwVector3 playerPos = MpPersonality::playerPosition[i] ;
		BbPilot* pPilot = new BbPilot() ;
		pPilot->setPosition(playerPos) ;
		pPilot->setPd(m_pd) ;
		pPilot->setCatId(CAT_PLAYER) ;
		p_wanderer = pPilot ;
        TeamA.push_back (pPilot);
        m_AllPlayers.push_back(pPilot);
		/////
		Character::Character *pPart = 
			static_cast<Character::Character*>(BbBuilder::singleton::get().getFactory("Ninja")->produce(pField)) ;

		pPart->setRelPos(playerPos) ;
		pPart->brain().setPilot(pPilot) ;
		pPilot->setModel(pPart) ;
		//
		MpHuman* pPersonality = new MpHuman(&pPart->brain(), TeamA, m_AllPlayers, m_TeamAGoal, m_TeamBGoal, true, i);
		pPart->brain().setPersonality(pPersonality) ;
		pPersonality->useTask("WANDERER") ;
		pPersonality->useTask("THINKER") ;
		//
		pPersonality->createTask("SEEKER") ;
		pPersonality->createTask("EVADER") ;
		//
		pPersonality->createTask("BOUNDER") ;
    }
    // Build Team B
    m_PlayerCountB = 8;
    for(unsigned int i=0; i < m_PlayerCountB ; ++i)
    {
		bwVector3 playerPos = bwVector3(-MpPersonality::playerPosition[i][0], MpPersonality::playerPosition[i][1], MpPersonality::playerPosition[i][2]) ;
		BbPilot* pPilot = new BbPilot() ;
		pPilot->setPosition(playerPos) ;
		pPilot->setPd(m_pd) ;
		pPilot->setCatId(CAT_PLAYER) ;
        TeamB.push_back (pPilot);
        m_AllPlayers.push_back(pPilot);
		/////
		Character::Character *pPart = 
			static_cast<Character::Character*>(BbBuilder::singleton::get().getFactory("Robot")->produce(pField)) ;

		pPart->setRelPos(playerPos) ;
		pPart->brain().setPilot(pPilot) ;
		pPilot->setModel(pPart) ;
		//
		MpDroid* pPersonality = new MpDroid(&pPart->brain(), p_wanderer, TeamA, m_AllPlayers, m_TeamAGoal, m_TeamBGoal, true, i);
		pPart->brain().setPersonality(pPersonality) ;
		pPart->brain().useTask("WANDERER") ;
		pPart->brain().useTask("THINKER") ;
		//
		pPersonality->createTask("PURSUER") ;
		//
		pPersonality->createTask("BOUNDER") ;
    }
    m_redScore = 0;
    m_blueScore = 0;
}

void MpScenario::buildProps(VrGroup *pGroup) {
	m_TeamAGoal = builder().build("Box", pGroup, PS_STATIC) ;
	m_TeamAGoal->setSize(4,4,4) ;
	m_TeamAGoal->setRelPos(-HALF_FIELD_WIDTH,1.1f,0) ;
	m_TeamAGoal->vuInfo().setMeshName("VrMetalBox.mesh") ;
	m_TeamAGoal->vuInfo().setMaterialName("VrMetalBox/mat_1_0") ;
	//
	m_TeamBGoal = builder().build("Box", pGroup, PS_STATIC) ;
	m_TeamBGoal->setSize(4,4,4) ;
	m_TeamBGoal->setRelPos(HALF_FIELD_WIDTH,1.1f,0) ;
	m_TeamBGoal->vuInfo().setMeshName("VrMetalBox.mesh") ;
	m_TeamBGoal->vuInfo().setMaterialName("VrMetalBox/mat_1_0") ;
	/////////////////////////////////////
	//Exterior
	//West Wall
	VrModel* pWall = builder().build("Box", pGroup, PS_STATIC) ;
	pWall->setSize(1,3,FIELD_DEPTH) ;
	pWall->setRelPos(-HALF_FIELD_WIDTH,1.1f,0) ;
	//East Wall
	pWall = builder().build("Box", pGroup, PS_STATIC) ;
	pWall->setSize(1,3,FIELD_DEPTH) ;
	pWall->setRelPos(HALF_FIELD_WIDTH,1.1f,0) ;
	//North Wall
	pWall = builder().build("Box", pGroup, PS_STATIC) ;
	pWall->setSize(FIELD_WIDTH,3,1) ;
	pWall->setRelPos(0,1.1f,-HALF_FIELD_DEPTH) ;
	//South Wall
	pWall = builder().build("Box", pGroup, PS_STATIC) ;
	pWall->setSize(FIELD_WIDTH,3,1) ;
	pWall->setRelPos(0,1.1f,HALF_FIELD_DEPTH) ;
	/////////////////////////////////////
	//Interior
	//West Wall
	pWall = builder().build("Box", pGroup, PS_STATIC) ;
	pWall->setSize(1,3,HALF_FIELD_DEPTH-10) ;
	pWall->setRelPos(-QUARTER_FIELD_WIDTH,1.1f,0) ;
	//East Wall
	pWall = builder().build("Box", pGroup, PS_STATIC) ;
	pWall->setSize(1,3,HALF_FIELD_DEPTH-10) ;
	pWall->setRelPos(QUARTER_FIELD_WIDTH,1.1f,0) ;
	//North Wall
	pWall = builder().build("Box", pGroup, PS_STATIC) ;
	pWall->setSize(HALF_FIELD_WIDTH-10,3,1) ;
	pWall->setRelPos(0,1.1f,-QUARTER_FIELD_DEPTH) ;
	//South Wall
	pWall = builder().build("Box", pGroup, PS_STATIC) ;
	pWall->setSize(HALF_FIELD_WIDTH-10,3,1) ;
	pWall->setRelPos(0,1.1f,QUARTER_FIELD_DEPTH) ;

}
void MpScenario::doPostEnable(bool sleeping) {
	BbScenario::doPostEnable(sleeping) ;
	Mapper* pMapper = new Mapper(p_world) ;
	pMapper->createEnabled() ;
	pMapper->setPos(bwPoint3(0,1.1f,0)) ;
	//
	BwStepper stepper ;
	pMapper->mapIt(stepper, pMapper->getPos()) ;
	getMap().sectorize(MCF_PATH, 128) ;
	getMap().portalize(MCF_PATH) ;
	getMap().edgize() ;
	//
	BbMapSectors& sectors = getMap().sectors() ;
	for(BbMapSectorsIter iter = sectors.begin() ; iter != sectors.end() ; ++iter) {
		BbMapSector& sector = **iter ;
		BbSector* pSector = new BbSector(getWorld()) ;
		pSector->setMapSector(&sector) ;
		pSector->create() ;
		bwSize3 size = getWorld()->getSize() ;
		pSector->setPos(sector.getPos()) ;
		pSector->setSize(sector.getSize()) ;
		pSector->config() ;
		pSector->enable() ;
		//
		VrModel* pEnergy = builder().build("Energy", getWorld(), PS_QUASISTATIC) ;
		//
		BbMarker* pMarker = new BbMarker() ;
		pMarker->setCatId(CAT_ITEM) ;
		pMarker->setPd(m_pd) ;
		pMarker->setModel(pEnergy) ;
		pEnergy->setTracer(BbDynamicTracer(pMarker)) ; //TODO:all seems round about ...
		//
		pEnergy->setPos(sector.getPos()) ;
		pEnergy->config() ;
		pEnergy->enable() ;
	}
}
} //namespace MpScenario