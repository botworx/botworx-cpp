/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _VRWORLD_H
#define _VRWORLD_H

#include "VrPlace.h"

class VrScenario ;
class VrCollider ;

class VrWorld : public VrPlace
{
public:
	VrWorld(BwActor *pParent) ;
	virtual ~VrWorld();
	virtual bool onCreate(const BwPartInfo& info) ;
	virtual void recenter(const bwPoint3& point) {}
public:
	virtual bwString getClassName() { return "VrWorld" ; }
protected:
};

#endif //_VRWORLD_H

