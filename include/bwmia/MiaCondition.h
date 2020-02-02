/*Botworx AI - An Artificial Intelligence Framework
Copyright (C) 2004  Kurtis Fields. See BotworxAI_License.txt for details.
*/
#ifndef _MiaCondition_H
#define _MiaCondition_H

#include "MiaRuleNode.h"

class MiaCondition ;
class MiaConditions ;
class MiaLhs ;

typedef std::list<MiaCondition*> MiaConditionList ;
typedef MiaConditionList::iterator MiaConditionIter ;

class MiaCondition : public MiaRuleNode {
public:
	MiaCondition(MiaConditions* pOwner, BwCell* pExpr) 
		: MiaRuleNode(pExpr), p_owner(pOwner), p_lhs(NULL) {}
	virtual ~MiaCondition() {}
	virtual void create() ;
	MiaLhs* getLhs() { return p_lhs ; }
	//Data Members
	MiaLhs* p_lhs ;
	MiaConditions* p_owner ;
};
class MiaSymbolCondition : public MiaCondition {
public:
	MiaSymbolCondition(MiaConditions* pOwner, BwCell* pExpr) : MiaCondition(pOwner, pExpr) {}
	virtual bool eval(MiaBinder& binder) ;
};
class MiaTest : public MiaCondition {
public:
	MiaTest(MiaConditions* pOwner, BwCell* pExpr) : MiaCondition(pOwner, pExpr) {}
};
class MiaMatchTest : public MiaTest {
public:
	MiaMatchTest(MiaConditions* pOwner, AiPair* pExpr) : MiaTest(pOwner, pExpr) {
		m_pattern.setExpr(pExpr) ;
	}
	virtual bool eval(MiaBinder& binder) ;
	//Data Members
	MiaPattern m_pattern ;
};
//
class MiaRelationalTest : public MiaTest {
public:
	MiaRelationalTest(MiaConditions* pOwner, BwCell* pExpr) : MiaTest(pOwner, pExpr) {}
	virtual bool eval(MiaBinder& binder) ;
	enum testTypes {
		TYPE_EQ = 0,
		TYPE_NEQ,
		TYPE_LT,
		TYPE_LE,
		TYPE_GT,
		TYPE_GE
	} ;
	typedef testTypes testType ;
	void setType(testType type) { m_type = type ; }
	//Data Members
	testType m_type ;
};
//
class MiaConditions : public MiaCondition {
public:
	MiaConditions(MiaConditions* pOwner, AiPair* pExpr) : MiaCondition(pOwner, pExpr) {}
	~MiaConditions() ;
	virtual bool eval(MiaBinder& binder) ;
	virtual void addCondition(MiaCondition* pCondition) ;
	//Data Members
	MiaConditionList m_conditions ;
};
//
class MiaFramedConditions : public MiaConditions {
public:
	MiaFramedConditions(MiaConditions* pOwner, AiPair* pExpr) ;
	virtual bool eval(MiaBinder& binder) ;
	//Data Members
	BwCell* getStateExpr() { return p_stateExpr.get() ; }
	BwCellPtr p_stateExpr ;
};
//
class MiaConjunction : public MiaConditions {
public:
	MiaConjunction(MiaConditions* pOwner, AiPair* pExpr) : MiaConditions(pOwner, pExpr) {}
};
//
class MiaNegation : public MiaConditions {
public:
	MiaNegation(MiaConditions* pOwner, AiPair* pExpr) : MiaConditions(pOwner, pExpr) {}
	virtual bool eval(MiaBinder& binder) ;
};
//
class MiaDisjunction : public MiaConditions {
public:
	MiaDisjunction(MiaConditions* pOwner, AiPair* pExpr) : MiaConditions(pOwner, pExpr) {}
	virtual bool eval(MiaBinder& binder) ;
};
//
class MiaLhs : public MiaConjunction {
public:
	MiaLhs(MiaRuleFactory* pRuleFactory, AiPair* pExpr) : MiaConjunction(NULL, pExpr) {
		p_ruleFactory = pRuleFactory ;
	}
	virtual void create() ;
	virtual bool eval(MiaBinder& binder) ;
	bool eval2(MiaBinder& binder, MiaConditionIter iter) ;
	//bool eval3(MiaBinder& binder, MiaConditionIter iter, MiaBindingIter bindIter, MiaBindingIter bindEnd, bool success) ;
	bool eval3(MiaBinder& binder, MiaConditionIter iter) ;
	//Data Members
	MiaRuleFactory* p_ruleFactory ;
};
//
#endif //_MiaCondition_H
