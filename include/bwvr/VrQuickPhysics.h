/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _VrQuickPhysics_H
#define _VrQuickPhysics_H

#include "VrPhysics.h"
//
//VrQuickPhysics
//
class VrQuickPhysics : public VrPhysics {
public:
	VrQuickPhysics(BwActor *pActor);
	//~VrQuickPhysics();
	virtual void doCreate(const BwPartInfo& info) ;
public:
	virtual void doStep(BwStepper& stepper) ;
	virtual bool onPostStep(BwStepper& stepper) ;
protected:
private:
};

#endif //_VrQuickPhysics_H

