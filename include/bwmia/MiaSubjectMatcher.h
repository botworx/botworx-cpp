/*Botworx AI - An Artificial Intelligence Framework
Copyright (C) 2004  Kurtis Fields. See BotworxAI_License.txt for details.
*/
#ifndef _MiaSubjectMatcher_H
#define _MiaSubjectMatcher_H

#include "MiaMatcherBase.h"

#include <bwmia/MiaLinkMatcher.h>

class MiaSubjectMatcher : public MiaMatcherBase {
public:
	MiaSubjectMatcher(MiaBinder& binder, MiaFactoid& result, MiaPattern& pattern)
		: MiaMatcherBase(binder, result, pattern) {
	}

	BwCell* getLogicVal(AiSymbol* pSymbol) {
		BwCell* pVal = MiaMatcherBase::getLogicVal(pSymbol) ;
		if(pVal != UNBOUND)
			return pVal ;
		//else
		//if not bound bind
		if(result().getSubject() != NIL) { //handling case of a posted fact.
			pVal = result().getSubject() ;
			p_binder->setVal(pSymbol, pVal) ;
			return pVal ;
		}
		//else
		return pVal ; //returning unbound by default
	}
	MiaFact* getSubjectVal(AiSymbol* pSymbol) {
		MiaFact* pVal = NULL ;
		switch(pSymbol->getSymType()) {
			case SYMTYP_LOGIC :
				pVal = asFact(getLogicVal(pSymbol)) ;
				break ;
			case SYMTYP_NORMAL :
				pVal = asFact(getGlobalVal(pSymbol)) ;
				break ;
			case SYMTYP_PROPERTY :
				pVal = asFact(getPropertyVal(pSymbol)) ;
				break ;
		}
		return pVal ;
	}
	bool matchBlankSubject(BwCell* pExpr) {
		MiaFact* pVal = NULL ;
		AiSymbol* pSymbol = NULL ;
		bool success = false ;
		ThingTT cellType = getTT(pExpr) ;
		switch(cellType) {
			case TT_SYMBOL :
				pSymbol = asSymbol(pExpr) ;
				pVal = getSubjectVal(pSymbol) ;
				if(pVal != UNBOUND)
					success = true ;
				else
					success = false ;
				//else
				result().setSubject(pVal) ;
				break ;
			default :
				bwAssert(0) ;
		}
		return success ;
	}
	bool matchSubject(BwCell* pExpr) {
		MiaFact* pVal = NULL ;
		AiSymbol* pSymbol = NULL ;
		//bool success = false ;
		bool success = true ;
		ThingTT cellType = getTT(pExpr) ;
		switch(cellType) {
			case TT_SYMBOL :
				pSymbol = asSymbol(pExpr) ;
				pVal = getSubjectVal(pSymbol) ;
				if(pVal == UNBOUND)
					break ; //success = false
				if(result().getSubject() == pVal)
					success = true ;
				break ;
			default :
				bwAssert(0) ;
		}
		return success ;
	}
	bool matchExpr(AiPair* pRest) {
		bool success = false ;
		BwCell* pExpr =  car(pRest) ;
		if(result().getSubject() != NIL)
			success = matchSubject(pExpr) ;
		else {
			success = matchBlankSubject(pExpr) ;
		}

		if(success) {
			MiaLinkMatcher linkMatcher(binder(), result(), pattern()) ;
			success = linkMatcher.matchExpr(pairCdr(pRest)) ;
			return success ;
		}
		return success ;
	}

} ;

#endif //_MiaSubjectMatcher_H
