/*Botworx AI - An Artificial Intelligence Framework
Copyright (C) 2004  Kurtis Fields. See BotworxAI_License.txt for details.
*/
#include "stdafx.h"

#include <bwmia/MiaMethod.h>
#include <bwmia/MiaRule.h>
#include <bwmia/MiaMind.h>
//TODO:Eliminate dependency on MiaState!!!
#include <bwmia/MiaState.h>
//
#include <bwai/AiInt.h>

void MiaMethod::purge() {
	MiaMethod::~MiaMethod() ;
#if AI_OPTION_POOLING
	k_method().release(this) ;
#else
	BW_USERFREE(this, MIA_TT_METHOD) ;
#endif
}
MiaMethod::MiaMethod(MiaMind& mind) : BwCell(MIA_TT_METHOD), p_mind(&mind), p_selectSpace(&mind) {
	m_binder.setMethod(this) ;
}

MiaMethod::MiaMethod(MiaMind& mind, MiaMethodFactory* pFactory, MiaBinder& binder, MiaFact* pFact)
	: BwCell(MIA_TT_METHOD), p_mind(&mind), p_selectSpace(&mind), p_factory(pFactory), p_fact(pFact){
	m_binder.copy(binder) ;
	m_binder.setMethod(this) ;
	setStatus(STATUS_BUSY) ;
}
//
//MiaMethod
//
bool MiaMethod::evalRule(MiaRuleFactory* pFactory) {
	pFactory->produce(&m_rule) ;
	bool success = m_rule.eval(*getBinder()) ;
	return success ;
}
bool MiaMethod::eval() {
	bool success = false ;
	MiaRuleFactory* pFactory = NULL ;
	for(AiPair* pExpr = p_factory->getRuleFactories() ; pExpr != NIL ; pExpr = pairCdr(pExpr)) {
		pFactory = asRuleFactory(car(pExpr)) ;
		success = evalRule(pFactory) ;
		if(!isBusy())
			break ;
	}
	return true ;
}
//TODO: Eliminate and replace with rule actions ...
bool MiaMethod::onSymbol(AiSymbol* pSymbol) {
	MiaState* pState = static_cast<MiaState*>(p_mind) ;
	if(pSymbol == SYM_BREAK)
		bwAssert(0) ;
	else if(pSymbol == SYM_RETURN) {
		setStatus(STATUS_RETURN) ;
		return false ;
	}
	else if(pSymbol == SYM_FAIL)
		return pState->fail() ;
	else if(pSymbol == SYM_MONITOR)
		p_mind->setIsMonitored(true) ;
	else if(pSymbol == SYM_HALT) {
		pState->setIsSolution(true) ;
		p_mind->halt() ;
	}
	else if(pSymbol == SYM_SOLUTION)
		pState->setIsSolution(true) ;
	else {
		pState->setNextMode(pSymbol) ;
		return false ;
	}
	return true ;
}
//
void MiaMethod::setPropertyVal(AiSymbol* pSymbol, BwCell* pVal) {
	bwAssert(0) ; //implement
}
BwCell* MiaMethod::getPropertyVal(AiSymbol* pSymbol) {
	if (pSymbol == PSYM_THOUGHT)
		return getFact() ;
	//else
	//TODO:p_mind?
	return getSelectSpace().getPropertyVal(pSymbol) ;
}
//
void MiaMethod::call(MiaFactoid& factoid) {
	factoid.setValue(SYM_UNKNOWN) ;
	factoid.setTruth(0) ;
	MiaFact* pFact = factoid.createFact() ;
	//
	p_mind->p_domain->produceMethods(getMind(), pFact) ;
}

//
//MiaMethodFactory
//
void MiaMethodFactory::purge() {
	MiaMethodFactory::~MiaMethodFactory() ;
	BW_USERFREE(this, MIA_TT_METHODFACTORY) ;
}
MiaMethodFactory::MiaMethodFactory(MiaDomain& domain, AiSymbol* pSymbol, AiPair* pSignature)
: MiaFactory(pSymbol, MIA_TT_METHODFACTORY) {
	p_domain = &domain ;
	m_triggerType = TRIGGER_ASSERTION ;
	p_signature = pSignature ;
	if(pSignature)
		processSignature(pSignature) ;
}
void MiaMethodFactory::processSignature(AiPair* pSignature) {
	AiPair* pTail = asPair(cddr(pSignature)) ;
	if(cdr(pTail) == NULL)
		return ;
	//else
	AiSymbol* pLinkSym = asSymbol(cadr(pSignature)) ;
	MiaIdentifier* pLinkId = internId(pLinkSym) ;
	//
	AiInt* pTruth = asInt(cadr(pTail)) ;
	switch(pTruth->m_value) {
		case -1 :
			m_triggerType = TRIGGER_RETRACTION ;
			break ;
		case 0 :
			m_triggerType = TRIGGER_UNKNOWN ;
			pLinkId->setHasFillers(true) ;
			break ;
		case 1 :
			m_triggerType = TRIGGER_ASSERTION ;
			break ;
	}
}
MiaMethod* MiaMethodFactory::produce(MiaMind& mind, MiaBinder& binder, MiaFact* pFact) {
	MiaMethod* pMethod = new MiaMethod(mind, this, binder, pFact) ;
	return pMethod ;
}
MiaRuleFactory* MiaMethodFactory::addRuleFactory(MiaRuleFactory* pFactory) {
	AiPair* pFactories = getRuleFactories() ;
	AiPair* pFactoryLink = consa(pFactory) ;
	if(isNil(pFactories))
		pFactories = pFactoryLink ;
	else
		pFactories = appendList(pFactories, pFactoryLink) ;
	p_ruleFactories = pFactories ;
	return pFactory ;
}
//
// MiaMethodKit Meta
//
DEFINE_KITTYPE(MiaMethodKit) ;

TYPEINFO_NONE(MiaMethodKit) ;
NO_KITINFO(MiaMethodKit) ;

KITINFO("MiaMethodKit", MIA_KT_METHOD, MiaMethodKit) ;
