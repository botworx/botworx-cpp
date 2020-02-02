/*Botworx AI - An Artificial Intelligence Framework
Copyright (C) 2004  Kurtis Fields. See BotworxAI_License.txt for details.
*/
#ifndef _MiaEval_H
#define _MiaEval_H

#include "MiaIdentifier.h"

class MiaBinder ;

class MiaEval {
public:
	MiaEval(MiaBinder& binder) {
		p_binder = &binder ;
	}
	BwCell* eval(BwCell* pExpr) ;
	BwCell* evalPair(AiPair* pExpr) ;
	MiaBinder* getBinder() { return p_binder ; }
	MiaBinder& binder() { return *p_binder ; }
	//
	void setSymbolVal(AiSymbol* pSymbol, BwCell* pVal) ;
	BwCell* getSymbolVal(AiSymbol* pSymbol) ;
	void setGlobalVal(AiSymbol* pSymbol, BwCell* pVal) ;
	BwCell* getGlobalVal(AiSymbol* pSymbol) ;
	void setLogicVal(AiSymbol* pSymbol, BwCell* pVal) ;
	BwCell* getLogicVal(AiSymbol* pSymbol) ;
	void setPropertyVal(AiSymbol* pSymbol, BwCell* pVal) ;
	BwCell* getPropertyVal(AiSymbol* pSymbol) ;
	//Data Members
	MiaBinder* p_binder ;
} ;

#endif //_MiaEval_H
