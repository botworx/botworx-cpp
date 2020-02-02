/*Botworx AI - An Artificial Intelligence Framework
Copyright (C) 2004  Kurtis Fields. See BotworxAI_License.txt for details.
*/
#ifndef _MiaSubjectAsserter_H
#define _MiaSubjectAsserter_H

#include "MiaAsserterBase.h"

#include <bwmia/MiaMethod.h>
#include <bwmia/MiaLinkAsserter.h>

class MiaSubjectAsserter : public MiaAsserterBase {
public:
	MiaSubjectAsserter(MiaBinder& binder, MiaFactoid& result)
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
				result().setSubject(pVal) ;
				success = true ;
				break ;
			default :
				bwAssert(0) ;
		}
		if(success) {
			MiaLinkAsserter linkAsserter(binder(), result()) ;
			success = linkAsserter.assertExpr(pairCdr(pExpr)) ;
			return success ;
		}
		return success ;
	}
} ;

#endif //_MiaSubjectAsserter_H
