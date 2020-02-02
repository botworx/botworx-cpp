/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _Bird_H
#define _Bird_H

#include <bwvr/VrBall.h>

class Bird : public VrBall {
public:
	Bird(VrGroup *pGroup) ;
	virtual bwString getClassName() { return "Bird" ; }
	virtual void createBrain() ;
	//Data Members
};

#endif //_Bird_H
