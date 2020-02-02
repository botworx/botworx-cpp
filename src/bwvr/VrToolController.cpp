/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <bwvr/VrToolController.h>
#include <bwvr/VrModel.h>

VrToolController::VrToolController(VrController *pSuper) : VrController(pSuper) {
	p_tool = NULL ;
}
void VrToolController::bind() {
	VrController::bind() ;
}
void VrToolController::unbind() {
	VrController::unbind() ;
}
bool VrToolController::processEvent(BwControllerEvent&& evt) {
	return true ;
}
