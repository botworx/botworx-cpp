/*Botworx AI - An Artificial Intelligence Framework
Copyright (C) 2004  Kurtis Fields. See BotworxAI_License.txt for details.
*/
#include "stdafx.h"

#include <bwai/AiMulti.h>

#include <bwmia/MiaTopic.h>
#include <bwmia/MiaIdentifier.h>

#include <bwmia/MiaAsserter.h>
#include <bwmia/MiaLinkAsserter.h>
#include <bwmia/MiaValueAsserter.h>
#include <bwmia/MiaTruthAsserter.h>

#include <bwmia/MiaState.h>

#include <bwmia/MiaAssertion.h>
#include <bwmia/MiaBinder.h>
//
//MiaAssertion
//
bool MiaAssertion::makeShort(MiaBinder& binder, AiPair* pExpr) {
	MiaFactoid result(*this) ;

	MiaLinkAsserter linkAsserter(binder, result) ;
	bool success = linkAsserter.assertExpr(pExpr) ;
	if(!success) return false ;
	//
	addResult(result.createFact()) ;
	return true ;
}
bool MiaAssertion::makeShort(MiaBinder& binder, AiSymbol* pLinkSym, BwCell* pVal) {
	AiPair* pCons = new AiPair(pVal, NIL) ;
	AiPairPtr pExpr = new AiPair(pLinkSym, pCons) ;
	return makeShort(binder, pExpr.get()) ;
}
bool MiaAssertion::makeShorts(MiaBinder& binder, AiPair* pExpr) {
	AiPair* pShort = NULL ;
	for(; pExpr != NIL ; pExpr = pairCdr(pExpr)) {
		pShort = pairCar(pExpr) ;
		makeShort(binder, pShort) ;
	}
	return true ;
}
bool MiaAssertion::makeSimple(MiaBinder& binder, AiPair* pExpr) {
	MiaAsserter asserter(binder, *this) ;
	bool success = asserter.assertExpr(pExpr) ;
	if(!success) return false ;
	//
	addResult(createFact()) ;
	return true ;
}
MiaFact* MiaAssertion::output(MiaBinder& binder, makerType type) {
	switch(type) {
		case MAKER_TEMPORARY :
			postTemps(binder) ;
			break ;
		case MAKER_PROPOSAL :
			proposeResults(binder) ;
			break ;
		case MAKER_RETRACTION :
			retractResults(binder) ;
			break ;
		default :
			postResults(binder) ;
	}
	return asFact(car(getResults())) ;
}
void MiaAssertion::postResults(MiaBinder& binder) {
	MiaFact* pFact = NULL ;
	for(AiPair* pResults = getResults() ; pResults != NIL ; pResults = pairCdr(pResults)) {
		pFact = asFact(car(pResults)) ;
		getMind(binder).post(pFact) ;
	}
}
void MiaAssertion::postTemps(MiaBinder& binder) {
	MiaFact* pFact = NULL ;
	for(AiPair* pResults = getResults() ; pResults != NIL ; pResults = pairCdr(pResults)) {
		pFact = asFact(car(pResults)) ;
		pFact->setIsCopyable(false) ;
		getMind(binder).post(pFact) ;
	}
}
void MiaAssertion::retractResults(MiaBinder& binder) {
	MiaFact* pFact = NULL ;
	for(AiPair* pResults = getResults() ; pResults != NIL ; pResults = pairCdr(pResults)) {
		pFact = asFact(car(pResults)) ;
		pFact->setTruth(-1) ;
		getMind(binder).post(pFact) ;
	}
}
void MiaAssertion::proposeResults(MiaBinder& binder) {
	MiaFact* pFact = NULL ;
	for(AiPair* pResults = getResults() ; pResults != NIL ; pResults = pairCdr(pResults)) {
		pFact = asFact(car(pResults)) ;
		getRule(binder).propose(pFact) ; //maybe just send the list?
	}
}