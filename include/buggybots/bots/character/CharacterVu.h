/*CharacterBots - A Botworx VR reference app and AI playground
Copyright (C) 2005  Kurtis Fields. See botworx_license.txt for details.
*/
#ifndef _CharacterVu_H
#define _CharacterVu_H

#include <bwvr/VrVu.h>

namespace Ogre {
	class AnimationState ;
	class SceneNode ;
}

namespace Character {

class Character ;

class CharacterVu : public VrVu
{
public:
	CharacterVu(Character *pCharacter) ;
	virtual void createSceneNode() ;
	virtual void createMeshInstance() ;
	virtual void attachMeshInstance() ;
	virtual bool onPostStep(BwStepper& stepper) ;
	virtual void validateNode() ;
private:
	Character *p_animat ;
	Ogre::AnimationState *p_animState ;
	Ogre::SceneNode *p_skelNode ;
public:
};

} //namespace Character

#endif

