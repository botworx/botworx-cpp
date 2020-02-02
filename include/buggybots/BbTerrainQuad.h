/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _BbTerrainQuad_H
#define _BbTerrainQuad_H

#include <bwvr/VrTerrainQuad.h>

class BbTerrainQuad : public VrTerrainQuad {
public:
	BbTerrainQuad(VrGroup *pGroup, BbTerrain *pTerrain, vrIndex quadIndex, int level) ;
	virtual void doConfig() ;
	/*Data Members*/
public:
	BbTerrain *p_terrain ;
};

#endif //_BbTerrainQuad_H