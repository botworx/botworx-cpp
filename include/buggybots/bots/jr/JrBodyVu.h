/*JrBots - A Botworx VR reference app and AI playground
Copyright (C) 2005  Kurtis Fields. See JrBots_License.txt for details.
*/
#ifndef _JrBodyVu_H
#define _JrBodyVu_H

#include <bwvr/VrVu.h>

namespace Ogre {
	class Light ;
}

class VrShape ;

namespace Jr {

class JrBody ;

class JrBodyVu : public VrVu {
public:
	JrBodyVu(JrBody *pChassis) ;
	virtual void createSceneNode() ;
	//virtual void createMeshInstance() ;
	void createLight() ;
	/*Data Members*/
public:
	JrBody *p_chassis ;
	Ogre::Light* p_light; //TODO:Maybe we need VrLight? Or too much wrapping involved?
};
}//end namespace BwVr::Bots::Jr
#endif //_JrBodyVu_H
