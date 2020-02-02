/*Botworx AI - An Artificial Intelligence Framework
Copyright (C) 2004  Kurtis Fields. See BotworxAI_License.txt for details.
*/
#include "stdafx.h"

#include <bwmia/MiaState.h>
//////////////////
MiaStage::MiaStage() : MiaStageBase() {
	m_maxValue = MiaState::DEFAULT_VALUE ;
	p_superiorState = NULL ;
}
void MiaStage::doStep(BwStepper& stepper) {
	MiaStageBase::doStep(stepper) ;
	//f6:newstuff
	if(p_superiorState != NULL) {
		for(T_List::iterator iter = m_actingActors.begin() ; iter != m_actingActors.end() ; ++iter) {
			MiaState* pState = static_cast<MiaState*>(*iter) ;
			if(pState != p_superiorState)
				pState->doze() ;
		}
	}
	owner().setCostTtl(owner().getCostTtl() + owner().getCost()) ;
	owner().setBenefitTtl(owner().getBenefitTtl() + owner().getBenefit()) ;
	owner().setValue(owner().getBenefitTtl() - owner().getCostTtl()) ;
}
bool MiaStage::onPostStep(BwStepper& stepper) {
	owner().setCostTtl(0) ;
	owner().setBenefitTtl(0) ;
	m_maxValue = MiaState::DEFAULT_VALUE ;
	p_superiorState = NULL ;
	bool success = MiaStageBase::onPostStep(stepper) ;
	return success ;
}
void MiaStage::onActorStep(T_Part *pActor) {
	MiaState* pState = static_cast<MiaState*>(pActor) ;
	float value = pState->getValue() ;
	owner().setCostTtl(owner().getCostTtl() + pState->getCostTtl()) ;
	owner().setBenefitTtl(owner().getBenefitTtl() + pState->getBenefitTtl()) ;
	if(value > m_maxValue) {
		m_maxValue = value ;
		p_superiorState = pState ;
	}
	MiaStageBase::onActorStep(pActor) ;
}
inline MiaState* MiaStage::getOwner() { return static_cast<MiaState*>(p_owner) ; }
inline MiaState& MiaStage::owner() { return *static_cast<MiaState*>(p_owner) ; }
