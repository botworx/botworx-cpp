/*Botworx AI - An Artificial Intelligence Framework
Copyright (C) 2004  Kurtis Fields. See BotworxAI_License.txt for details.
*/
#ifndef _MiaState_H
#define _MiaState_H

#include "MiaMind.h"
#include "MiaStage.h"
#include "MiaPattern.h"
#include <bwai/AiList.h>
#include "MiaExplorer.h"
#include "MiaRule.h"

class MiaProblem ;
class BwScript ;

//
//MiaState
//
class MiaState : public MiaMind {
public:
	MiaState(MiaState* pState, AiSymbol* pSymbol, AiPair* pInput) ;
	void *operator new(size_t count) throw() ;
	virtual ~MiaState() ;
	virtual void doCreate(const BwPartInfo& info) ;
	virtual bool onCreate(const BwPartInfo& info) ;
	virtual void doStep(BwStepper& stepper) ;
	virtual bool onPostStep(BwStepper& stepper) ;
	//
	bool fail() ;
	bool isIdle() { return m_posts.empty() ; }
	bool isStalled() { return m_posts.empty() && m_stage.isIdle() ; }
	//
	void createDefaultMode() ;
	bool advanceMode() ;
	void setNextMode(AiSymbol* pSymbol) { p_nextMode = pSymbol ; }
	AiSymbol* getNextMode() { return p_nextMode.get() ; }
	AiSymbolPtr p_nextMode ;
	void setMode(AiSymbol* pSymbol) { p_mode = pSymbol ; }
	AiSymbol* getMode() { return p_mode.get() ; }
	AiSymbolPtr p_mode ;
	//
	AiPair* getPosts() const { return m_posts.get() ; }
	AiPair* getInput() const { return m_input.get() ; }
	AiPair* getOutput() const { return m_output.get() ; }
	//
	void addState(MiaState* pState) ;
	void removeState(MiaState* pState) ;
	void destroyState(MiaState* pState) ;
	//
	bool processPosts() ;
	bool eval(MiaExplorer& explorer) ;
	bool jumpstart(MiaExplorer& explorer) ;
	//
	void input() ;
	void output(MiaExplorer& explorer) ;
	void spawnState(AiPair* pProposals) ;
	//
	MiaProblem* getProblem() { return p_problem ; }
	MiaProblem* p_problem ;
	//
	virtual BwCell* getPropertyVal(AiSymbol* pSymbol) ;
	//
	virtual bool onSuccess() ;
	virtual bool onFailure() ;
	//
	void setIsSolution(bool val) ;
	bool isSolution() { return m_isSolution ; }
	virtual BwScript* makeScript() { return _makeScript() ; }
	virtual BwScript* _makeScript() ;
	void setScript(bwString script) { m_script = script ; }
	bwString m_script ;
	//
	virtual void receive(MiaFact* pFact) ; //fact as message to mind...
	bool hasUnexplored() { return !m_output.empty() ; }
	void exploreOne() ;
	void exploreAll() ;
	//Data
	AiList m_input ; //list for incoming proposals
	//
	MiaStage m_stage ;
	//
	int m_childCount ;
	int m_depth ;
	//
	bool m_isSolution ;
	const static float DEFAULT_COST ;
	const static float DEFAULT_BENEFIT ;
	const static float DEFAULT_VALUE ; //includes children value
	void setCost(float cost) { m_cost = cost ; }
	float getCost() { return m_cost ; }
	void setCostTtl(float cost) { m_costTtl = cost ; }
	float getCostTtl() { return m_costTtl ; }
	void setBenefit(float benefit) { m_benefit = benefit ; }
	float getBenefit() { return m_benefit ; }
	void setBenefitTtl(float benefit) { m_benefitTtl = benefit ; }
	float getBenefitTtl() { return m_benefitTtl ; }
	void setValue(float value) { m_value = value ; }
	float getValue() { return m_value ; }
	//
	float m_cost ;
	float m_costTtl ; //total cost including substates
	float m_benefit ;
	float m_benefitTtl ; //total benefit including substates
	float m_value ; //m_benefitTtl - m_costTtl
	/////////
	void setFact(MiaFact* pFact) { p_fact = pFact ; }
	MiaFact* getFact() { return p_fact.get() ; }
	//Data Members
	MiaBinder m_binder ; //binder for logic variables
	MiaFactPtr p_fact ; //fact this op is instantiated with / bound to
	//
	bool isRoot() { return p_parent == NULL ; }
	//
	MiaExplorer& explorerCast(BwStepper& stepper) { return *static_cast<MiaExplorer*>(&stepper) ; }
	//
	MiaState& parentState() { return *static_cast<MiaState*>(p_parent) ; }
} ;
//
//MiaStateKit
//
#include <bwai/AiKit.h>

class MiaStateKit : public AiPoolKitT<AiKit, MiaState> {
public:
	MiaStateKit(AiKit*  pSuperKit, AiKitInfo *pKitInfo) 
		: AiPoolKitT<AiKit, MiaState>(MIA_KT_STATE, pSuperKit, pKitInfo) {}
} ;

DECLARE_KITINFO(MiaStateKit) ;
//
//MiaState
//
inline void* MiaState::operator new(size_t size) throw() {
#if AI_OPTION_POOLING
	return k_state().rent() ;
#else
	return BW_MALLOC(size) ;
#endif
}

#endif //_MiaState_H