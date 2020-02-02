/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _BbLaser_H
#define _BbLaser_H

#include <bwvr/VrRay.h>

class BbLaser : public VrRay {
public:
	BbLaser(VrGroup *pGroup) ;
	virtual bwString getClassName() { return "BbLaser" ; }
	virtual bool onPostStep(BwStepper& stepper) ;
	//Data Members
};

#endif //_BbLaser_H
