/*MapperBots - A Botworx VR reference app and AI playground
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _MapperBrain_H
#define _MapperBrain_H

#include <buggybots/BbPilotBrain.h>

class Mapper ;

class MapperBrain : public BbPilotBrain {
public:
	MapperBrain(Mapper *pMapper) ;
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
	Mapper *p_animat ;
};

#endif //_MapperBrain_H
