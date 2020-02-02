#include "stdafx.h"

#include <bwvr/VrPhysicsBase.h>
#include <bwvr/VrModel.h>

//
const bwDT VrPhysicsBase::STEPSIZE_MIN = 0.01f ;
const bwDT VrPhysicsBase::STEPSIZE_MAX = 0.03f ;
const bwDT VrPhysicsBase::STEPSIZE_RAMP = 0.001f ;
//
//VrPhysicsBase
//
VrPhysicsBase::VrPhysicsBase(BwActor *pActor) : BwActor(pActor) {
	p_stage = &m_stage ; 	
	m_stage.setOwner(this) ; 
	m_stage.create() ;
	/*
	STEP_FIXED,
	STEP_VARIABLE,
	STEP_CLAMPED,
	STEP_ACCUM
	*/
	m_steppingMode = STEP_CLAMPED ;
	//m_steppingMode = STEP_VARIABLE ;
	//m_steppingMode = STEP_ACCUM ;
	//
	m_stepSizeMin = STEPSIZE_MIN ;
	m_stepSizeMax = STEPSIZE_MAX ;
	m_accumStepSize = 0 ;
	setDeltaTime(m_stepSizeMin) ;
	m_stepTtl = 0 ;
	m_gravity = bwVector3(0, -9.98f, 0) ;
	//m_gravity = bwVector3(0, -25, 0) ; //why??? standard gravity is too floaty???
 }
VrPhysicsBase::~VrPhysicsBase() {
}
//TODO: space heirarchy needs to go into scenario?
void VrPhysicsBase::addModel(VrModel *pModel) {
	pModel->p_owner = this ;
	p_stage->addActor(pModel) ;
}
void VrPhysicsBase::doStep(BwStepper& stepper) {
	bwDT deltaTime = stepper.getDeltaTime() ;
	setDeltaTime(calcStepSize(deltaTime)) ;
	BwActor::doStep(stepper) ;
}
bool VrPhysicsBase::onPostStep(BwStepper& stepper) {
	return BwActor::onPostStep(stepper) ;
}
bwDT VrPhysicsBase::calcFixedStepSize(bwDT stepSize) {
	m_stepTtl = 1 ;
	return m_stepSizeMin ;
}
bwDT VrPhysicsBase::calcVariableStepSize(bwDT stepSize)  {
	m_stepTtl = 1 ;
	return stepSize ;
}
bwDT VrPhysicsBase::calcClampedStepSize(bwDT stepSize) {
	m_stepTtl = 1 ;
	bwDT adjStepSize = stepSize ;
	if(stepSize > m_deltaTime + STEPSIZE_RAMP)
		adjStepSize = m_deltaTime + STEPSIZE_RAMP ; //Ramp Down from Max
	else
		adjStepSize = m_deltaTime - STEPSIZE_RAMP ; //Ramp Down from Max

	if(adjStepSize < m_stepSizeMin)
		return m_stepSizeMin ;
	else if(adjStepSize > m_stepSizeMax)
		return m_stepSizeMax ;
	else
		return adjStepSize ;
}
bwDT VrPhysicsBase::calcAccumStepSize(bwDT stepSize) {
	bwDT adjStepSize = stepSize ;
	if(stepSize > m_stepSizeMax)
		adjStepSize = m_stepSizeMax ;
	m_accumStepSize += adjStepSize ;
	m_stepTtl = 0 ;
	while (m_accumStepSize > m_stepSizeMin)	{
		m_accumStepSize -= adjStepSize ;
		m_stepTtl++ ;
	}
	return adjStepSize ;
}
bwDT VrPhysicsBase::calcStepSize(bwDT stepSize) {
	switch(m_steppingMode) {
		case STEP_FIXED :
			return calcFixedStepSize(stepSize) ;
		case STEP_VARIABLE :
			return calcVariableStepSize(stepSize) ;
		case STEP_CLAMPED :
			return calcClampedStepSize(stepSize) ;
		case STEP_ACCUM :
			return calcAccumStepSize(stepSize) ;
	}
	return stepSize ;
}