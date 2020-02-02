/*Botworx AI - An Artificial Intelligence Framework
Copyright (C) 2004  Kurtis Fields. See BotworxAI_License.txt for details.
*/
#include "stdafx.h"

#include <bwcontrol/BwScript.h>
#include <bwmia/MiaAgent.h>
#include <bwmia/MiaProblem.h>
#include <bwai/AiInt.h>
#include <bwai/AiBuffer.h>

#include <bwmia/MiaTopic.h>
#include <bwmia/MiaIdentifier.h>
#include <bwmia/MiaDomain.h>
#include <bwmia/MiaState.h>
#include <bwmia/MiaMatcher.h>
#include <bwmia/MiaBinder.h>
#include <bwmia/config/options.h>

#include <bwagency/_BwAgent.h>
using namespace _BwAgent ;
#include <bwagency/_BwState.h>
using namespace _BwState ;

const float MiaState::DEFAULT_COST = 1.0f ;
const float MiaState::DEFAULT_BENEFIT = 1.0f ;
const float MiaState::DEFAULT_VALUE = 0.0f ; //includes children value

MiaState::MiaState(MiaState* pState, AiSymbol* pSymbol, AiPair* pInput)
	: MiaMind(pState, pSymbol) {
	if(hasParent()){
		m_depth = parentState().m_depth + 1 ;
		p_domain = parentState().getDomain() ;
	}
	else {
		m_depth = 0 ;
	}
	//
	m_input.set(pInput) ;
	if(!m_input.empty())
		setFact(asFact(car(pInput))) ;
	//
	p_problem = NULL ;
	//
	p_stage = &m_stage ;
	m_stage.setOwner(this) ;
	m_stage.create() ;
//
	m_childCount = 0 ;
	//
	m_isSolution = false ;
	m_cost = m_costTtl = DEFAULT_COST ;
	m_benefit = m_benefitTtl = DEFAULT_BENEFIT ;
	m_value = m_benefitTtl - m_costTtl ;
	//
	#if AI_OPTION_POOLING
		setFactory(k_state().p_defaultFactory) ; //TODO:a better way?
	#endif
}
MiaState::~MiaState() {
	//delete p_space ;
}
bool MiaState::eval(MiaExplorer& explorer) {
	processPosts() ;
	for(MiaMethodQueue::iterator iter = m_methodQueue.begin() ; iter != m_methodQueue.end() ; ++iter) {
		iter->get()->eval() ;
	}
	m_methodQueue.clear() ;
	return true ;
}
//
void MiaState::createDefaultMode() {
	setNextMode(getDomain()->getDefaultModeFactory()->getSymbol()) ;
}
bool MiaState::advanceMode() {
	bool success = false ;
	AiSymbol* pSymbol = getNextMode() ;
	if(pSymbol == NULL)
		return success ;
	//else
	success = true ;
	MiaMethodFactory* pMethodFactory = getDomain()->findMethodFactory(pSymbol) ;
	MiaBinder binder ;
	scheduleMethod(pMethodFactory->produce(*this, binder)) ;
	#if AI_OPTION_INSTRUMENT
		if(isLogging()) {
			//if(!isState()) logger << getState()->getSymbol()->getString() << "::" ;
			logger() << *p_symbol ;
			logger() << ":  Mode Change  :  " ;
			logger() << *pSymbol << endl ;
		}
	#endif
	setMode(pSymbol) ;
	setNextMode(NULL) ;
	return success ;
}
void MiaState::doCreate(const BwPartInfo& info) {
	MiaMind::doCreate(info) ;

	if(isRoot()) {
		setFact(getId()) ; //too keep :goal from bombing at root!
	}
	else
		p_problem = parentState().getProblem() ;
}
bool MiaState::onCreate(const BwPartInfo& info) {
//
#if AI_OPTION_INSTRUMENT
	if(isEmitting()) {
		MiaFact* pArc = getFact() ;
		MiaPrinter printer ;
		BwStringSink printSink(true) ;
		bwString tempBuffer ;
		printSink.setString(tempBuffer) ;
		printer.pushSink(&printSink) ;
		//
		bwHandle parentHandle = bwAnyHandle ;
		if(hasParent())
			parentHandle = getParent()->getHandle() ;
		if(pArc != NULL)
			printer << *pArc ;
		k_agent().getEventSlot().send(BwStateAddedEvent(getSymbol()->getString(), getHandle(), parentHandle, tempBuffer)) ;
	}
#endif
//
	createDefaultMode() ;
	//post(new MiaFact(getId(), SUBJECT_TYPE, SYM_STATE)) ;
	getIdTopic()->addFact(new MiaFact(getId(), SUBJECT_TYPE, SYM_STATE)) ;
	input() ;
	return MiaMind::onCreate(info) ;
}
void MiaState::input() {
	if(m_input.empty())
		return ;
	//else
	MiaFact* pProposal = NULL ;
	for(AiPair* pProposals = m_input.get() ; pProposals != NIL ; pProposals = pairCdr(pProposals)) {
		pProposal = asFact(car(pProposals)) ;
		post(pProposal) ;
	}
}
BwCell* MiaState::getPropertyVal(AiSymbol* pSymbol) {
	if(pSymbol == PSYM_STATE)
		return getId() ;
	//else
	if (pSymbol == PSYM_AGENT)
		return SUBJECT_AGENT ;
	//else
	if (pSymbol == PSYM_THOUGHT)
		//return getFact() ;
		bwAssert(0) ; //this is the methods input ... never gets here.
	//else
	if (pSymbol == PSYM_GOAL)
		return getFact() ;
	//else
	if (pSymbol == PSYM_PARENT) {
		if(p_parent != NULL) {
			return p_parent->getId() ;
		}
		else {
			return NULL ;
		}
	}
	//else
	return UNBOUND ;
}
void MiaState::doStep(BwStepper& stepper) {
	BwActor::doStep(stepper) ;
	if(isHalted() || isDead())
		return ;
	eval(explorerCast(stepper)) ;
}
bool MiaState::onPostStep(BwStepper& stepper) {
	MiaExplorer& explorer = explorerCast(stepper) ;
	bool success = true ;
	bool maxDepth = (m_depth == explorer.getMaxDepth()) ;
	if(isHalted() || isDozing() || isDead())
		return false ;

	if(m_isSolution) {
		//explorer.addSolution(this) ;
		p_problem->addSolution(this) ;
		success = doze() ;
	}
	else if(!maxDepth && isIdle()) {
		success = jumpstart(explorer) ;
	}

	return success & BwActor::onPostStep(stepper) ;
}
bool MiaState::jumpstart(MiaExplorer& explorer) {
	bool success = true ;
	output(explorer) ;

	//still stalled
	if(isStalled())
		success = advanceMode() ;

	return success ;
}
bool MiaState::onSuccess() {
	return true ;
}
bool MiaState::onFailure() {
#if AI_OPTION_INSTRUMENT
	if(isEmitting()) {
		k_agent().getEventSlot().send(BwStateFailedEvent(getHandle())) ;
	}
#endif
	//return die() ;
	return doze() ;
}
void MiaState::setIsSolution(bool val) {
	m_isSolution = val ;
#if AI_OPTION_INSTRUMENT
	if(isEmitting()) {
		k_agent().getEventSlot().send(BwStateSolutionEvent(getHandle())) ;
	}
#endif
}
void MiaState::addState(MiaState* pState) {
	m_stage.addActor(pState) ;
}
void MiaState::removeState(MiaState* pState) {
	m_stage.removeActor(pState) ;
}
void MiaState::destroyState(MiaState* pState) {
	removeState(pState) ;
	destroyPart(pState) ;
}
//TODO:need to handle retractions?
void MiaState::receive(MiaFact *pFact) {
	MiaFact *pLink = pFact->getLink() ;
	if(pLink == SUBJECT_SCRIPT) {
		AiString *pScript = asString(pFact->getValue()) ;
		m_script = pScript->getString() ;
	}
	else if(pLink == SUBJECT_COST) { //TODO:what about float???!!!
		AiInt *pVal = asInt(pFact->getValue()) ;
		setCost(pVal->m_value) ;
	}
	else if(pLink == SUBJECT_BENEFIT) {
		AiInt *pVal = asInt(pFact->getValue()) ;
		setBenefit(pVal->m_value) ;
	}
}
bool MiaState::processPosts() {
	if(m_posts.empty())
		return false ;
	MiaFact* pFact = NULL ;
	for(AiPair* pPosts = getPosts() ; pPosts != NIL ; pPosts = pairCdr(pPosts) ) {
		pFact = asFact(car(pPosts)) ;
		getDomain()->produceMethods(*this, pFact) ;
	}
	m_posts.clear() ;
	return true ;
}
void MiaState::output(MiaExplorer& explorer) {
	if(m_output.empty())
		return ;
	switch(explorer.getExplorationStyle()) {
		case MiaExplorer::EXPLORE_DIAGONAL : {
			exploreOne() ;
		}
		break ;
		case MiaExplorer::EXPLORE_VERTICAL : {
			exploreAll() ;
		}
		break ;
		case MiaExplorer::EXPLORE_HORIZONTAL : {
			bwAssert(0) ;
			/*if(m_stage.isIdle()) {
				MiaState *pUnexplored = choose_unexplored() ;
				explore(pUnexplored) ;
			}*/
		}
		break ;
	}
}
void MiaState::exploreOne() {
	AiPair* pProposals = getOutput() ;
	AiPair* pProposal = pairCar(pProposals) ;
	spawnState(pProposal) ;
	m_output.set(pairCdr(pProposals)) ;
}
void MiaState::exploreAll() {
	AiPair* pProposal = NULL ;
	for(AiPair* pProposals = getOutput() ; pProposals != NIL ; pProposals = pairCdr(pProposals)) {
		pProposal = pairCar(pProposals) ;
		spawnState(pProposal) ;
	}
	m_output.clear() ;
}
void MiaState::spawnState(AiPair* pProposals) {
	AiBufferPtr buffer = new AiBuffer() ;
	char* cbuffer = buffer->getBuffer();
    size_t bufferSize = buffer->getSize();
	//_itoa(m_childCount++, cbuffer, 10) ;
	//snprintf(cbuffer, bufferSize, "%d", m_childCount++);
	bwItoa(m_childCount++, cbuffer, bufferSize, 10);

	AiSymbol* pSymbol = new AiSymbol(p_symbol->getString() + "/" + cbuffer) ;
	MiaState* pState = new MiaState(this, pSymbol, pProposals) ;

	pState->createEnabled() ;
	addState(pState) ;
}
BwScript* MiaState::_makeScript() {
	if(!hasParent())
		return NULL ;
	//else
	BwScript* pScript = NULL ;
	if(!m_script.empty()) {
		pScript = new BwScript(m_script) ;
		BwScript* pSubScript = parentState()._makeScript() ;
		if(pSubScript != NULL)
			pScript->addScript(pSubScript) ;
		return pScript ;
	}
	else
		return parentState()._makeScript() ;
}
bool MiaState::fail() {
#if AI_OPTION_INSTRUMENT
	if(isEmitting()) {
		k_agent().getEventSlot().send(BwStateFailedEvent(getHandle())) ;
	}
#endif
	//return die() ;
	return doze() ;
}
/////////////////
DEFINE_KITTYPE(MiaStateKit) ;

TYPEINFO_NONE(MiaStateKit) ;
NO_KITINFO(MiaStateKit) ;

KITINFO("MiaStateKit", MIA_KT_STATE, MiaStateKit) ;
