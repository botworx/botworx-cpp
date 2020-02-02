/*Botworx AI - An Artificial Intelligence Framework
Copyright (C) 2004  Kurtis Fields. See BotworxAI_License.txt for details.
*/
#ifndef _MiaAction_H
#define _MiaAction_H

#include "MiaRuleNode.h"

class MiaAction ;
class MiaActions ;
class MiaRhs ;

typedef std::list<MiaAction*> MiaActionList ;
typedef MiaActionList::iterator MiaActionIter ;

class MiaAction : public MiaRuleNode {
public:
	MiaAction(MiaActions* pOwner, BwCell* pExpr) 
		: MiaRuleNode(pExpr), p_owner(pOwner), p_rhs(NULL) {}
	virtual ~MiaAction() {}
	virtual void create() ;
	MiaRhs* getRhs() { return p_rhs ; }
	//Data Members
	MiaActions* p_owner ;
	MiaRhs* p_rhs ;
};
//
class MiaSymbolAction : public MiaAction {
public:
	MiaSymbolAction(MiaActions* pOwner, BwCell* pExpr) : MiaAction(pOwner, pExpr) {}
	virtual bool eval(MiaBinder& binder) ;
};
//
class MiaDestroyAction : public MiaAction {
public:
	MiaDestroyAction(MiaActions* pOwner, BwCell* pExpr) : MiaAction(pOwner, pExpr) {}
	virtual bool eval(MiaBinder& binder) ;
};
//
class MiaPrintAction : public MiaAction {
public:
	MiaPrintAction(MiaActions* pOwner, BwCell* pExpr) : MiaAction(pOwner, pExpr) {}
	virtual bool eval(MiaBinder& binder) ;
};
//
class MiaActions : public MiaAction {
public:
	MiaActions(MiaActions* pOwner, BwCell* pExpr) : MiaAction(pOwner, pExpr) {}
	~MiaActions() ;
	virtual bool eval(MiaBinder& binder) ;
	virtual void addAction(MiaAction* pAction) ;
	//Data Members
	MiaActionList m_actions ;
};
//
class MiaRhs : public MiaActions {
public:
	MiaRhs(MiaRuleFactory* pRuleFactory, BwCell* pExpr) : MiaActions(NULL, pExpr) {
		p_ruleFactory = pRuleFactory ;
	}
	virtual void create() ;
	virtual bool eval(MiaBinder& binder) ;
	//Data Members
	MiaRuleFactory* p_ruleFactory ;
};
//
#endif //_MiaAction_H
