/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _VrBall_H
#define _VrBall_H

#include "VrShape.h"
//
//VrBall
//
class VrBall : public VrShape {
public:
	VrBall(VrGroup *pGroup) ;
	virtual bwString getClassName() { return "VrBall" ; }
	virtual void validateMass() ;
	virtual void createGeom() ;
	virtual void validateGeom() ;
	//
	virtual void createConvex() ;
};

#endif //_VrBall_H
