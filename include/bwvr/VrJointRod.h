/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _VrJointRod_H
#define _VrJointRod_H

#include "VrRod.h"

class VrJoint ;

class VrJointRod : public VrRod {
public:
	VrJointRod(BwPart *pOwner) : VrRod(pOwner) {}
	void create(VrJoint *pJoint) ;
	VrJoint& getJoint() { return *p_joint ; }
	VrJoint *p_joint ;
} ;

#endif //_VrJointRod_H