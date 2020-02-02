/*Botworx AI - An Artificial Intelligence Framework
Copyright (C) 2004  Kurtis Fields. See BotworxAI_License.txt for details.
*/
#ifndef _MiaLinkAsserter_H
#define _MiaLinkAsserter_H

#include "MiaAsserterBase.h"

#include <bwmia/MiaValueAsserter.h>

class MiaLinkAsserter : public MiaAsserterBase {
public:
	MiaLinkAsserter(MiaBinder& binder, MiaFactoid& result)
		: MiaAsserterBase(binder, result) {
	}
	bool assertExpr(AiPair* pExpr) {
		MiaFact* pVal = NULL ;
		BwCell* pHead = car(pExpr) ;
		AiSymbol* pSymbol = NULL ;
		bool success = false ;
		ThingTT cellType = getTT(pHead) ;
		switch(cellType) {
			case TT_SYMBOL :
				pSymbol = asSymbol(pHead) ;
				pVal = asFact(getVal(binder(), pSymbol)) ;
				if(pVal == UNBOUND)
					break ; //success = false
				//else
				result().setLink(pVal) ;
				success = true ;
				break ;
			default :
				bwAssert(0) ;
		}
		if(success) {
			MiaValueAsserter valAsserter(binder(), result()) ;
			success = valAsserter.assertExpr(pairCdr(pExpr)) ;
			return success ;
		}
		return success ;
	}
} ;

#endif //_MiaLinkAsserter_H
