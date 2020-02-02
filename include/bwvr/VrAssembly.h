/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _VrAssembly_H
#define _VrAssembly_H

#include "VrGroup.h"

class VrShape ;
class VrShape ;
class VrLayout ;
class VrPhysics ;
class VrNodeKit ;

class VrAssembly : public VrGroup {
public:
	VrAssembly(VrGroup *pGroup) ;
	virtual bwString getClassName() { return "VrAssembly" ; }
	virtual void validateMass() ;
	virtual void onModelAddition(VrModel *pModel) ;
/*Data Members*/
};

#endif //_VrAssembly_H
