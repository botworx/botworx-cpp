#include "stdafx.h"

#include <bwvr/VrQuickPhysics.h>
#include <bwvr/VrCollider.h>

VrQuickPhysics::VrQuickPhysics(BwActor *pActor) : VrPhysics(pActor) {
}
/*************************************************
dReal dWorldGetAutoDisableLinearThreshold (dWorldID w)
void dWorldSetAutoDisableLinearThreshold (dWorldID w, dReal linear_threshold)
dReal dWorldGetAutoDisableAngularThreshold (dWorldID w)
void dWorldSetAutoDisableAngularThreshold (dWorldID w, dReal angular_threshold)
int dWorldGetAutoDisableSteps (dWorldID w)
void dWorldSetAutoDisableSteps (dWorldID w, int steps)
dReal dWorldGetAutoDisableTime (dWorldID w)
void dWorldSetAutoDisableTime (dWorldID w, dReal time)
int dWorldGetAutoDisableFlag (dWorldID w)
void dWorldSetAutoDisableFlag (dWorldID w, int do_auto_disable)
void dWorldSetQuickStepNumIterations (dWorldID w, int num)
int dWorldGetQuickStepNumIterations (dWorldID w)
void dWorldSetQuickStepW (dWorldID w, dReal param)
dReal dWorldGetQuickStepW (dWorldID w)
void dWorldSetContactMaxCorrectingVel (dWorldID w, dReal vel)
dReal dWorldGetContactMaxCorrectingVel (dWorldID w)
void dWorldSetContactSurfaceLayer (dWorldID w, dReal depth)
dReal dWorldGetContactSurfaceLayer (dWorldID w)
*************************************************/

void VrQuickPhysics::doCreate(const BwPartInfo& info) {
	VrPhysics::doCreate(info) ;
	//dWorldSetQuickStepNumIterations (m_worldID, 20); //20 is default
}
void VrQuickPhysics::doStep(BwStepper& stepper) {
	VrPhysics::doStep(stepper) ;
	//dWorldSetQuickStepNumIterations (m_worldID, 5); //20 is default
	if(m_deltaTime != 0)
		for(size_t i = 0 ; i < m_stepTtl ; ++i)
			dWorldQuickStep(m_worldID, m_deltaTime);
}
bool VrQuickPhysics::onPostStep(BwStepper& stepper) {
	return VrPhysics::onPostStep(stepper) ;
}