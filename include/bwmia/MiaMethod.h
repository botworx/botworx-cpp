/*Botworx AI - An Artificial Intelligence Framework
Copyright (C) 2004  Kurtis Fields. See BotworxAI_License.txt for details.
*/
#ifndef _MiaMethod_H
#define _MiaMethod_H

#include "MiaRule.h"
#include "MiaBinder.h"

class MiaSpace ;
class MiaMind ;
class MiaDomain ;
class MiaFactoid ;

class MiaMethodFactory ;
typedef boost::intrusive_ptr<MiaMethodFactory> MiaMethodFactoryPtr ;

class MiaMethod : public BwCell {
public:
	//use for dummy creation
	MiaMethod(MiaMind& mind) ;
	MiaMethod(MiaMind& mind, MiaMethodFactory* pFactory, MiaBinder& binder, MiaFact* pFact = NULL) ;
	void *operator new(size_t count) throw() ;
	virtual void purge() ;
	//
	MiaMind& getMind() { return *p_mind ; }
	bool eval() ;
	bool evalRule(MiaRuleFactory* pFactory) ;
	MiaMethodFactory* getMethodFactory() { return p_factory ; }
	//Data
	MiaMind* p_mind ;
	MiaMethodFactory* p_factory ;
	MiaRule m_rule ;
	//
	bool onSymbol(AiSymbol* pSymbol) ;

	enum methodStatus_E {
		STATUS_BUSY,
		STATUS_RETURN
	} ;
	typedef methodStatus_E methodStatus ;
	bool isBusy() { return m_status == STATUS_BUSY ; }
	void setStatus(methodStatus status) { m_status = status ; }
	methodStatus getStatus() { return m_status ; }
	methodStatus m_status ;
	//
	MiaBinder* getBinder() { return &m_binder ; }
	MiaBinder m_binder ; //binder for logic variables
	//
	void setSelectSpace(MiaSpace* pSpace) { p_selectSpace = pSpace ; }
	MiaSpace& getSelectSpace() { return *p_selectSpace ; }
	MiaSpace* p_selectSpace ; //defaults to p_state, yet may refer otherwise.
	//
	void setPropertyVal(AiSymbol* pSymbol, BwCell* pVal) ;
	BwCell* getPropertyVal(AiSymbol* pSymbol) ;
	//
	void call(MiaFactoid& factoid) ;
	//
	void setFact(MiaFact* pFact) { p_fact = pFact ; }
	MiaFact* getFact() { return p_fact.get() ; }
	MiaFactPtr p_fact ; //fact this op is instantiated with / bound to
} ;
typedef boost::intrusive_ptr<MiaMethod> MiaMethodPtr ;
//
//MiaMethodKit
//
#include <bwai/AiKit.h>

class MiaMethodKit : public AiPoolKitT<AiKit, MiaMethod> {
public:
	MiaMethodKit(AiKit*  pSuperKit, AiKitInfo *pKitInfo) 
		: AiPoolKitT<AiKit, MiaMethod>(MIA_KT_METHOD, pSuperKit, pKitInfo) {}
} ;

DECLARE_KITINFO(MiaMethodKit) ;
//
//MiaFact
//
inline void* MiaMethod::operator new(size_t size) throw() {
#if AI_OPTION_POOLING
	return k_method().rent() ;
#else
	return BW_USERMALLOC(size, MIA_TT_METHOD) ;
#endif
}
////////////////////////////////////
#include "MiaFactory.h"
class MiaRuleFactory ;

enum triggerType_E {
	TRIGGER_ASSERTION,
	TRIGGER_RETRACTION,
	TRIGGER_UNKNOWN
} ;
typedef triggerType_E triggerType ;

class MiaMethodFactory : public MiaFactory {
public:
	MiaMethodFactory(MiaDomain& domain, AiSymbol* pSymbol, AiPair* pSignature = NULL) ;
	void *operator new(size_t count) throw() ;
	virtual void purge() ;
	//
	MiaMethod* produce(MiaMind& mind, MiaBinder& binder, MiaFact* pFact = NULL) ;
	AiPair* getRuleFactories() { return p_ruleFactories.get() ; }
	MiaRuleFactory* addRuleFactory(MiaRuleFactory* pFactory) ;
	//Data
	AiPairPtr p_ruleFactories ;
	//
	void processSignature(AiPair* pSignature) ;
	AiPair* getSignature() { return p_signature.get() ; }
	triggerType getTriggerType() { return m_triggerType ; }
	//
	MiaDomain* getDomain() { return p_domain ; }
	MiaDomain* p_domain ;
	triggerType m_triggerType ;
	AiPairPtr p_signature ; //(:agent stack ?x)
} ;
#define asMethodFactory(X) (static_cast<MiaMethodFactory*>(X))
//
inline void* MiaMethodFactory::operator new(size_t count) throw() {
	return BW_USERMALLOC(sizeof(MiaMethodFactory), MIA_TT_METHODFACTORY) ;
}

#endif //_MiaMethod_H
