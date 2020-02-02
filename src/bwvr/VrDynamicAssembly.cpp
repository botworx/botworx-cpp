/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <bwvr/VrDynamicAssembly.h>
#include <bwvr/VrBody.h>
#include <bwvr/VrMultiBody.h>
//
VrDynamicAssembly::VrDynamicAssembly(VrGroup *pGroup) : VrAssembly(pGroup) {
	setMotionType(MOTION_KINEMATIC) ;
}
void VrDynamicAssembly::createBody() {
	return ;
	p_body = new VrMultiBody(this) ;
	p_body->create() ;
}
bool VrDynamicAssembly::onPostStep(BwStepper& stepper) {
	if(p_main != NULL) {
		VrBody *pBody = p_main->getBody() ;
		if(pBody != NULL)
			setQuat(pBody->getQuat()) ;
		else
			setQuat(p_main->getQuat()) ;
	}
	return VrAssembly::onPostStep(stepper) ;
}
