/*Botworx AI - An Artificial Intelligence Framework
Copyright (C) 2004  Kurtis Fields. See BotworxAI_License.txt for details.
*/
#include "stdafx.h"

#include <bwmia/MiaMethod.h>
#include <bwmia/MiaTopic.h>
#include <bwmia/MiaIdentifier.h>
#include <bwmia/MiaAction.h>
#include <bwmia/MiaRule.h>
#include <bwmia/MiaBinderOps.h>
//
#include <bwmia/MiaEval.h>
#include <bwmia/MiaState.h>
//
//MiaAction
//
void MiaAction::create() {
	if(p_owner != NULL)
		p_rhs = p_owner->getRhs() ;
}
//
//MiaActions
//
void MiaActions::addAction(MiaAction* pAction) {
	bwAssert(pAction != this) ;
	m_actions.push_back(pAction) ;
}
MiaActions::~MiaActions() {
	MiaAction* pAction = NULL ;
	for(MiaActionIter iter = m_actions.begin() ; iter != m_actions.end() ; ++iter) {
		pAction = *iter ;
		delete pAction ;
	}
}
bool MiaActions::eval(MiaBinder& binder) {
	MiaAction* pAction = NULL ;
	for(MiaActionIter iter = m_actions.begin() ; iter != m_actions.end() ; ++iter) {
		pAction = *iter ;
		if(!pAction->eval(binder))
			return false ;
	}
	return true ;
}
//
//MiaSymbolAction
//
bool MiaSymbolAction::eval(MiaBinder& binder) {
	return getMethod(binder).onSymbol(asSymbol(getExpr())) ;
}
//
//MiaDestroyAction
//
bool MiaDestroyAction::eval(MiaBinder& binder) {
	MiaEval e(binder) ;
	MiaFact* pId = asFact(e.getSymbolVal(asSymbol(getExpr()))) ;
	MiaTopic* pTopic = getSelectSpace(binder).lookup(pId) ;
	pTopic->setIsCopyable(false) ;
	return true ;
}
//
//MiaDestroyAction
//
bool MiaPrintAction::eval(MiaBinder& binder) {
	MiaEval e(binder) ;
	if(getExpr() == NULL)
		k_printer() << binder ;
	else
	for(AiPair* pExpr = asPair(getExpr()) ; pExpr != NULL ; pExpr = pairCdr(pExpr)) {
		BwCell* pCell = e.eval(car(pExpr)) ;
		k_printer().printCell(pCell) ;
	}
	return true ;
}
//
//MiaRhs
//
void MiaRhs::create() {
	MiaActions::create() ;
	p_rhs = this ;
}
bool MiaRhs::eval(MiaBinder& binder) {
	MiaAction* pAction = NULL ;
	for(MiaActionIter iter = m_actions.begin() ; iter != m_actions.end() ; ++iter) {
		pAction = *iter ;
		if(!pAction->eval(binder))
			return false ;
	}
	return true ;
}
