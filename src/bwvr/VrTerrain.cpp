/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <bwvr/VrTerrain.h>
#include <bwvr/VrTerrainQuad.h>
#include <bwvr/VrLayout.h>
#include <bwvr/VrShape.h>
#include <bwvr/VrVu.h>

VrTerrain::VrTerrain(VrGroup *pGroup) 
	: VrQuadTree(pGroup) {
}
void VrTerrain::createQuadFactory() {
	p_quadFactory = new VrQuadFactory(sizeof(VrQuad)) ; 
}
VrQuad* VrTerrain::createQuad(VrGroup *pGroup, int index, int level) {
	VrQuad *pQuad = new (p_quadFactory->rentQuad()) VrTerrainQuad(pGroup, this, index, level) ;
	pQuad->setFactory(p_quadFactory) ;
	pQuad->create() ;
	return pQuad ;
}

