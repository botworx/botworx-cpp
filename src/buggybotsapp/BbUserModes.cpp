/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include "BbUserModes.h"
#include <bwvr/VrBody.h>

void BbObjectCreator::activate() {
	bwString name = p_parent->getShortName() ;
	bwQuat quat ;
	set(quat, bwAxisAngle(bwRealTraits::Pi, bwVector3(0,1,0))) ;
	bwPose pose(bwPoint3(0,0,0), quat) ;
	VrModel* pModel = p_user->getHand()->buildEnabled(name, pose) ;
	_BwKernel::Info evt("User built a " + name + "\n") ;
	BwKernel::singleton::get().getEventSlot()->send(evt) ;
	//
	VrBody* pBody = pModel->getBody() ;
	if(pBody != NULL) {
		bwReal mass = pBody->bodyInfo().getMass() ;
		char buffer[32]  ;
		// std::stringstream temp(buffer, 32) ;
		std::stringstream temp(buffer) ;
		temp << mass ;
		_BwKernel::Info evt("Mass = " + bwString(temp.str()) + "\n") ;
		BwKernel::singleton::get().getEventSlot()->send(evt) ;
	}
}
