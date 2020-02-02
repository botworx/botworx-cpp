/*BikeBots - A Botworx VR reference app and AI playground
Copyright (C) 2005  Kurtis Fields. See BikeBots_License.txt for details.
*/
#ifndef _BikePrimaryVu_H
#define _BikePrimaryVu_H

#include <bwvr/VrVu.h>

namespace Ogre {
	class Light ;
}

class VrShape ;

namespace Bike {

class BikePrimary ;

class BikePrimaryVu : public VrVu {
public:
	BikePrimaryVu(BikePrimary *pChassis) ;
	virtual void createSceneNode() ;
	//virtual void createMeshInstance() ;
	void createLight() ;
	/*Data Members*/
public:
	BikePrimary *p_chassis ;
	Ogre::Light* p_light; //TODO:Maybe we need VrLight? Or too much wrapping involved?
};
}//end namespace BwVr::Bots::Bike
#endif //_BikePrimaryVu_H
