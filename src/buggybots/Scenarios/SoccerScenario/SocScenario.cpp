/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <buggybots/scenarios/soccerscenario/SocScenario_common.h>
#include <buggybots/scenarios/soccerscenario/SocScenario.h>
#include <buggybots/scenarios/soccerscenario/SocPlayer.h>

#include <buggybots/bots/character/Character.h>

#include <buggybots/BbTracer.h>
#include <buggybots/BbWorld.h>
#include <buggybots/BbBuilder.h>

#include <bwvr/VrBall.h>
#include <bwvr/VrPlane.h>
//
#include <sstream>
#include <iomanip>
#include <sstream>
//
//////////////
typedef Character::Character BbCharacter ;
//#define YPOS .5f
#define YPOS 1
//
#define FIELD_WIDTH 100
#define HALF_FIELD_WIDTH (FIELD_WIDTH/2)
#define QUARTER_FIELD_WIDTH (FIELD_WIDTH/4)
#define FIELD_DEPTH 50
#define HALF_FIELD_DEPTH (FIELD_DEPTH/2)
#define QUARTER_FIELD_DEPTH (FIELD_DEPTH/4)

//
namespace SoccerScenario {
bwVector3 SocPersonality::playerPosition[9] = {
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
BbSoccerScenario::BbSoccerScenario(VrApplet* pApplet) : BbScenario(pApplet) {
	avatarInfo().setAvatarType(AVATAR_UFO) ;
	avatarInfo().setPos(bwPoint3(0,1,0)) ;
	//
    m_PlayerCountA = 8;
    m_PlayerCountB = 8;
    m_redScore = 0;
    m_blueScore = 0;
}
void BbSoccerScenario::createWorld() {
	BbScenario::createWorld() ;
	//build the field
	//VrPlace* pField = new VrPlace(p_world) ;
	VrGroup* pField = new VrGroup(p_world) ;
	pField->create() ;
	pField->setRelPos(0,0,0) ;
	pField->setSize(FIELD_WIDTH, 3, FIELD_DEPTH) ;
	buildGoals(p_world) ;
	//
    // Make a ball
	VrBall* pBall = new VrBall(pField);
	pBall->vuInfo().setMeshName("BbSoccerBall.mesh") ;
	m_Ball = new BbMarker() ;
	m_Ball->setModel(pBall) ;
	pBall->setTracer(BbDynamicTracer(m_Ball)) ;
	pBall->create() ;
	pBall->setSize(.5,.5,.5) ;
	pBall->setRelPos(0,1,0) ;
    // Build team A
    for(unsigned int i=0; i < m_PlayerCountA ; ++i)
    {
		BbPilot* pPilot = new BbPilot() ;
		pPilot->setPd(m_pd) ;
        TeamA.push_back (pPilot);
        m_AllPlayers.push_back(pPilot);
		/////
		Character::Character *pPart = 
			static_cast<Character::Character*>(BbBuilder::singleton::get().getFactory("Robot")->produce(pField)) ;
		bwVector3 playerPos = SocPersonality::playerPosition[i] ;
		pPart->setRelPos(playerPos) ;
		pPart->brain().setPilot(pPilot) ;
		//
		SocPlayer* pPersonality = new SocPlayer(&pPart->brain(), TeamA, m_AllPlayers, m_Ball, m_TeamAGoal, m_TeamBGoal, true, i);
		pPersonality->setAvatar(pPart) ;
		//
		pPart->brain().setPersonality(pPersonality) ;
		pPart->brain().useTask("THINKER") ;
		pPart->brain().useTask("DYNAMICAVOIDER") ;
		pPart->brain().useTask("KICKER") ;
    }
    // Build Team B
    for(unsigned int i=0; i < m_PlayerCountB ; ++i)
    {
		BbPilot* pPilot = new BbPilot() ;
		pPilot->setPd(m_pd) ;
        TeamB.push_back (pPilot);
        m_AllPlayers.push_back(pPilot);
		/////
		Character::Character *pPart = 
			static_cast<Character::Character*>(BbBuilder::singleton::get().getFactory("Ninja")->produce(pField)) ;
		bwVector3 playerPos = bwVector3(-SocPersonality::playerPosition[i][0], SocPersonality::playerPosition[i][1], SocPersonality::playerPosition[i][2]);
		pPart->setRelPos(playerPos) ;
		pPart->brain().setPilot(pPilot) ;
		//
		SocPlayer* pPersonality = new SocPlayer(&pPart->brain(), TeamB, m_AllPlayers, m_Ball, m_TeamBGoal, m_TeamAGoal, false, i);
		pPersonality->setAvatar(pPart) ;
		//
		pPart->brain().setPersonality(pPersonality) ;
		pPart->brain().useTask("THINKER") ;
		pPart->brain().useTask("DYNAMICAVOIDER") ;
		pPart->brain().useTask("KICKER") ;
    }
}
void BbSoccerScenario::buildGoals(VrGroup *pGroup) {
	m_TeamAGoal = builder().build("Box", pGroup, PS_STATIC) ;
	m_TeamAGoal->setSize(4,4,4) ;
	m_TeamAGoal->setRelPos(HALF_FIELD_WIDTH-2,1.1f,0) ;
	m_TeamAGoal->vuInfo().setMeshName("VrMetalBox.mesh") ;
	m_TeamAGoal->vuInfo().setMaterialName("VrMetalBox/mat_1_0") ;
	//
	m_TeamBGoal = builder().build("Box", pGroup, PS_STATIC) ;
	m_TeamBGoal->setSize(4,4,4) ;
	m_TeamBGoal->setRelPos(-(HALF_FIELD_WIDTH-2),1.1f,0) ;
	m_TeamBGoal->vuInfo().setMeshName("VrMetalBox.mesh") ;
	m_TeamBGoal->vuInfo().setMaterialName("VrMetalBox/mat_1_0") ;
	//
	//Walls
	bwSize3 wallSizeNS = bwSize3(FIELD_WIDTH+4,4,4) ;
	//bwSize3 wallSizeWE = bwSize3(FIELD_WIDTH,3,2) ;
	bwSize3 wallSizeWE = bwSize3(4,4,FIELD_DEPTH+4) ;
	//West Wall
	VrModel* pWall = new VrPlane(pGroup) ;
	pWall->setSize(wallSizeWE) ;
	pWall->setRelPos(-HALF_FIELD_WIDTH,2,0) ;
	pWall->setQuat(makePure(bwVector3(1,0,0))) ;
	pWall->create() ;
	//East Wall
	pWall = new VrPlane(pGroup) ;
	pWall->setSize(wallSizeWE) ;
	pWall->setRelPos(HALF_FIELD_WIDTH,2,0) ;
	pWall->setQuat(makePure(bwVector3(-1,0,0))) ;
	pWall->create() ;
	//North Wall
	pWall = new VrPlane(pGroup) ;
	pWall->setSize(wallSizeNS) ;
	pWall->setRelPos(0,2,-HALF_FIELD_DEPTH) ;
	pWall->setQuat(makePure(bwVector3(0,0,1))) ;
	pWall->create() ;
	//South Wall
	pWall = new VrPlane(pGroup) ;
	pWall->setSize(wallSizeNS) ;
	pWall->setRelPos(0,2,HALF_FIELD_DEPTH) ;
	pWall->setQuat(makePure(bwVector3(0,0,-1))) ;
	pWall->create() ;

	/*VrModel* pWall = builder().build("Box", pGroup, PS_STATIC) ;
	pWall->setSize(1,3,FIELD_DEPTH) ;
	pWall->setRelPos(-HALF_FIELD_WIDTH,1.1f,0) ;
	//
	pWall = builder().build("Box", pGroup, PS_STATIC) ;
	pWall->setSize(1,3,FIELD_DEPTH) ;
	pWall->setRelPos(HALF_FIELD_WIDTH,1.1f,0) ;
	//
	pWall = builder().build("Box", pGroup, PS_STATIC) ;
	pWall->setSize(FIELD_WIDTH,3,1) ;
	pWall->setRelPos(0,1.1f,-HALF_FIELD_DEPTH) ;
	//
	pWall = builder().build("Box", pGroup, PS_STATIC) ;
	pWall->setSize(FIELD_WIDTH,3,1) ;
	pWall->setRelPos(0,1.1f,HALF_FIELD_DEPTH) ;*/
}

} //namespace SoccerScenario {