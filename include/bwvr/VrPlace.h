/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _VrPlace_H
#define _VrPlace_H

#include "VrGroup.h"

class VrShape ;
class VrShape ;
class VrLayout ;

class VrPlaceKit ;
class VrPlaceFactory ;
//
//VrPlace
//
class VrPlace : public VrGroup {
public:
	VrPlace(VrGroup *pGroup) ;
	virtual bwString getClassName() { return "VrPlace" ; }
	virtual void doConfig() ;
	virtual void createDynamicLay() ;
	virtual void invalidate(VrModel *pModel, invalid flags) ;
	VrModelContainer* collectStaticModels() ;
	//Data Members
};
//
class VrPlaceLay : public VrLay {
public:
	virtual bwString getClassName() { return "VrPlaceLay" ; }
	virtual void validate() {}
};

#endif //_VrPlace_H