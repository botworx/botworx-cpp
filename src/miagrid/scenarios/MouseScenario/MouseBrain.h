/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _MouseBrain_H
#define _MouseBrain_H

#include "MgBrain.h"

class MouseBrain : public MgBrain {
public:
	MouseBrain(MgEntity* pEntity) ;
	virtual void createAgent() ;
	virtual void sense() ;
	//Data Members
public:
};

#endif //_MouseBrain_H
