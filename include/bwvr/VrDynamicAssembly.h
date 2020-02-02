/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _VrDynamicAssembly_H
#define _VrDynamicAssembly_H

#include "VrAssembly.h"

class VrShape ;
class VrShape ;
class VrLayout ;
class VrPhysics ;
class VrNodeKit ;
class VrSkeleton ;

class VrDynamicAssembly : public VrAssembly {
public:
	VrDynamicAssembly(VrGroup *pGroup) ;
	virtual bwString getClassName() { return "VrDynamicAssembly" ; }
	virtual void createBody() ;
	virtual bool onPostStep(BwStepper& stepper) ;
	//Data Members
};

#endif //_VrDynamicAssembly_H
