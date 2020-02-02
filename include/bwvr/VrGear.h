/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _VRGEAR_H
#define _VRGEAR_H

#include "VrRod.h"

class VrGear ;

typedef std::list<VrGear*> VrGearContainer ;
typedef std::list<VrGear*>::iterator VrGearIter ;

class VrGear : public VrRod {
public:
	VrGear(BwPart *pOwner, VrRod *pRod = NULL, bwReal radius = 1) ;

	//VrRod
	virtual void setVelocity(bwReal value) ;
	virtual void setAngle(bwReal value) ;
	virtual void setForceMax(bwReal value) ;
	virtual void addTorque(bwReal value) ;
	//VrGear
	virtual VrGear* addGear(VrRod *pRod, bwReal radius = 1) ;
	void setRod(VrRod *pRod) { p_rod = pRod ; }
	VrRod* getRod() { return p_rod ; }
	//Data Members
	VrRod *p_rod ; //transmit power too..
	VrGearContainer m_gears ; //Gears attached to this one.
	int m_gearTotal ;
	bwReal m_radius ;
	bwReal m_ratio ; //Ratio to parent gear
} ;

#endif //_VRGEAR_H