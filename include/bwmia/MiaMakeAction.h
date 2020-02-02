/*Botworx AI - An Artificial Intelligence Framework
Copyright (C) 2004  Kurtis Fields. See BotworxAI_License.txt for details.
*/
#ifndef _MiaMakeAction_H
#define _MiaMakeAction_H

#include "MiaAction.h"
//
//MiaMakeAction
//
class MiaMakeAction : public MiaAction {
public:
	MiaMakeAction(MiaActions* pOwner, BwCell* pExpr, makerType type) : MiaAction(pOwner, pExpr), m_makerType(type) {}
	virtual bool eval(MiaBinder& binder) ;
	//
	MiaFact* makeSimple(MiaBinder& binder, AiPair* pExpr) ;
	MiaFact* makeComplex(MiaBinder& binder, AiPair* pExpr) ;
	bool makeTopic(MiaBinder& binder, AiPair* pExpr) ;
	//Data Members
	makerType getMakeActionType() { return m_makerType ; }
	makerType m_makerType ;
};
//
//MiaSimpleMakeAction
//
class MiaSimpleMakeAction : public MiaMakeAction {
public:
	MiaSimpleMakeAction(MiaActions* pOwner, BwCell* pExpr, makerType type) : MiaMakeAction(pOwner, pExpr, type) {}
	virtual bool eval(MiaBinder& binder) ;
};
//
//MiaComplexMakeAction
//
class MiaComplexMakeAction : public MiaMakeAction {
public:
	MiaComplexMakeAction(MiaActions* pOwner, BwCell* pExpr, makerType type) : MiaMakeAction(pOwner, pExpr, type) {}
	virtual bool eval(MiaBinder& binder) ;
};
//
//MiaTopicMakeAction
//
class MiaTopicMakeAction : public MiaMakeAction {
public:
	MiaTopicMakeAction(MiaActions* pOwner, BwCell* pExpr, makerType type) : MiaMakeAction(pOwner, pExpr, type) {}
	virtual bool eval(MiaBinder& binder) ;
};
#endif //_MiaMakeAction_H
