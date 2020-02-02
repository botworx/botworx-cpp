/*Botworx AI - An Artificial Intelligence Framework
Copyright (C) 2004  Kurtis Fields. See BotworxAI_License.txt for details.
*/
#include "stdafx.h"

#include <bwmia/MiaSelect.h>
#include <bwmia/MiaState.h>
#include <bwmia/MiaFrame.h>
#include <bwai/AiMulti.h>
#include <bwmia/MiaBinderOps.h>

//
//MiaTopicSelect
//
void MiaTopicSelect::create() {
	AiPair* pExpr = asPair(getExpr()) ;
	p_bindSymbol = asSymbol(car(pExpr)) ;
	pExpr = pairCdr(pExpr) ; //skip binding symbol
	for(; pExpr != NULL ; pExpr = pairCdr(pExpr)) {
		MiaPattern pattern(cons(LSYM_WILDCARD, car(pExpr))) ;
		m_patterns.push_back(pattern) ;
	}
}
bool MiaTopicSelect::eval(MiaBinder& binder) {
	AiList subjects = getSelectSpace(binder).findSubjects(m_patterns) ;
	BwCell* pVal = NULL ;
	if(!subjects.empty()) { //TODO:only applies to goals?
		if(!subjects.hasTail())
			pVal = car(subjects.get()) ;
		else
			pVal = new AiMulti(subjects.get()) ;
	}
	else
		return false ;
	if(p_bindSymbol != NULL)
		setVal(binder, p_bindSymbol.get(), pVal) ;
	return true ;
}
//
//MiaSpaceSelect
//
void MiaSpaceSelect::create() {
	AiPair* pExpr = asPair(getExpr()) ;
	p_bindSymbol = asSymbol(car(pExpr)) ;
	pExpr = pairCdr(pExpr) ; //skip binding symbol
	for(; pExpr != NULL ; pExpr = pairCdr(pExpr)) {
		MiaPattern pattern(cons(LSYM_WILDCARD, car(pExpr))) ;
		m_patterns.push_back(pattern) ;
	}
}
bool MiaSpaceSelect::eval(MiaBinder& binder) {
	bool success = true ;
	if(p_bindSymbol == LSYM_WILDCARD) {
		MiaSpace* pOldSpace = &getSelectSpace(binder) ;
		MiaFrameContainer& frames = k_core().getFrames() ;
		for(MiaFrameIter iter = frames.begin() ; iter != frames.end() ; ++iter) {
			setSelectSpace(binder, *iter) ;
			MiaConditions::eval(binder) ;
		}
		setSelectSpace(binder, pOldSpace) ;
	}
	else
		bwAssert(0) ;
	return success ;
}
