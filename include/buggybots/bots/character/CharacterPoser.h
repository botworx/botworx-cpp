/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _CharacterPoser_H
#define _CharacterPoser_H

#include <bwvr/VrPoser.h>

namespace Character {

class CharacterPoser : public VrPoser {
public:
	CharacterPoser(VrModel* pModel) ;
	virtual bwString getClassName() { return "CharacterPoser" ; }
	virtual bool onStep(BwStepper& stepper) ;
	virtual bool onPostStep(BwStepper& stepper) ;
	//
	void applyLinearForce() ;
	void applyAngularForce() ;
};

} //namespace Character

#endif //_CharacterPoser_H
