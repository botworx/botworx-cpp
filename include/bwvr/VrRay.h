/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _VrRay_H
#define _VrRay_H

#include "VrGroup.h"
#include "VrShape.h"

class VrContactCollector ;

class VrRay : public VrShape {
public:
	VrRay(VrGroup *pGroup) ;
	virtual bwString getClassName() { return "VrRay" ; }
	virtual void createGeom() ;
	virtual void validateGeom() ;
	virtual void createCollider() ;
	VrContactCollector* getCollector() { return p_collector ; }
	/*Data Members*/
	VrContactCollector* p_collector ;
};

#endif //_VrRay_H
