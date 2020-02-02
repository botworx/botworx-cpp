/*Botworx AI - An Artificial Intelligence Framework
Copyright (C) 2004  Kurtis Fields. See BotworxAI_License.txt for details.
*/
#include "stdafx.h"

#include <bwai/AiMulti.h>

#include <bwai/AiComparison.h>

#include <bwmia/MiaTopic.h>
#include <bwmia/MiaIdentifier.h>
#include <bwmia/MiaState.h>
#include <bwmia/MiaCondition.h>
#include <bwmia/MiaRule.h>
#include <bwmia/MiaBinderOps.h>
#include <bwmia/MiaEval.h>
//
//MiaCondition
//
void MiaCondition::create() {
	if(p_owner != NULL)
		p_lhs = p_owner->getLhs() ;
}
//
//MiaSymbolCondition
//
//TODO:?:I know this is odd, but ... need some way to break inside conditions.
bool MiaSymbolCondition::eval(MiaBinder& binder) {
	return getMethod(binder).onSymbol(asSymbol(getExpr())) ;
}
//
//MiaConditions
//
MiaConditions::~MiaConditions() {
	MiaCondition* pCondition = NULL ;
	for(MiaConditionIter iter = m_conditions.begin() ; iter != m_conditions.end() ; ++iter) {
		pCondition = *iter ;
		delete pCondition ;
	}
}
void MiaConditions::addCondition(MiaCondition* pCondition) {
	bwAssert(pCondition != this) ;
	m_conditions.push_back(pCondition) ;
}
bool MiaConditions::eval(MiaBinder& binder) {
	bool success = true ;
	MiaCondition* pCondition = NULL ;
	for(MiaConditionIter iter = m_conditions.begin() ; iter != m_conditions.end() ; ++iter) {
		pCondition = *iter ;
		success = pCondition->eval(binder) ;
		if(!success)
			break ;
	}
	return success ;
}
//
//MiaFramedConditions
//
MiaFramedConditions::MiaFramedConditions(MiaConditions* pOwner, AiPair* pExpr)
	: MiaConditions(pOwner, pairCdr(pExpr)) {
		p_stateExpr = car(pExpr) ;
}
bool MiaFramedConditions::eval(MiaBinder& binder) {
	bool success = true ;
	MiaSpace* pOldSpace = &getSelectSpace(binder) ;
	MiaIdentifier* pId = asIdentifier(getVal(binder, asSymbol(getStateExpr()))) ;
	//
	if(pId == NULL)
		return false ;
	//
	setSelectSpace(binder, pId->getSpace()) ;
	success = MiaConditions::eval(binder) ;
	setSelectSpace(binder, pOldSpace) ;
	return success ;
}
//
//MiaNegation
//
bool MiaNegation::eval(MiaBinder& binder) {
	return ! MiaConditions::eval(binder) ;
}
//
//MiaDisjunction
//
bool MiaDisjunction::eval(MiaBinder& binder) {
	bool success = false ;
	MiaCondition* pCondition = NULL ;
	for(MiaConditionIter iter = m_conditions.begin() ; iter != m_conditions.end() ; ++iter) {
		pCondition = *iter ;
		success |= pCondition->eval(binder) ;
	}
	return success ;
}
//
//MiaMatchTest
//
bool MiaMatchTest::eval(MiaBinder& binder) {
	bool success = true ;
	MiaFactoid result ;
	success = m_pattern.match(binder, result) ;
	MiaMethod& method = getMethod(binder) ;
	//f6:newstuff:faults
	if(!success && asIdentifier(m_pattern.getLink())->hasFillers()) {
		method.call(result) ;
	}
	//
	#if AI_OPTION_INSTRUMENT
	MiaMind& mind = getMind(binder) ;
	if(mind.isMonitored()) {
		MiaPrinter& logger = mind.logger() ;
		logger << method.getMethodFactory()->getSymbol()->getString() ;
		logger << ":  Evaluated  :  " << *getExpr() ;
		if(success)
			logger << " : TRUE" << endl ;
		else
			logger << " : FALSE" << endl ;
		logger << "\t" << binder << endl ;
	}
	#endif //AI_OPTION_INSTRUMENT
	return success ;
}
//
//MiaRelationalTest
//
bool MiaRelationalTest::eval(MiaBinder& binder) {
	bool success = true ;
	MiaEval e(binder) ;
	BwCell* pThis = e.eval(car(asPair(getExpr()))) ;
	BwCell* pThat = e.eval(caddr(asPair(getExpr()))) ;
	AiComparison comparison(pThis, pThat) ;
	switch(m_type) {
		case TYPE_EQ :
			success = comparison.eq() ;
		break ;
		case TYPE_NEQ :
			success = comparison.ne() ;
		break ;
		case TYPE_LT :
			success = comparison.lt() ;
		break ;
		case TYPE_LE :
			success = comparison.le() ;
		break ;
		case TYPE_GT :
			success = comparison.gt() ;
		break ;
		case TYPE_GE :
			success = comparison.ge() ;
		break ;
	}
	return success ;
}
//
//MiaLhs
//
void MiaLhs::create() {
	MiaConjunction::create() ;
	p_lhs = this ;
}
bool MiaLhs::eval(MiaBinder& binder) {
	return eval2(binder, m_conditions.begin()) ;
}
bool MiaLhs::eval2(MiaBinder& binder, MiaConditionIter iter) {
	bool success = true ;
	if(iter == m_conditions.end()) { //we made it successfully to the end.
		getRule(binder).applyMatchSuccess(binder) ;
		return success ;
	}
	//else
	MiaCondition* pCondition = *iter ;
	success = pCondition->eval(binder) ;
	if(!success) {
		getRule(binder).applyMatchFailure(binder) ; //f6:review:this may be too expensive. not worth it.
		if(++iter == m_conditions.end())
			getRule(binder).setTotalSuccess(false) ;
		return success ;
	}
	//else
	if(binder.isMulti()) {
		return eval3(binder, ++iter) ;
	}
	//else
	return eval2(binder, ++iter) ;
}
bool MiaLhs::eval3(MiaBinder& binder, MiaConditionIter iter) {
	bool multiSuccess = true ;
	int multiNdx = binder.m_multiNdx ;
	BwCell* pVal = binder.m_bindings[multiNdx].getValue() ;
	for(AiPair* pList = asMulti(pVal)->getList() ; pList != NULL ; pList = pairCdr(pList)) {
		MiaBinder clone(binder) ;
		clone.m_isMulti = false ;
		clone.m_bindings[multiNdx].p_value = car(pList) ;
		multiSuccess |= eval2(clone, iter) ;
	}
	return multiSuccess ;
}
