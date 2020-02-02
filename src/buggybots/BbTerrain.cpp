/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <buggybots/BbTerrain.h>
#include <buggybots/BbTerrainQuad.h>

#include <bwvr/VrVu.h>
#include <bwvr/VrConcaveMesh.h>
#include <bwvr/VrRandomQuadMap.h>
#include <bwvr/VrGrayscaleQuadMap.h>
#include <bwvr/VrOgreMeshBuilder.h>
#include <bwvr/config/ogre.h>

BbTerrain::BbTerrain(VrGroup *pGroup) 
	: VrTerrain(pGroup) {
}
bool BbTerrain::onCreate(const BwPartInfo& info) {
	VrGrayscaleQuadMap map ;
	map.loadImage("bb-terrain.png") ;
	map.setScale(10) ;
	map.setPixelVertexRatio(4) ;
	map.alter(this) ;

	generateMesh(m_levelCount) ;
	//
	VrOmTriMesh *pMesh = getMesh() ;
	VrOgreMeshBuilder builder("BbTerrain_mesh") ;
	builder.setMaterialName("BuggyBots/Ground") ;
	builder.build(pMesh) ;
	//
	p_main = new VrConcaveMesh(this) ;
	p_main->setMinSize(m_minSize) ; //TODO:why isn't it being sized correctly?
	p_main->setMotionType(MOTION_STATIC) ;
	p_main->setIsViewable(true) ;
	p_main->vuInfo().setMeshName("BbTerrain_mesh") ;
	p_main->create() ;
	return VrTerrain::onCreate(info) ;
}
void BbTerrain::createQuadFactory() {
	p_quadFactory = new VrQuadFactory(sizeof(BbTerrainQuad)) ; 
}
VrQuad* BbTerrain::createQuad(VrGroup *pGroup, int index, int level) {
	VrQuad *pQuad = new (p_quadFactory->rentQuad()) BbTerrainQuad(pGroup, this, index, level) ;
	pQuad->setFactory(p_quadFactory) ;
	pQuad->create() ;
	return pQuad ;
}

