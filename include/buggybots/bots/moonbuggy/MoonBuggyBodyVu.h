/*BuggyBots - A Botworx VR reference app and AI playground
Copyright (C) 2005  Kurtis Fields. See BuggyBots_License.txt for details.
*/
#ifndef _MoonBuggyChassisVu_H
#define _MoonBuggyChassisVu_H

#include <bwvr/VrVu.h>

namespace Ogre {
	class Light ;
}

class VrShape ;

namespace MoonBuggy {

class BuggyChassis ;

class BuggyChassisVu : public VrVu {
public:
	BuggyChassisVu(BuggyChassis *pChassis) ;
	virtual void createSceneNode() ;
	//virtual void createMeshInstance() ;
	void createLight() ;
	/*Data Members*/
public:
	BuggyChassis *p_chassis ;
	Ogre::Light* p_light; //TODO:Maybe we need VrLight? Or too much wrapping involved?
};
}//end namespace BwVr::Bots::MoonBuggy
#endif //_MoonBuggyChassisVu_H
