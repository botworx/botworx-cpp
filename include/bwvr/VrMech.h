/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _VrMech_H
#define _VrMech_H

#include <bwcontrol/BwBrain.h>
/*
VrMech:  This is a Mechanically Inclined Brain.
*/
class VrJoint ;
typedef std::list<VrJoint*> VrJointContainer ;

class VrMech : public BwBrain {
public:
	VrMech(BwActor *pOwner) ;
	virtual void pose(int poseCmd) {}
	//Data
} ;
///////////////
class VrRod ;
class VrRodMech : public VrMech {
public:
	VrRodMech(BwActor *pOwner) : VrMech(pOwner) {
		p_rod = NULL ;
	}
	void setRod(VrRod *pRod) { p_rod = pRod ; }
	VrRod* getRod() { return p_rod ; }
	//Data
	VrRod *p_rod ;
} ;
///////////////
class VrMotor ;
class VrMotorMech : public VrRodMech {
public:
	VrMotorMech(BwActor *pOwner) : VrRodMech(pOwner) {
		p_motor = NULL ;
	}
	void setMotor(VrMotor *pMotor) { p_motor = pMotor ; }
	VrMotor* getMotor() { return p_motor ; }
	//Data
	VrMotor *p_motor ;
} ;
///////////////
class VrJoint ;
class VrJointMech : public VrMech {
public:
	VrJointMech(BwActor *pOwner) : VrMech(pOwner) {
		p_rod_1 = NULL ;
		p_rod_2 = NULL ;
	}
	void setJoint(VrJoint *pJoint) { p_joint = pJoint ; }
	VrJoint* getJoint() { return p_joint ; }
	VrRod* getRod1() { return p_rod_1 ; }
	VrRod* getRod2() { return p_rod_2 ; }
	//Data
	VrJoint *p_joint ;
	VrRod *p_rod_1 ;
	VrRod *p_rod_2 ;
} ;
///////////////
class VrMotorizedJointMech : public VrJointMech {
public:
	VrMotorizedJointMech(BwActor *pOwner) : VrJointMech(pOwner) {
		p_motor_1 = NULL ;
		p_motor_2 = NULL ;
	}
	VrMotor* getMotor1() { return p_motor_1 ; }
	VrMotor* getMotor2() { return p_motor_2 ; }
	//Data
	VrMotor *p_motor_1 ;
	VrMotor *p_motor_2 ;
} ;

#endif //_VrMech_H
