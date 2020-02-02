/*Botworx AI - An Artificial Intelligence Framework
Copyright (C) 2004  Kurtis Fields. See BotworxAI_License.txt for details.
*/
#ifndef _MiaRule_H
#define _MiaRule_H

#include <bwai/AiList.h>

class MiaCondition ;
class MiaConditions ;
class MiaLhs ;
class MiaAction ;
class MiaActions ;
class MiaRhs ;
class MiaRuleFactory ;
class MiaBinder ;

class MiaRule {
public:
	MiaRule() : p_factory(NULL) {}
	MiaRule(MiaRuleFactory *pFactory) ;
	void *operator new(size_t count) throw() ;
	void *operator new(size_t count, MiaRule* pRule) throw() { return pRule; }
	//
	virtual bool eval(MiaBinder& binder) ;
	bool applyMatchSuccess(MiaBinder& binder) ;
	bool applyMatchFailure(MiaBinder& binder) ;
	bool applySuccess(MiaBinder& binder) ;
	bool applyFailure(MiaBinder& binder) ;
	//Access
	//Data Members
	MiaRuleFactory *p_factory ;
	//
	void setPartialSuccess(bool val) { m_partialSuccess = val ; }
	bool m_partialSuccess ; //used for testing total success
	void setTotalSuccess(bool val) { m_totalSuccess = val ; }
	bool m_totalSuccess ; //used for testing total success
	//
	void propose(MiaFact* pFact) ;
	AiList m_output ; //list for output. need to collect as list then put in state.
} ;
typedef boost::intrusive_ptr<MiaRule> MiaRulePtr ;
///////////////////
#include "MiaFactory.h"
class MiaRuleFactory : public MiaFactory {
public:
	MiaRuleFactory() ;
	~MiaRuleFactory() ;
	void* operator new(size_t count) {
		return BW_USERMALLOC(count, MIA_TT_RULEFACTORY) ;
	}
	virtual void purge() ;
	void produce(MiaRule* pRule) ;
	//
	void setLhs(MiaLhs* pLhs) { p_lhs = pLhs ; }
	MiaLhs* getLhs() { return p_lhs ; }
	void setMatchSuccessRhs(MiaRhs* pRhs) { p_matchSuccessRhs = pRhs ; }
	MiaRhs* getMatchSuccessRhs() { return p_matchSuccessRhs ; }
	void setMatchFailureRhs(MiaRhs* pRhs) { p_matchFailureRhs = pRhs ; }
	MiaRhs* getMatchFailureRhs() { return p_matchFailureRhs ; }
	void setSuccessRhs(MiaRhs* pRhs) { p_successRhs = pRhs ; }
	MiaRhs* getSuccessRhs() { return p_successRhs ; }
	void setFailureRhs(MiaRhs* pRhs) { p_failureRhs = pRhs ; }
	MiaRhs* getFailureRhs() { return p_failureRhs ; }
	//Data Members
	MiaLhs* p_lhs ;
	MiaRhs* p_matchSuccessRhs ;
	MiaRhs* p_matchFailureRhs ;
	MiaRhs* p_successRhs ;
	MiaRhs* p_failureRhs ;
} ;
typedef boost::intrusive_ptr<MiaRuleFactory> MiaRuleFactoryPtr ;
#define asRuleFactory(X) (static_cast<MiaRuleFactory*>(X))
////////////////////////////////////
#include <bwai/AiKit.h>

class MiaRuleKit : public AiPoolKitT<AiKit, MiaRule> {
public:
	MiaRuleKit(AiKit*  pSuperKit, AiKitInfo *pKitInfo) 
		: AiPoolKitT<AiKit, MiaRule>(MIA_KT_RULE, pSuperKit, pKitInfo) {}
} ;
DECLARE_KITINFO(MiaAssertKit) ;
//
inline void* MiaRule::operator new(size_t size) throw() {
#if AI_OPTION_POOLING
	return k_rule().rent() ;
#else
	return (MiaRule*)BW_USERMALLOC(size, MIA_TT_RULE) ;
#endif
}

#endif //_MiaRule_H
