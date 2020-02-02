/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _VRGROUND_H
#define _VRGROUND_H

#include "VrShape.h"

class VrPlane : public VrShape {
public:
	VrPlane(VrGroup *pGroup) ;
	virtual void createVu() ;
	virtual bwString getClassName() { return "VrPlane" ; }
	virtual void createGeom() ;
	virtual void validateGeom() ;
	//
	virtual void createConvex() ;
} ;

#endif //_VRGROUND_H