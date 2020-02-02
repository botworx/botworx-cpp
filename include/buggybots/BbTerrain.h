/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _BbTerrain_H
#define _BbTerrain_H

#include <bwvr/VrTerrain.h>

class BbTerrain : public VrTerrain {
public:
	BbTerrain(VrGroup *pGroup) ;
	virtual bool onCreate(const BwPartInfo& info) ;
	virtual void createQuadFactory() ;
	virtual VrQuad* createQuad(VrGroup *pGroup, int index, int level) ;
	//Data Members
};

#endif //_BbTerrain_H
