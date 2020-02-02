/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _Ufo_H
#define _Ufo_H

#include <bwvr/VrBall.h>

class Ufo : public VrBall {
public:
	Ufo(VrGroup *pGroup) ;
	virtual bwString getClassName() { return "Ufo" ; }
	virtual void createBrain() ;
	//Data Members
};

#endif //_Ufo_H
