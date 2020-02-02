/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _VrCapsule_H
#define _VrCapsule_H

#include "VrGroup.h"
#include "VrShape.h"

class VrCapsule ;

class VrCapsule : public VrShape {
public:
	VrCapsule(VrGroup *pGroup) ;
	virtual bwString getClassName() { return "VrCapsule" ; }
	virtual void validateMass() ;
	virtual void createGeom() ;
	virtual void validateGeom() ;
	/*Data Members*/
};

#endif //_VrCapsule_H
