/*UfoBots - A Botworx VR reference app and AI playground
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _UfoBrain_H
#define _UfoBrain_H

#include <buggybots/BbPilotBrain.h>

class Ufo ;

class UfoBrain : public BbPilotBrain {
public:
	UfoBrain(Ufo *pUfo) ;
	virtual void moveForward() ;
	virtual void moveReverse() ;
	//Steering
	virtual void turnLeft() ;
	virtual void turnRight() ;
	virtual void pitchUp() ;
	virtual void pitchDown() ;
	virtual void rollLeft() ;
	virtual void rollRight() ;
	//Data Members
public:
	Ufo *p_animat ;
};

#endif //_UfoBrain_H
