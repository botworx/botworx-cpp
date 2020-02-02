/*Botworx AI - An Artificial Intelligence Framework
Copyright (C) 2004  Kurtis Fields. See BotworxAI_License.txt for details.
*/
#ifndef _MiaAssertion_H
#define _MiaAssertion_H

#include <bwai/AiList.h>

#include "MiaFactoid.h"

class MiaBinder ;

class MiaAssertion : public MiaFactoid {
public:
	MiaAssertion() : MiaFactoid() {}
	MiaAssertion(MiaFact* pSubject, MiaFact* pLink = NULL, BwCell* pVal = NULL, float truth = 1.0f) 
		: MiaFactoid(pSubject, pLink, pVal, truth)  {}
	MiaAssertion(const MiaFact& fact) : MiaFactoid(fact) {}

	AiPair* getResults() { return m_results.get() ; }

	void addResult(MiaFact* pFact) { m_results.push_back(pFact) ; }

	bool makeShort(MiaBinder& binder, AiPair* pExpr) ;
	bool makeShort(MiaBinder& binder, AiSymbol* pLinkSym, BwCell* pVal) ;
	bool makeShorts(MiaBinder& binder, AiPair* pExpr) ;
	bool makeSimple(MiaBinder& binder, AiPair* pExpr) ;

	MiaFact* output(MiaBinder& binder, makerType type = MAKER_ASSERTION) ;
private:
	void postResults(MiaBinder& binder) ;
	void postTemps(MiaBinder& binder) ;
	void proposeResults(MiaBinder& binder) ;
	void retractResults(MiaBinder& binder) ;
	//Data Members
public:
	AiList m_results ;
};

#endif //_MiaAssertion_H
