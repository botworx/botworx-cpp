#ifndef _MiaSelect_H
#define _MiaSelect_H

#include "MiaCondition.h"

class MiaSelect : public MiaConditions {
public:
	MiaSelect(MiaConditions* pOwner, AiPair* pExpr) : MiaConditions(pOwner, pExpr) {}
	//Data Members
	MiaPatterns m_patterns ;
	AiSymbolPtr p_bindSymbol ;
};
typedef std::list<MiaSelect*> MiaSelectList ;
typedef MiaSelectList::iterator MiaSelectIter ;
//
class MiaTopicSelect : public MiaSelect {
public:
	MiaTopicSelect(MiaConditions* pOwner, AiPair* pExpr) : MiaSelect(pOwner, pExpr) {}
	virtual void create() ;
	virtual bool eval(MiaBinder& binder) ;
};
//
class MiaSpaceSelect : public MiaSelect {
public:
	MiaSpaceSelect(MiaConditions* pOwner, AiPair* pExpr) : MiaSelect(pOwner, pExpr) {}
	virtual void create() ;
	virtual bool eval(MiaBinder& binder) ;
};

#endif //_MiaSelect_H