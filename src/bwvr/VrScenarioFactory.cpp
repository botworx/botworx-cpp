/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <bwvr/VrScenarioFactory.h>
#include <bwvr/VrSystem.h>
#include <bwvr/VrApplet.h>

void VrScenarioFactory::release(void *pCell) {
	VrApplet* pApplet = VrApplet::singleton::getPtr() ;
	if(pApplet != NULL)
		pApplet->nextScenario() ;
}