/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _VrPhysicsBase_H
#define _VrPhysicsBase_H

#include <bwcore/BwStage.h>

class VrScenario ;
class VrModel ;
class VrGroup ;
class VrBody ;
class VrJoint ;
class VrCollisionRecord ;
struct VrContact ;
class VrSurfaceInfo ;
//
//VrPhysics
//
class VrPhysicsBase : public BwActor {
public:
	VrPhysicsBase(BwActor *pActor) ;
	virtual ~VrPhysicsBase();
	void addModel(VrModel *pModel) ;
	virtual void doStep(BwStepper& stepper) ;
	virtual bool onPostStep(BwStepper& stepper) ;
public:
	void setSteppingMode(int mode) { m_steppingMode = mode ; }
	virtual bwDT calcStepSize(bwDT stepSize) ;
	//Factory Methods
	virtual VrBody* createBody(VrModel* pModel) = 0 ;
	virtual VrJoint* createJoint(jointType type, VrGroup* pGroup) = 0 ;
	//
	virtual void releaseInnerCollision(void* pInner) {} //release collision inside physics engine.
	virtual void processContact(VrCollisionRecord& record, VrSurfaceInfo& contactSurfaceInfo, VrContact *pContact) = 0 ;
//protected:
	bwDT calcFixedStepSize(bwDT stepSize) ;
	bwDT calcVariableStepSize(bwDT stepSize) ;
	bwDT calcClampedStepSize(bwDT stepSize) ;
	bwDT calcAccumStepSize(bwDT stepSize) ;
public:
	enum SteppingMode {
		STEP_FIXED,
		STEP_VARIABLE,
		STEP_CLAMPED,
		STEP_ACCUM
	};
	static const bwDT STEPSIZE_MIN ;
	static const bwDT STEPSIZE_MAX ;
	static const bwDT STEPSIZE_RAMP ;
	//
	bwVector3 m_gravity ;
protected:
	int m_steppingMode ;
	size_t m_stepTtl ;
	bwDT m_stepSizeMax ;
	bwDT m_stepSizeMin ;
	bwDT m_accumStepSize;
public:
	//
	void setDeltaTime(bwDT deltaTime) { 
		m_deltaTime = deltaTime ; 
		if (deltaTime > 0.0f)
			m_invDt = 1.0f / deltaTime ;
		else
			m_invDt = 1.0e-30f ;
	}
	bwDT getDeltaTime() { return m_deltaTime ; }
	bwDT getInvDt() { return m_invDt ; }
	//
	//Data Members
	BwDefaultStage m_stage ;
	bwDT m_deltaTime ;
	bwDT m_invDt ;
};

#endif //_VrPhysicsBase_H


