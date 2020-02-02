/*Botworx AI - An Artificial Intelligence Framework
Copyright (C) 2004  Kurtis Fields. See BotworxAI_License.txt for details.
*/
#ifndef _MiaLinkMatcher_H
#define _MiaLinkMatcher_H

#include "MiaMatcherBase.h"
#include <bwmia/MiaValueMatcher.h>

class MiaLinkMatcher : public MiaMatcherBase {
public:
	MiaLinkMatcher(MiaBinder& binder, MiaFactoid& result, MiaPattern& pattern)
		: MiaMatcherBase(binder, result, pattern) {
	}
	//TODO:this looks like it can go down into matcher class.
	BwCell* getLogicVal(AiSymbol* pSymbol) {
		bwAssert(0) ; //TODO:is this a dead method?
		BwCell* pVal = MiaMatcherBase::getLogicVal(pSymbol) ;
		//if not bound bind
		/*if(pVal == UNBOUND)
			bwAssert(0) ;
		else
			return pVal ;*/
		//else
		return NULL ;
	}
	//TODO:this looks like it can go down into matcher class.
	MiaFact* getLinkVal(AiSymbol* pSymbol) {
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
	//here is where things start to deviate.
	bool matchBlankLink(BwCell* pExpr) {
		MiaFact* pVal = NULL ;
		AiSymbol* pSymbol = NULL ;
		bool success = false ;
		ThingTT cellType = getTT(pExpr) ;
		switch(cellType) {
			case TT_SYMBOL :
				pSymbol = asSymbol(pExpr) ;
				pVal = getLinkVal(pSymbol) ;
				if(pVal == UNBOUND)
					break ; //success = false
				//else
				result().setLink(pVal) ;
				success = true ;
				break ;
			default :
				bwAssert(0) ;
		}
		return success ;
	}
	bool matchLink(BwCell* pExpr) {
		MiaFact* pVal = NULL ;
		AiSymbol* pSymbol = NULL ;
		bool success = false ;
		ThingTT cellType = getTT(pExpr) ;
		switch(cellType) {
			case TT_SYMBOL :
				pSymbol = asSymbol(pExpr) ;
				pVal = getLinkVal(pSymbol) ;
				if(pVal == UNBOUND)
					break ; //success = false
				if(result().getLink() == pVal)
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
		if(result().getLink() != NIL)
			success = matchLink(pExpr) ;
		else
			success = matchBlankLink(pExpr) ;

		if(success) {
			MiaValueMatcher valMatcher(binder(), result(), pattern()) ;
			success = valMatcher.matchExpr(pairCdr(pRest)) ;
			return success ;
		}
		return success ;
	}
} ;

#endif //_MiaLinkMatcher_H
