/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _VrRigidBody_H
#define _VrRigidBody_H

#include <bwvr/VrBody.h>

class VrRigidBody : public VrBody {
public:
	VrRigidBody(VrModel *pModel) ;
	virtual ~VrRigidBody() ;
	virtual void doCreate(const BwPartInfo& info) ;
	virtual void doEnable(bool sleeping = false) ;
	virtual void doDisable(bool sleeping = true) ;
	//
	virtual bwString getClassName() { return "VrRigidBody" ; }

	virtual void setPos(const bwPoint3& pos) ;
	virtual bwPoint3 getPos() ;
	virtual void addForce(const bwVector3& force) ;
	virtual void addRelForce(const bwVector3& force) ;
	virtual void addForceAtPos(const bwVector3& force, const bwPoint3& point) ;
	virtual void addForceAtRelPos(const bwVector3& force, const bwPoint3& point) ;
	virtual void addRelForceAtRelPos(const bwVector3& force, const bwPoint3& point) ;
	virtual void addTorque(const bwVector3& torque) ;
	virtual void addRelTorque(const bwVector3& torque) ;
	virtual void setGravityMode(int mode) ;
	virtual void setBodyInfo(const VrBodyInfo *bodyInfo) ;
	virtual void setLinearVel(const bwVector3& vel) ;
	virtual void setAngularVel(const bwVector3& vel) ;
	virtual void setQuat(const bwQuat &pQuat) ;
	virtual bwQuat getQuat() ;
	dBodyID getBodyID() { return m_bodyID ; }
protected:
	virtual void updateLinearVel() ;
	virtual void updateAngularVel() ;
	/*Data Members*/
public:
protected:
	dBodyID m_bodyID ;
} ;

#endif //_VrRigidBody_H