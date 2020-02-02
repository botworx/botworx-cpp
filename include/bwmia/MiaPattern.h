#ifndef _MiaPattern_H
#define _MiaPattern_H

#include "MiaFactoid.h"

class MiaBinder ;
class MiaFactoid ;

class MiaPattern : public MiaFactoid {
public:
	MiaPattern() : MiaFactoid() {}
	MiaPattern(MiaFact* pSubject, MiaFact* pLink, BwCell* pVal, float truth = 1.0f) 
		: MiaFactoid(pSubject, pLink, pVal, truth)  {}
	MiaPattern(const MiaFact& fact) : MiaFactoid(fact) {}
	MiaPattern(AiPair* pSignature) { setExpr(pSignature) ; }
	void setExpr(AiPair* pSignature) ;
	//
	bool matchSignature(MiaFact* pFact) const {
		if(p_link == pFact->getLink())
			if(p_subject == NULL || p_subject == pFact->getSubject())
				if(m_truth == pFact->getTruth())
					return true ;
		//else
		return false ;
	}
	bool match(MiaFact* pFact) const {
		if(p_link == pFact->getLink())
			if(p_subject == NULL || p_subject == pFact->getSubject())
				if(p_value == NULL || p_value == pFact->getValue())
					return true ;
		//else
		return false ;
	}
	bool match(MiaBinder& binder, MiaFactoid& result) ;
	//
	AiPair* getExpr() { return p_expr.get() ; }
	//Data Members
	AiPairPtr p_expr ;
} ;
typedef std::vector<MiaPattern> MiaPatterns ;
typedef MiaPatterns::iterator MiaPatternIter ;

////////
#include <bwai/AiList.h>

enum searchResultType_E {
	SEARCHRESULT_FACT = 0,
	SEARCHRESULT_SUBJECT ,
	SEARCHRESULT_LINK,
	SEARCHRESULT_VALUE
} ;
typedef searchResultType_E searchResultType ;

class MiaSearch : public MiaPattern {
public:
	MiaSearch() : MiaPattern() {}
	MiaSearch(MiaFact* pSubject, MiaFact* pLink, BwCell* pVal, float truth = 1.0f) 
		: MiaPattern(pSubject, pLink, pVal, truth)  {}
	MiaSearch(const MiaFact& fact) : MiaPattern(fact) {}
	MiaSearch(AiPair* pSignature) : MiaPattern(pSignature) {}
	MiaSearch(const MiaPattern& pattern) {
		init(pattern.getSubject(), 
		pattern.getLink(), 
		pattern.getValue(), 
		pattern.getTruth()) ;
	}
	//
	void setResultType(searchResultType type) { m_resultType = type ; }
	searchResultType getResultType() { return m_resultType ; }
	//
	void addResult(BwCell* pVal) { m_results.push_back(pVal) ; }
	AiPair* getResults() { return m_results.get() ; }
	bool empty() { return m_results.empty() ; }
	//Data Members
	searchResultType m_resultType ;
	//AiList m_results ;
	AiFastList m_results ;
} ;

#endif //_MiaPattern_H