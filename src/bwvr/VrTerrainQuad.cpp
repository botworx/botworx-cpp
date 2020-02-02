/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <bwvr/VrTerrain.h>
#include <bwvr/VrTerrainQuad.h>


VrTerrainQuad::VrTerrainQuad(VrGroup *pGroup, VrQuadTree *pTerrain, vrIndex quadIndex, int level) 
: VrQuad(pGroup, pTerrain, quadIndex, level) {
}