/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <buggybots/BbScenario.h>
#include <buggybots/BbScene.h>
#include <buggybots/BbWorld.h>
#include <buggybots/BbTerrain.h>
#include <buggybots/BbMap.h>

#include <bwvr/VrPlane.h>
#include <bwvr/VrBuilder.h>
#include <bwvr/VrFixedAssembly.h>
#include <bwvr/VrSharedVu.h>

#include <bwvr/config/ogre.h>

BbScenario::BbScenario(VrApplet* pApplet) : VrScenario(pApplet) {
	m_worldSize = bwSize3(500,500,500) ;
	m_usesMap = false ;
	m_usesToys = false;
	m_usesObstacles = false;
	m_usesTiles = false;
	m_usesLevels = false;
	m_usesBalls = false;
	//
	setGroundType(GROUND_PLANE) ;
	setGroundMaterialName("BuggyBots/Ground") ;
	//
	setSkyType(SKY_DOME) ;
	setSkyMaterialName("BuggyBots/Sky") ;
	//
	avatarInfo().setAvatarType(AVATAR_UFO) ;
	//
	p_map = new BbMap() ;
}
BbScenario::~BbScenario() {
	delete p_map ;
}
/////////////////////////////////////////
void BbScenario::createWorld() {
	VrPlace* pWorld = new BbWorld(NULL) ;

	p_world = pWorld ;

	p_world->setOwner(this) ;

	p_world->setMinSize(m_worldSize) ;
	p_world->setSize(m_worldSize) ;

	p_world->create() ;
}
void BbScenario::createAvatar() {
	switch(avatarInfo().getAvatarType()) {
		case AVATAR_BUGGY :
			p_avatar = builder().build("Buggy", p_world) ;
			break ;
		case AVATAR_JR :
			p_avatar = builder().build("Jr", p_world) ;
			break ;
		case AVATAR_UFO :
			p_avatar = builder().build("Ufo", p_world) ;
			break ;
		case AVATAR_CRAWLER :
			p_avatar = builder().build("Crawler", p_world) ;
			break ;
	}
	p_avatar->setRelPos(avatarInfo().getPos());
	bwQuat quat ;
	set(quat, bwAxisAngle(bwRealTraits::Pi, bwVector3(0,1,0))) ;
	p_avatar->setRelQuat(quat) ;
}
void BbScenario::createGround() {
	VrModel* pMain = NULL ;
	switch(m_groundType) {
		case GROUND_PLANE :
			createPlane() ;
			break ;
		case GROUND_TERRAIN :
			createTerrain() ;
			break ;
	}
}
void BbScenario::createPlane() {
	VrModel* pModel = new VrPlane(p_world) ;
	pModel->setQuat(makePure(bwVector3(0,1,0))) ;
	pModel->vuInfo().setMaterialName(m_groundMaterialName) ;
	bwSize3 size(m_worldSize[0],20,m_worldSize[2]) ;
	pModel->setMinSize(size) ;
	pModel->setSize(size) ;
	pModel->create() ;
	p_world->setMain(pModel) ;
}
void BbScenario::createTerrain() {
	VrModel* pModel = new BbTerrain(p_world) ;
	bwSize3 size(m_worldSize[0],20,m_worldSize[2]) ;
	pModel->setMinSize(size) ;
	pModel->setSize(size) ;
	pModel->create() ;
	p_world->setMain(pModel) ;
}
void BbScenario::createProps() {
	if(m_usesToys) {
		buildToy1(p_world) ;
		buildToy2(p_world) ;
		buildToy3(p_world) ;
	}
	if(m_usesObstacles)
		addObstacles() ;
	if(m_usesTiles)
		addTiles() ;
	if(m_usesLevels)
		addLevels() ;
	if(m_usesBalls) {
		VrBuilderConfig config(builder().getFactory("Ball"),
			bwSize3(4, 4, 4),
			bwSize3(0, 0, 0)) ;
		VrModel* pMatrix = builder().buildMatrix(&config, p_world) ;

		pMatrix->setRelPos(-45, .5, 45);
		pMatrix->doze() ;
	}
}
void BbScenario::addLevels() {
	VrModel* pLevel = builder().getFactory("Parking")->produce(p_world) ;
	pLevel->setRelPos(0, 0, 100) ;
}
void BbScenario::addObstacles() {
	VrModel* pModel = builder().getFactory("Obstacles")->produce(p_world) ;
	pModel->setRelPos(125, 0, 125) ;
}
void BbScenario::addTiles() {
	VrModel* pTiles = builder().getFactory("Tiles")->produce(p_world) ;
	pTiles->setRelPos(0, -.75, 100) ;
}
void BbScenario::buildToy1(VrGroup *pGroup) {
	VrModel* pToy = builder().build("Toy1", pGroup) ;
	pToy->setRelPos(-45,1.1f,-20) ;
	pToy->doze() ;
}
void BbScenario::buildToy2(VrGroup *pGroup) {
	VrModel* pToy = builder().build("Toy2", pGroup) ;
	pToy->setRelPos(-45,2.25,0) ;
	pToy->doze() ;
}
void BbScenario::buildToy3(VrGroup *pGroup) {
	VrModel* pToy = builder().build("Toy3", pGroup) ;
	pToy->setRelPos(-45,1,75) ;
	pToy->doze() ;
}
void BbScenario::onLoad() {
	switchAvatar(getAvatar()) ; //
	//TODO:This runs out of memory on large worlds! Multiple smaller maps I guess.
	if(m_usesMap) {
		bwSize3 size = getWorld()->getSize() ;
		getMap().setSize(size) ;
	}
	//
	VrScenario::onLoad() ;
}
void BbScenario::createScene(void) {
	p_scene = new BbScene(this) ;
	p_scene->create() ;
}
void BbScenario::enableSky(bool val) {
	Ogre::SceneManager& manager = VrScene::singleton::get().manager() ;
	switch(m_skyType) {
		case SKY_DOME :
			manager.setSkyDome(val, getSkyMaterialName(), 4, 2);
	}
}