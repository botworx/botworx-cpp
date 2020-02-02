/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _BbLaserGun_H
#define _BbLaserGun_H

#include "BbGun.h"

class BbLaser ;

class BbLaserGun : public BbGun {
public:
	BbLaserGun(VrGroup *pGroup) ;
	//virtual bool doStep(BwStepper& stepper) ;
	virtual void doStep(BwStepper& stepper) ;
	virtual bwString getClassName() { return "BbLaserGun" ; }
	//
	virtual void onTrigger() ;
	/*Data Members*/
private:
	BbLaser *p_laser ;
};

#endif //_BbLaserGun_H
