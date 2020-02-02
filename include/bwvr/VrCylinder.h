/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _VrCylinder_H
#define _VrCylinder_H

#include "VrGroup.h"
#include "VrShape.h"

class VrCylinder ;

class VrCylinder : public VrShape {
public:
	VrCylinder(VrGroup *pGroup) ;
	virtual bwString getClassName() { return "VrCylinder" ; }
	virtual void validateMass() ;
	virtual void createGeom() ;
	virtual void createConvex() ;
	virtual void validateGeom() ;
	/*Data Members*/
};

#endif //_VrCylinder_H
