/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _VrKinematicPoser_H
#define _VrKinematicPoser_H

#include "VrPoser.h"

class VrKinematicPoser : public VrPoser {
public:
	VrKinematicPoser(VrModel* pModel) : VrPoser(pModel) {
	}
	virtual bool onStep(BwStepper& stepper) {
		p_model->setPos(getPos()) ;
		p_model->setQuat(getQuat()) ;
		return VrPoser::onStep(stepper) ;
	}
};

#endif //_VrKinematicPoser_H
