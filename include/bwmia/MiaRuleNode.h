/*Botworx AI - An Artificial Intelligence Framework
Copyright (C) 2004  Kurtis Fields. See BotworxAI_License.txt for details.
*/
#ifndef _MiaRuleNode_H
#define _MiaRuleNode_H

#include "MiaBinder.h"
#include "MiaPattern.h"

class MiaRule ;
class MiaRuleFactory ;

class MiaRuleNode {
public:
	MiaRuleNode(BwCell* pExpr) : p_expr(pExpr){}
	virtual ~MiaRuleNode() {}
	virtual void create() {}
	virtual bool eval(MiaBinder& binder) { return true ; }
	//void setExpr(BwCell* pExpr) { p_expr = pExpr ; }
	BwCell* getExpr() { return p_expr.get() ; }
	//Data Members
	BwCellPtr p_expr ;
};

#endif //_MiaRuleNode_H
