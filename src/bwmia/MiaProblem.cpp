/*Botworx AI - An Artificial Intelligence Framework
Copyright (C) 2004  Kurtis Fields. See BotworxAI_License.txt for details.
*/
#include "stdafx.h"

#include <bwmia/MiaProblem.h>
#include <bwmia/MiaDomain.h>
#include <bwmia/MiaExplorer.h>
#include <bwmia/MiaState.h>
#include <bwmia/MiaAgent.h>
//
// MiaProblem
//
MiaProblem::MiaProblem(MiaDomain* pDomain) : BwActor(NULL), p_domain(pDomain) {
	createRoot() ;
	createExplorer() ;
}
MiaProblem::~MiaProblem() {
	destroyPart(p_root) ;
}
//
void MiaProblem::createRoot() {
	AiSymbol* pSymbol = p_domain->getSymbol() ;
	AiSymbol* pName = new AiSymbol( ("/" + pSymbol->getString()).c_str()) ;
	p_root = new MiaState(NULL, pName, NULL) ;
	p_root->p_problem = this ;
	p_root->setDomain(p_domain) ;
	if(k_core().getIoMode() == MiaCore::IO_MESSAGING) {
		p_root->setIsLogging(true) ;
		p_root->setIsEmitting(true) ;
	}
	p_root->createEnabled() ;
}
void MiaProblem::createExplorer() {
	p_explorer = new MiaExplorer(p_root) ;
	p_explorer->setMaxDepth(20) ;
	//TODO:In the future specify style in domain definition
	p_explorer->setExplorationStyle(MiaExplorer::EXPLORE_VERTICAL) ;
	//p_explorer->setExplorationStyle(MiaExplorer::EXPLORE_DIAGONAL) ;
	//p_explorer->setExplorationStyle(MiaExplorer::EXPLORE_HORIZONTAL) ;
}
//
MiaState* MiaProblem::chooseSolution() {
	size_t solutionCount = m_solutions.size() ;
	if(solutionCount == 0)
		return NULL ;
	if(solutionCount == 1)
		return m_solutions[0] ;
	//else
	int ndx = k_agent().rollInt(0, (int)m_solutions.size()-1) ;
	return m_solutions[ndx] ;
}
BwScript* MiaProblem::makeScript() {
	MiaState *pState = chooseSolution() ;
	if(pState == NULL)
		return NULL ;
	return pState->makeScript() ;
}