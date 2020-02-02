/*Botworx AI - An Artificial Intelligence Framework
Copyright (C) 2004  Kurtis Fields. See BotworxAI_License.txt for details.
*/
#include "stdafx.h"

#include <bwai/AiMulti.h>

#include <bwmia/MiaTopic.h>
#include <bwmia/MiaIdentifier.h>
#include <bwmia/MiaState.h>
#include <bwmia/MiaAction.h>
#include <bwmia/MiaRule.h>

#include <bwmia/MiaMakeAction.h>
#include <bwmia/MiaAssertion.h>
#include <bwmia/MiaBinderOps.h>
//
//MiaMakeAction
//
bool MiaMakeAction::eval(MiaBinder& binder) {
	return MiaAction::eval(binder) ;
}
MiaFact* MiaMakeAction::makeSimple(MiaBinder& binder, AiPair* pExpr) {
	MiaAssertion assertion ;
	assertion.makeSimple(binder, pExpr) ;
	return assertion.output(binder, m_makerType) ;
}
MiaFact* MiaMakeAction::makeComplex(MiaBinder& binder, AiPair* pExpr) {
	AiPair* pIdExpr = asPair(car(pExpr)) ;
	MiaFact* pId = makeSimple(binder, pIdExpr) ;
	MiaAssertion assertion(pId) ;
	assertion.makeShorts(binder, asPair(cdr(pExpr))) ;
	assertion.output(binder, m_makerType) ;
	return pId ;
}
bool MiaMakeAction::makeTopic(MiaBinder& binder, AiPair* pExpr) {
	AiSymbol* pBindSymbol = NULL ;
	AiSymbol* pTypeSym = asSymbol(car(pExpr)) ;
	pExpr = pairCdr(pExpr) ; //skip type symbol
	if(isSymbol(car(pExpr))) { //optional binding symbol
		pBindSymbol = asSymbol(car(pExpr)) ;
		pExpr = pairCdr(pExpr) ; //skip binding symbol
	}
	//
	AiSymbol* pName = genSym(pTypeSym) ;
	MiaFact* pId = new MiaIdentifier(pName) ; //TODO:this won't work for proposals! see makeAssertion.
	MiaAssertion assertion(pId) ;
	assertion.makeShort(binder, SYM_TYPE, pTypeSym) ;
	assertion.makeShorts(binder, pExpr) ;
	//
	MiaTopic* pTopic = getSelectSpace(binder).lookup(assertion.getResults()) ;
	if(pTopic != NULL) { //TODO:only applies to goals?
		//pId = pTopic->getId() ;
		pId = pTopic->getSubject() ;
	}
	else
		assertion.output(binder, m_makerType) ;
	if(pBindSymbol != NULL)
		setVal(binder, pBindSymbol, pId) ;
	return true ;
}
//
//MiaSimpleMakeAction
//
bool MiaSimpleMakeAction::eval(MiaBinder& binder) {
	makeSimple(binder, asPair(getExpr())) ;
	return true ;
}
//
//MiaComplexMakeAction
//
bool MiaComplexMakeAction::eval(MiaBinder& binder) {
	makeComplex(binder, asPair(getExpr())) ;
	return true ;
}
//
//MiaTopicMakeAction
//
bool MiaTopicMakeAction::eval(MiaBinder& binder) {
	return makeTopic(binder, asPair(getExpr())) ;
}


