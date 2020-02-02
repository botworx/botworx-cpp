/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _VrBody_H
#define _VrBody_H

#include <bwcore/BwActor.h>
#include "VrBodyInfo.h"

class VrBody : public BwActor {
public:
	VrBody(VrModel *pModel) ;
	virtual ~VrBody() ;
	virtual void doCreate(const BwPartInfo& info) ;
	virtual void doEnable(bool sleeping = false) ;
	virtual void doDisable(bool sleeping = true) ;
	virtual void doStep(BwStepper& stepper) ;
	virtual bool onPostStep(BwStepper& stepper) ;
	virtual void _sleep() ;
	virtual void _touch(VrModel *pModel) ;
	virtual void _wake() ;
	//
	virtual bwString getClassName() { return "VrBody" ; }
	VrModel* getModel() { return p_model ; }

	virtual void setBodyInfo(const VrBodyInfo *m_bodyInfo) ; //TODO:why is this virtual ... do virtual on_bodyInfo/notify_bodyInfo
	const VrBodyInfo* getBodyInfo() { return &m_bodyInfo ; }
	VrBodyInfo& bodyInfo() { return m_bodyInfo ; }
	virtual void setPos(const bwPoint3& pos) = 0 ;
	virtual bwPoint3 getPos() = 0 ;
	virtual void addForce(const bwVector3& force) = 0 ;
	virtual void addRelForce(const bwVector3& force) = 0 ;
	virtual void addForceAtPos(const bwVector3& force, const bwPoint3& point) = 0 ;
	virtual void addForceAtRelPos(const bwVector3& force, const bwPoint3& point) = 0 ;
	virtual void addRelForceAtRelPos(const bwVector3& force, const bwPoint3& point) = 0 ;
	virtual void addTorque(const bwVector3& torque) = 0 ;
	virtual void addRelTorque(const bwVector3& torque) = 0 ;
	virtual void setGravityMode(int mode) = 0 ;
	virtual void setLinearVel(const bwVector3& vel) = 0 ;
	bwVector3 getLinearVel() ;
	virtual void setAngularVel(const bwVector3& vel) = 0 ;
	bwVector3 getAngularVel() ;
	virtual void setQuat(const bwQuat &pQuat) = 0 ;
	virtual bwQuat getQuat() = 0 ;
	void setRestThresh(bwReal val) { m_restThresh = val ; }
	void dampen(bwReal stepSize) ;
	//
	virtual void setRotMode(bwmath::rotationMode mode) { m_rotMode = mode ; }
	bwmath::rotationMode getRotMode() { return m_rotMode ; }
	virtual void setPosMode(bwmath::positionMode mode) { m_posMode = mode ; }
	bwmath::positionMode getPosMode() { return m_posMode ; }

	//Data Members
public:
	VrModel *p_model ;
	VrBody *p_parent ;
	VrBodyInfo m_bodyInfo ;
protected:
	bwVector3 m_linearVel ;
	bwReal m_linearEnergy ;
	bwVector3 m_angularVel ;
	bwReal m_angularEnergy ;
	bwReal m_energy ;
	bwReal m_restThresh ;
	//
	bwmath::rotationMode m_rotMode ;
	bwmath::positionMode m_posMode ;
protected:
	virtual void updateLinearVel() = 0 ;
	virtual void updateAngularVel() = 0 ;
} ;

#endif //_VrBody_H