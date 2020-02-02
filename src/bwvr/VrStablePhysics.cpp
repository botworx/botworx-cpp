#include "stdafx.h"

#include <bwvr/VrStablePhysics.h>
#include <bwvr/VrCollider.h>

VrStablePhysics::VrStablePhysics(BwActor *pActor) : VrPhysics(pActor)
{
}
void VrStablePhysics::doCreate(const BwPartInfo& info) {
	VrPhysics::doCreate(info) ;
}
void VrStablePhysics::doStep(BwStepper& stepper)
{
	VrPhysics::doStep(stepper) ;

	if(m_deltaTime != 0)
		for(size_t i = 0 ; i < m_stepTtl ; ++i)
			dWorldStep(m_worldID, m_deltaTime);
}