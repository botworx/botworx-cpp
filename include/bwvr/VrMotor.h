/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _VrMotor_H
#define _VrMotor_H

#include "VrGear.h"
class VrMech ;

class VrMotor : public VrGear {
public:
	VrMotor(BwPart *pOwner, VrRod *pRod, bwReal radius) ;
	virtual ~VrMotor() ;
	virtual void setPower(bwReal power) ; //0 to 1 
	bwReal getPower() { return m_power ; }
	//Data
	VrMech *p_mech ;
	bwReal m_power ;
} ;

#endif //_VrMotor_H