/*Botworx AI - An Artificial Intelligence Framework
Copyright (C) 2004  Kurtis Fields. See BotworxAI_License.txt for details.
*/
#ifndef _MgMouse_H
#define _MgMouse_H

#include "MgEntity.h"

class MgMouse : public MgEntity {
public:
	MgMouse(MgScenario *pWorld) ;
	virtual void createBrain() ;
	virtual void createVu() ;
	//Data Members
} ;

#endif //_MgMouse_H
