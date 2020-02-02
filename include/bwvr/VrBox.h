/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _VrBox_H
#define _VrBox_H

#include "VrGroup.h"
#include "VrShape.h"

class VrBox : public VrShape {
public:
	VrBox(VrGroup *pGroup) ;
	virtual bwString getClassName() { return "VrBox" ; }
	virtual void validateMass() ;
	virtual void createGeom() ;
	virtual void validateGeom() ;
	//
	virtual void createConvex() ;
};

#endif //_VrBox_H
