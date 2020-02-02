/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _VrModelFactory_H
#define _VrModelFactory_H

#include <bwcore/BwFactory.h>

class VrGroup ;
//
//VrModelFactory
//
class VrModelFactory : public BwFactory {
public:
	VrModelFactory(BwPart* pOwner, BwKit *pKit = NULL) : BwFactory(pOwner, pKit) {}
	virtual VrModel* produce(VrGroup *pGroup, bwPartStyle style = PS_DEFAULT) { return NULL ; }
public:
	//Data
} ;

#endif //_VrModelFactory_H
