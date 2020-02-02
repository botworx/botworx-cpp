/*BirdBots - A Botworx VR reference app and AI playground
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _BirdBrain_H
#define _BirdBrain_H

#include <buggybots/BbPilotBrain.h>

class Bird ;

class BirdBrain : public BbPilotBrain {
public:
	BirdBrain(Bird *pBird) ;
	virtual void moveForward() ;
	virtual void moveReverse() ;
	//virtual void moveNone() ;

	//Steering
	virtual void turnLeft() ;
	virtual void turnRight() ;
	//virtual void turnNone() ;
	virtual void pitchUp() ;
	virtual void pitchDown() ;
	virtual void rollLeft() ;
	virtual void rollRight() ;

	/*Data Members*/
public:
	Bird *p_animat ;
};

#endif //_BirdBrain_H
