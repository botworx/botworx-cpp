/*Botworx AI - An Artificial Intelligence Framework
Copyright (C) 2004  Kurtis Fields. See BotworxAI_License.txt for details.
*/
#include "stdafx.h"

#include <bwmia/MiaTopic.h>
#include <bwmia/MiaIdentifier.h>
#include <bwmia/MiaRule.h>
#include <bwmia/MiaMethod.h>

#include <bwmia/MiaState.h>
#include <bwmia/MiaCondition.h>
#include <bwmia/MiaAction.h>
#include <bwmia/MiaMakeAction.h>
#include <bwmia/MiaBinderOps.h>

//
//MiaRule
//
MiaRule::MiaRule(MiaRuleFactory *pFactory) {
	p_factory = pFactory ;
	m_partialSuccess = false ; 
	m_totalSuccess = true ; //used for testing total success
}
bool MiaRule::applyMatchSuccess(MiaBinder& binder) {
	m_partialSuccess = true ;
	MiaRhs* pMatchSuccessRhs = p_factory->getMatchSuccessRhs() ;
	if(pMatchSuccessRhs == NULL)
		return true ;
	//else
	bool success = pMatchSuccessRhs->eval(binder) ;
	if(!m_output.empty()) {
		getMind(binder).propose(m_output.get()) ;
		m_output.clear() ;
	}
	return success ;
}
bool MiaRule::applyMatchFailure(MiaBinder& binder) {
	MiaRhs* pMatchFailureRhs = p_factory->getMatchFailureRhs() ;
	if(pMatchFailureRhs == NULL)
		return true ;
	bool success = pMatchFailureRhs->eval(binder) ;
	if(!m_output.empty()) {
		getMind(binder).propose(m_output.get()) ;
		m_output.clear() ;
	}
	return success ;
}
bool MiaRule::applySuccess(MiaBinder& binder) {
	MiaRhs* pSuccessRhs = p_factory->getSuccessRhs() ;
	if(pSuccessRhs == NULL)
		return true ;
	bool success = pSuccessRhs->eval(binder) ;
	if(!m_output.empty()) {
		getMind(binder).propose(m_output.get()) ;
		m_output.clear() ;
	}
	return success ;
}
bool MiaRule::applyFailure(MiaBinder& binder) {
	MiaRhs* pFailureRhs = p_factory->getFailureRhs() ;
	if(pFailureRhs == NULL)
		return true ;
	bool success = pFailureRhs->eval(binder) ;
	if(!m_output.empty()) {
		getMind(binder).propose(m_output.get()) ;
		m_output.clear() ;
	}
	return success ;
}
bool MiaRule::eval(MiaBinder& binder) {
	bool success = true ;
	MiaLhs* pLhs = p_factory->getLhs() ;
	if(pLhs != NULL) {
		MiaBinder clone(binder) ;
		pLhs->eval(clone) ; //due to branching we can't use lhs's return value. hmmm.
		success = m_partialSuccess ; //success: at least one TOTAL match succeeded.
	}
	else {
		success = m_partialSuccess = m_totalSuccess = true ;
		applyMatchSuccess(binder) ;
	}
	//
	if(p_factory->getMatchSuccessRhs() != NULL) { //kind of a hack ... no matchRhs means test for total success.
		if(success) {
			applySuccess(binder) ;
		}
		else {
			applyFailure(binder) ;
		}
	}
	else {
		if(success && m_totalSuccess) {
			applySuccess(binder) ;
		}
		else {
			applyFailure(binder) ;
		}
	}
	return success ;
}
//
//Propose a new fact
void MiaRule::propose(MiaFact* pFact) {
	pFact->setIsCopyable(false) ;
	m_output.push_back(pFact) ;
}
//
//MiaRuleFactory
//
MiaRuleFactory::MiaRuleFactory() 
	: MiaFactory(NULL, MIA_TT_RULEFACTORY) {

	p_lhs = NULL ;
	p_successRhs = NULL ;
	p_matchSuccessRhs = NULL ;
	p_failureRhs = NULL ;
	p_matchFailureRhs = NULL ;
}
MiaRuleFactory::~MiaRuleFactory() {
	delete p_lhs ;
	delete p_successRhs ;
	delete p_matchSuccessRhs ;
	delete p_failureRhs ;
	delete p_matchFailureRhs ;
}
void MiaRuleFactory::purge() {
	MiaRuleFactory::~MiaRuleFactory() ;
	BW_USERFREE(this, MIA_TT_RULEFACTORY) ;
}
void MiaRuleFactory::produce(MiaRule* pRule) {
	pRule->MiaRule::~MiaRule() ; //destruct old
	new (pRule) MiaRule(this) ; //construct new
}
//
//MiaRuleKit
//
DEFINE_KITTYPE(MiaRuleKit) ;

TYPEINFO_NONE(MiaRuleKit) ;
NO_KITINFO(MiaRuleKit) ;

KITINFO("MiaRuleKit", MIA_KT_RULE, MiaRuleKit) ;
