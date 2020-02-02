/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _VrStablePhysics_H
#define _VrStablePhysics_H

#include "VrPhysics.h"

class VrStablePhysics : public VrPhysics {
public:
	VrStablePhysics(BwActor *pActor);
	//~VrStablePhysics();
	virtual void doCreate(const BwPartInfo& info) ;
public:
	virtual void doStep(BwStepper& stepper) ;
protected:
private:
};

#endif //_VrStablePhysics_H

