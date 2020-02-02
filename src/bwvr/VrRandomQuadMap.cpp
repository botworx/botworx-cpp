/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <bwvr/VrRandomQuadMap.h>
#include <bwvr/VrQuadTree.h>

void VrRandomQuadMap::alter(VrQuadTree *pTree) {
	VrQuad *pQuadRow = pTree->getOuterQuad(VR_NW) ;
	VrQuad *pQuad = pQuadRow ;
	bwPoint3 point ;
	int rowCounter = 0, colCounter = 0 ;
	bwReal rndHeight = 0 ;
	srand(1) ;
	while(pQuadRow != NULL) {
		while(pQuad != NULL) {
			//pQuad->setVertexHeight(1) ;
			point = pQuad->getPos() ; //fixme
			//pQuad->setPos(vector[0], rowCounter + colCounter, vector[2]) ;
			//rndHeight = ( (double)rand() / (double)(RAND_MAX+1) ) * m_scale ;
			rndHeight = bwReal(bwmath::unitRandom()) * m_scale ;

			pQuad->setPos(point[0], rndHeight, point[2]) ;
			pQuad = pQuad->p_east ;
			rowCounter = rowCounter + 1 ;
		}
		pQuad = pQuadRow = pQuadRow->p_south ;
		colCounter = colCounter + 1 ;
	}
}