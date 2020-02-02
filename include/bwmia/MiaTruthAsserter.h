/*Botworx AI - An Artificial Intelligence Framework
Copyright (C) 2004  Kurtis Fields. See BotworxAI_License.txt for details.
*/
#ifndef _MiaTruthAsserter_H
#define _MiaTruthAsserter_H

#include "MiaAsserterBase.h"
#include <bwmia/MiaBinderOps.h>

#include <bwai/AiMath.h>

class MiaTruthAsserter : public MiaAsserterBase {
public:
	MiaTruthAsserter(MiaBinder& binder, MiaFactoid& result)
		: MiaAsserterBase(binder, result) {
	}
	class MiaTruthAsserterExpander {
	public:
		MiaTruthAsserterExpander(MiaTruthAsserter *pUser) : p_user(pUser) {
		}
		BwCell* operator ( ) (BwCell* pExpr) const
		{
			BwCell* pVal = NULL ;
			ThingTT cellType = getTT(pExpr) ;
			switch(cellType) {
				case TT_SYMBOL : {
					AiSymbol* pSymbol = asSymbol(pExpr) ;
					pVal = getVal(p_user->binder(), pSymbol) ;
					}
					break ;
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
		MiaTruthAsserter* p_user ;
	};
	bool assertExpr(AiPair* pExpr) {
		BwCell* pVal = NULL ;
		BwCell* pHead = car(pExpr) ;
		AiSymbol* pSymbol = NULL ;
		bool success = false ;
		ThingTT cellType = getTT(pHead) ;
		switch(cellType) {
			case TT_PAIR :
				pVal = evalPair(asPair(pHead)) ;
				success = true ;
				break ;
			case TT_SYMBOL :
				pSymbol = asSymbol(pHead) ;
				pVal = getVal(binder(), pSymbol) ;
				if(pVal == UNBOUND)
					break ; //success = false
				//else
				success = true ;
				break ;
			case TT_XSTRING : {
				pVal = AiXString_expand(asXString(pHead), MiaTruthAsserterExpander(this)) ;
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
		AiMath math(pVal) ;
		result().setTruth(math.getFloat()) ;
		return success ;
	}
} ;

#endif //_MiaTruthAsserter_H
