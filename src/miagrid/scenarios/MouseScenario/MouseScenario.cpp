/*Botworx AI - An Artificial Intelligence Framework
Copyright (C) 2004  Kurtis Fields. See BotworxAI_License.txt for details.
*/
#include "stdafx.h"

#include <MouseScenario/MouseScenario.h>
#include <MouseScenario/MgMouse.h>

MouseScenario::MouseScenario() : MgScenario() {
}
bool MouseScenario::onCreate(const BwPartInfo& info) {
	MgMouse* pEntity1 = new MgMouse(this) ;
	pEntity1->setName("Mouse") ;
	pEntity1->setPos(mgPos(6,6)) ;
	pEntity1->create() ;
	return MgScenario::onCreate(info) ;
}