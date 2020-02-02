/*Botworx AI - An Artificial Intelligence Framework
Copyright (C) 2004  Kurtis Fields. See BotworxAI_License.txt for details.
*/
#include "stdafx.h"

#include <MouseScenario/MouseScenario.h>
#include <MouseScenario/MgMouse.h>
#include <MouseScenario/MouseBrain.h>

#include "MgVu.h"


/*class MgMouseBrain : public MgBrain {
public:
	MgMouseBrain(MgMouse* pMouse) : MgBrain(pMouse), p_mouse(pMouse) {
	} ;
	//Data Members
	MgMouse* p_mouse ;
};*/
//
MgMouse::MgMouse(MgScenario *pWorld) : MgEntity(pWorld) {
}
void MgMouse::createVu() {
	//p_vu = new MgMouseVu(this) ;
	p_vu = new MgVu(this) ;
	p_vu->create() ;
}
void MgMouse::createBrain() {
	//p_brain = new MgMouseBrain(this) ;
	p_brain = new MouseBrain(this) ;
	p_brain->create() ;	
}