/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <bwvr/VrController.h>
#include <bwvr/VrScenario.h>

VrController::VrController(VrController *pSuper) : BwController(pSuper) {
}
void VrController::bind() { 
	BwController::bind() ;
}
void VrController::unbind() {
	BwController::unbind() ;
}
VrScenario* VrController::getScenario() {
	return VrScenario::singleton::getPtr() ;
}