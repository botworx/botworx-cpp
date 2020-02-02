/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _VrSharedVu_H
#define _VrSharedVu_H

#include "VrVu.h"

#include <OGRE/OgreStaticGeometry.h>

class VrPlace ;

class VrSharedVu : public VrVu {
public:
	VrSharedVu(VrPlace *pPlace) ;
	virtual ~VrSharedVu() ;
	virtual void doPostEnable(bool sleeping = false) ;
	virtual void doPostDisable(bool sleeping = false) ;
	virtual void build() ;
	//Data Members
public:
	VrPlace *p_place ;
	Ogre::StaticGeometry* p_geometry ;
};

#endif //_VrSharedVu_H