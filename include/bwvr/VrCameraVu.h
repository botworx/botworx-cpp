/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _VrCameraVu_H
#define _VrCameraVu_H

#include "VrVu.h"

namespace Ogre {
	class Viewport ;
	class Camera ;
}

class VrCamera ;

class VrCameraVu : public VrVu
{
public:
	VrCameraVu(VrCamera *pCamera) ;
	virtual void doPostConfig() ;
	virtual bool onPostStep(BwStepper& stepper) ;
public:
	void createCamera() ;
	Ogre::Camera * getOgreCamera() { return p_ogreCamera ; }
private:
	VrCamera *p_camera ;
	Ogre::Viewport* p_viewport ;
	Ogre::Camera *p_ogreCamera ;
};

#endif

