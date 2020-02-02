/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _VrBrain_H
#define _VrBrain_H

//#include <bwcontrol/BwBrain.h>
#include <bwvr/VrMech.h>

//class VrBrain : public BwBrain {
class VrBrain : public VrMech {
public:
	VrBrain(VrModel* pModel) ;
	virtual ~VrBrain() ;
	virtual bool processMessage(BwMessage&& msg) ;
	//Moving
	virtual void moveForward() {}
	virtual void moveReverse() {}
	virtual void moveNone() {}
	//Steering
	virtual void turnLeft() {}
	virtual void turnRight() {}
	virtual void turnNone() {}
	//Etc
	virtual void pitchUp() {}
	virtual void pitchDown() {}
	virtual void rollLeft() {}
	virtual void rollRight() {}
	//Jumping
	virtual void jump() {}
	virtual void jumpNone() {}
	//Firing
	virtual void fireMissile() {}
	virtual void fireLaser() {}
	//
	VrModel& model() { return *getModel() ; }
	VrModel* getModel() { return p_model ; }
	/*Data Members*/
public:
	VrModel* p_model ;
};

#endif //_VrBrain_H
