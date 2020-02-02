/*CharacterBots - A Botworx VR reference app and AI playground
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _CharacterBrain_H
#define _CharacterBrain_H

#include <buggybots/BbPilotBrain.h>

class BbScanner ;

namespace Character {

class Character ;
class CharacterPoser ;

class CharacterBrain : public BbPilotBrain {
public:
	CharacterBrain(Character *pCharacter) ;
	virtual void doConfig() ;
	virtual bool onPostStep(BwStepper& stepper) ;
	virtual void moveForward() ;
	virtual void moveReverse() ;
	virtual void moveNone() ;

	//Steering
	virtual void turnLeft() ;
	virtual void turnRight() ;
	virtual void turnNone() ;
	//Jumping
	virtual void jump() ;
	virtual void jumpNone() ;

	void pitchUp() ;
	void pitchDown() ;
	void rollLeft() ;
	void rollRight() ;
	//Data Members
public:
	Character* p_animat ;
	BbScanner* p_scanner ;
};

} //namespace Character {

#endif //_CharacterBrain_H
