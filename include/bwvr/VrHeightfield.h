/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _VrHeightfield_H
#define _VrHeightfield_H

#include "VrShape.h"

class VrTriMeshData ;

class VrHeightfield : public VrShape {
public:
	VrHeightfield(VrGroup *pGroup) ;
	virtual bwString getClassName() { return "VrHeightfield" ; }
	//
	virtual void createGeom() ;
	virtual void validateGeom() ;
	//
	virtual void createConvex() ;
	//
	void buildHfData() ;
	void setHeightData(bwReal* pHeightData) { p_heightData = pHeightData ; }
	bwReal* getHeightData() { return p_heightData ; }
	//Data Members
	bwReal* p_heightData ;
	dHeightfieldDataID m_hfDataID ;
};

#endif //_VrHeightfield_H
