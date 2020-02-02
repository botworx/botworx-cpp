/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _VrMultiBody_H
#define _VrMultiBody_H

#include "VrBody.h"

class VrMultiBody : public VrBody {
public:
	VrMultiBody(VrModel *pModel) ;
	virtual bool onPostStep(BwStepper& stepper) { return true ; }
	//Pure Virtual Implementations
	//TODO:need to implement?
	virtual void setPos(const bwPoint3& pos) {}
	virtual bwPoint3 getPos() { return bwPoint3() ; } //TODO:
	virtual void addForce(const bwVector3& force) {}
	virtual void addRelForce(const bwVector3& force) {}
	virtual void addForceAtPos(const bwVector3& force, const bwPoint3& point) {}
	virtual void addForceAtRelPos(const bwVector3& force, const bwPoint3& point) {}
	virtual void addRelForceAtRelPos(const bwVector3& force, const bwPoint3& point) {}
	virtual void addTorque(const bwVector3& torque) {}
	virtual void addRelTorque(const bwVector3& torque) {}
	virtual void setGravityMode(int mode) {}
	virtual void setLinearVel(const bwVector3& vel) {}
	virtual void setAngularVel(const bwVector3& vel) {}
	virtual void setQuat(const bwQuat &pQuat) {}
	virtual bwQuat getQuat() { return bwQuat() ; } //TODO:
protected:
	virtual void updateLinearVel() {}
	virtual void updateAngularVel() {}
} ;
#endif //_VrMultiBody_H