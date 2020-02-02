/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _VRSTEERING_H
#define _VRSTEERING_H

#include "VrGear.h"

class VrMech ;

class VrSteering : public VrGear {
public:
	VrSteering(BwPart *pOwner, VrRod *pRod = NULL, bwReal radius = 1) ;
	virtual void turnLeft() ;
	virtual void turnRight() ;
	void turnNone() ;
} ;

#endif //_VRSTEERING_H