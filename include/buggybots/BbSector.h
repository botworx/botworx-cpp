/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _BbSector_H
#define _BbSector_H

#include <bwvr/VrPlace.h>

class VrShape ;
class VrShape ;
class VrLayout ;
class BbMapSector ;

class BbSector : public VrPlace {
public:
	BbSector(VrGroup *pGroup) ;
	virtual void createVu() ;
	virtual void onModelAddition(VrModel *pModel) ;
	virtual void onModelRemoval(VrModel *pModel) ;
	/*Data Members*/
	void setMapSector(BbMapSector* pMapSector) { p_mapSector = pMapSector ; }
	BbMapSector* getMapSector() { return p_mapSector ; }
public:
	BbMapSector* p_mapSector ;
};

#endif //_BbSector_H