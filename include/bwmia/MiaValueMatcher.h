/*Botworx AI - An Artificial Intelligence Framework
Copyright (C) 2004  Kurtis Fields. See BotworxAI_License.txt for details.
*/
#ifndef _MiaValueMatcher_H
#define _MiaValueMatcher_H

#include "MiaMatcherBase.h"
#include <bwmia/MiaTopic.h>
#include <bwmia/MiaIdentifier.h>
#include <bwmia/MiaPattern.h>
#include <bwmia/MiaState.h>
#include <bwmia/MiaBinderOps.h>

class MiaValueMatcher : public MiaMatcherBase {
public:
	MiaValueMatcher(MiaBinder& binder, MiaFactoid& result, MiaPattern& pattern)
		: MiaMatcherBase(binder, result, pattern) {
	}
	AiPair* seekValues(BwCell* pVal) {
		MiaFact* pSubject = result().getSubject() ;
		//bwAssert(isFact(pSubject)) ;
		bwAssert(ofFact(pSubject)) ;

		MiaTopic* pTopic = getSelectSpace(binder()).lookup(pSubject) ;
		if(pTopic == NULL)
			return NULL ;
		//else
		AiPair* pMatchingValues = NULL ;
		MiaSearch search(result().getSubject(), result().getLink(), pVal) ;
		search.setResultType(SEARCHRESULT_VALUE) ;
		pTopic->seek(search) ;
		pMatchingValues = search.getResults() ;

		return pMatchingValues ;
	}
	bool matchValue(BwCell* pVal) {
		MiaFact* pSubject = result().getSubject() ;
		//bwAssert(isFact(pSubject)) ;
		bwAssert(ofFact(pSubject)) ;

		MiaTopic* pTopic = getSelectSpace(binder()).lookup(pSubject) ;
		if(pTopic == NULL)
			return false ;
		//else
		MiaPattern pattern(result().getSubject(), result().getLink(), pVal) ;
		return pTopic->match(pattern) ;
	}
	BwCell* getLogicVal(AiSymbol* pSymbol) {
		BwCell* pVal = MiaMatcherBase::getLogicVal(pSymbol) ;
		if(pVal != UNBOUND)
			return pVal ;
		//else
		//if not bound bind
		if(result().getValue() != NIL) { //handling case of a posted fact.
			pVal = result().getValue() ;
			p_binder->setVal(pSymbol, pVal) ;
			return pVal ;
		}
		//else
		AiPairPtr pMatchingValues = seekValues(NIL) ;
		if(pMatchingValues != NULL) {
			if(pMatchingValues->p_right == NULL)
				pVal = car(pMatchingValues.get()) ;
			else
				pVal = new AiMulti(pMatchingValues.get()) ;
			p_binder->setVal(pSymbol, pVal) ;
			return pVal ;
		}
		//else
		return pVal ; //returning unbound by default
	}
	BwCell* getValueVal(AiSymbol* pSymbol) {
		BwCell* pVal = NULL ;
		switch(pSymbol->getSymType()) {
			case SYMTYP_LOGIC :
				pVal = getLogicVal(pSymbol) ;
				break ;
			case SYMTYP_NORMAL : {
				pVal = getGlobalVal(pSymbol) ;
				bwAssert(pVal != UNBOUND) ;
				AiPairPtr pVals = seekValues(pVal) ;
				if(pVals != NULL)
					return car(pVals.get()) ;
				//return matchValue(pVal) ;
								}
				break ;
			case SYMTYP_PROPERTY :
				pVal = getPropertyVal(pSymbol) ;
				break ;
		}
		return pVal ;
	}
	bool matchBoundValue(BwCell* pExpr) {
		bool success = false ;
		AiSymbol* pSymbol = asSymbol(pExpr) ;
		BwCell* pVal = NULL ;
		BwCell* pMatchVal = NULL ;

		switch(pSymbol->getSymType()) {
			case SYMTYP_LOGIC : {
				pVal = p_binder->getVal(pSymbol) ;
				/*AiPairPtr pVals = seekValues(pVal) ;
				return (pVals != NULL) ;*/
				return matchValue(pVal) ;
								}
				break ;
			case SYMTYP_NORMAL : {
				pVal = getGlobalVal(pSymbol) ;
				/*AiPairPtr pVals = seekValues(pVal) ;
				return (pVals != NULL) ;*/
				return matchValue(pVal) ;
								}
				break ;
			case SYMTYP_PROPERTY :
				pVal = getPropertyVal(pSymbol) ;
				success = pVal == pExpr ;
				break ;
		}
		return success ;
	}
	bool matchUnboundValue(BwCell* pExpr) {
		BwCell* pVal = NULL ;
		AiSymbol* pSymbol = NULL ;
		bool success = false ;
		ThingTT cellType = getTT(pExpr) ;
		switch(cellType) {
			case TT_SYMBOL :
				pSymbol = asSymbol(pExpr) ;
				pVal = getValueVal(pSymbol) ;
				if(pVal == UNBOUND)
					break ; //success = false
				success = true ;
				break ;
			default :
				bwAssert(0) ;
		}
		result().setValue(pVal) ;
		return success ;
	}
	bool matchConstantValue(BwCell* pExpr) {
		BwCell* pVal = NULL ;
		AiSymbol* pSymbol = NULL ;
		bool success = false ;
		ThingTT cellType = getTT(pExpr) ;
		switch(cellType) {
			case TT_SYMBOL :
				pSymbol = asSymbol(pExpr) ;
				pVal = getValueVal(pSymbol) ; //this is the value to match against
				if(pVal == UNBOUND)
					break ; //success = false
				//else
				if(result().getValue() == pVal)
					success = true ;
				break ;
			default :
				bwAssert(0) ;
		}
		return success ;
	}
	bool matchExpr(AiPair* pRest) {
		bool success = false ;
		BwCell* pExpr = car(pRest) ;
		AiSymbol* pSymbol =  asSymbol(pExpr) ;

		if(result().getValue() != NIL)
			success = matchConstantValue(pExpr) ;
		else
		if(pSymbol->isLogic()) {
			if(p_binder->exists(pSymbol))
				success = matchBoundValue(pExpr) ;
			else
				success = matchUnboundValue(pExpr) ;
		}
		else
		success = matchBoundValue(pExpr) ;

		return success ;
	}
} ;

#endif //_MiaValueMatcher_H
