/*Botworx AI - An Artificial Intelligence Framework
Copyright (C) 2004  Kurtis Fields. See BotworxAI_License.txt for details.
*/
#ifndef _MiaValueAsserter_H
#define _MiaValueAsserter_H

#include "MiaAsserterBase.h"

#include <bwai/AiXString.h>
#include <bwmia/MiaTruthAsserter.h>

class MiaValueAsserter : public MiaAsserterBase {
public:
	MiaValueAsserter(MiaBinder& binder, MiaFactoid& result)
		: MiaAsserterBase(binder, result) {
	}
	class MiaValueAsserterExpander {
	public:
		MiaValueAsserterExpander(MiaValueAsserter *pUser) : p_user(pUser) {
		}
		BwCell* operator ( ) (BwCell* pExpr) const
		{
			BwCell* pVal = NULL ;
			ThingTT cellType = getTT(pExpr) ;
			switch(cellType) {
				case TT_SYMBOL : {
					AiSymbol* pSymbol = asSymbol(pExpr) ;
					pVal = getVal(p_user->binder(), pSymbol) ;
					break ;
				}
				case TT_STRING :
				case TT_XSTRING :
				case TT_INT :
				case TT_FLOAT :
				default :
					bwAssert(0) ;
			}
			return pVal ;
		}
		//
		MiaValueAsserter* p_user ;
	};
	bool assertExpr(AiPair* pExpr) {
		BwCell* pVal = NULL ;
		BwCell* pHead = car(pExpr) ;
		AiSymbol* pSymbol = NULL ;
		bool success = false ;
		ThingTT cellType = getTT(pHead) ;
		switch(cellType) {
			case TT_SYMBOL :
				pSymbol = asSymbol(pHead) ;
				pVal = getVal(binder(), pSymbol) ;
				if(pVal == UNBOUND)
					break ; //success = false
				//else
				success = true ;
				break ;
			case TT_PAIR :
				pVal = evalPair(asPair(pHead)) ;
				success = true ;
				break ;
			case TT_XSTRING : {
				pVal = AiXString_expand(asXString(pHead), MiaValueAsserterExpander(this)) ;
				success = true ;
				break ;
			}
			case TT_STRING :
			case TT_INT :
			case TT_FLOAT : {
				pVal = pHead ;
				success = true ;
				break ;
			}
			default :
				bwAssert(0) ;
		}
		result().setValue(pVal) ;
		if(success) {
			AiPair* pTruthExpr = pairCdr(pExpr) ;
			if(pTruthExpr != NIL) {
				MiaTruthAsserter truthAsserter(binder(), result()) ;
				success = truthAsserter.assertExpr(pTruthExpr) ;
				return success ;
			}
		}
		return success ;
	}
} ;

#endif //_MiaValueAsserter_H
