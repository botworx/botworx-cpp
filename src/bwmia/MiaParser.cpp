/*Botworx AI - An Artificial Intelligence Framework
Copyright (C) 2004  Kurtis Fields. See BotworxAI_License.txt for details.
*/
#include "stdafx.h"

#include <bwmia/MiaIdentifier.h>
#include <bwmia/MiaAssertion.h>
#include <bwmia/MiaRule.h>
#include <bwmia/MiaMethod.h>
#include <bwmia/MiaDomain.h>
#include <bwmia/MiaReader.h>
#include <bwmia/MiaParser.h>
#include <bwmia/MiaTopic.h>
//
#include <bwmia/MiaMind.h>
#include <bwmia/MiaState.h>
#include <bwmia/MiaFrame.h>

#include <bwmia/MiaCondition.h>
#include <bwmia/MiaSelect.h>
#include <bwmia/MiaAction.h>
#include <bwmia/MiaMakeAction.h>
#include <bwmia/MiaBinder.h>
//
#include <bwmia/MiaSpace.h>
#include <bwmia/MiaAgent.h>
#include <bwmia/MiaProblem.h>
//
//MiaRuleParser - Condition Parsing
//
void MiaRuleParser::parseSymbolCondition(MiaConditions* pConditions, BwCell* pExpr) {
	MiaSymbolCondition* pCondition = new MiaSymbolCondition(pConditions, pExpr) ;
	pCondition->create() ;
	pConditions->addCondition(pCondition) ;
}
void MiaRuleParser::parseMatchTest(MiaConditions* pConditions, AiPair* pExpr) {
	MiaMatchTest* pTest = new MiaMatchTest(pConditions, pExpr) ;
	pTest->create() ;
	pConditions->addCondition(pTest) ;
}
void MiaRuleParser::parseRelationalTest(MiaConditions* pConditions, AiPair* pExpr) {
	MiaRelationalTest* pTest = new MiaRelationalTest(pConditions, pExpr) ;
	AiSymbol* pLinkSym = asSymbol(cadr(pExpr)) ;
	if(pLinkSym == SYM_EQ)
		pTest->setType(MiaRelationalTest::TYPE_EQ) ;
	else
	if(pLinkSym == SYM_NEQ)
		pTest->setType(MiaRelationalTest::TYPE_NEQ) ;
	else
	if(pLinkSym == SYM_LT)
		pTest->setType(MiaRelationalTest::TYPE_LT) ;
	else
	if(pLinkSym == SYM_LE)
		pTest->setType(MiaRelationalTest::TYPE_LE) ;
	else
	if(pLinkSym == SYM_GT)
		pTest->setType(MiaRelationalTest::TYPE_GT) ;
	else
	if(pLinkSym == SYM_GE)
		pTest->setType(MiaRelationalTest::TYPE_GE) ;

	pTest->create() ;
	pConditions->addCondition(pTest) ;
}
void MiaRuleParser::parseTest(MiaConditions* pConditions, AiPair* pExpr) {
	AiSymbol* pLinkSym = asSymbol(cadr(pExpr)) ;
	if(	(pLinkSym == SYM_EQ) ||
		(pLinkSym == SYM_NEQ) ||
		(pLinkSym == SYM_LT) ||
		(pLinkSym == SYM_LE) ||
		(pLinkSym == SYM_GT) ||
		(pLinkSym == SYM_GE)
		)
		return parseRelationalTest(pConditions, pExpr) ;
	//else
	return parseMatchTest(pConditions, pExpr) ;
}
void MiaRuleParser::parseCondition(MiaConditions* pConditions, BwCell* pExpr) {
	if(isSymbol(pExpr))
		parseSymbolCondition(pConditions, pExpr) ;
	else
	if(isPair(pExpr)) {
		AiPair* pPairExpr = asPair(pExpr) ;
		if(car(pPairExpr) == SYM_NOT)
			parseNegation(pConditions, pairCdr(pPairExpr)) ;
		else
		if(car(pPairExpr) == SYM_OR)
			parseDisjunction(pConditions, pairCdr(pPairExpr)) ;
		else
		if(car(pPairExpr) == SYM_AND)
			parseConjunction(pConditions, pairCdr(pPairExpr)) ;
		else
		if(car(pPairExpr) == SYM_TOPIC)
			parseTopicSelect(pConditions, pairCdr(pPairExpr)) ;
		else
		if(car(pPairExpr) == SYM_SPACE)
			parseSpaceSelect(pConditions, pairCdr(pPairExpr)) ;
		else
		if(isPair(cadr(pPairExpr)))
			parseFramedConditions(pConditions, pPairExpr) ;
		else
			parseTest(pConditions, pPairExpr) ;
	}
}
void MiaRuleParser::parseConditions(MiaConditions* pConditions, AiPair* pExprs) {
	if(pExprs == NULL)
		return ;
	BwCell* pExpr = NULL ;
	bool success = false ;
	for(; pExprs != NIL ; pExprs = pairCdr(pExprs)) {
		pExpr = car(pExprs) ;
		parseCondition(pConditions, pExpr) ;
	}
}
void MiaRuleParser::parseFramedConditions(MiaConditions* pConditions, AiPair* pExpr) {
	if(pExpr == NULL)
		return ;
	MiaFramedConditions* pCondition = new MiaFramedConditions(pConditions, pExpr) ;
	pCondition->create() ;
	pConditions->addCondition(pCondition) ;
	parseConditions(pCondition, pairCdr(pExpr)) ;
}
void MiaRuleParser::parseConjunction(MiaConditions* pConditions, AiPair* pExpr) {
	if(pExpr == NULL)
		return ;
	MiaConjunction* pCondition = new MiaConjunction(pConditions, pExpr) ;
	pCondition->create() ;
	pConditions->addCondition(pCondition) ;
	parseConditions(pCondition, pExpr) ;
}
void MiaRuleParser::parseNegation(MiaConditions* pConditions, AiPair* pExpr) {
	if(pExpr == NULL)
		return ;
	MiaNegation* pCondition = new MiaNegation(pConditions, pExpr) ;
	pCondition->create() ;
	pConditions->addCondition(pCondition) ;
	parseConditions(pCondition, pExpr) ;
}
void MiaRuleParser::parseDisjunction(MiaConditions* pConditions, AiPair* pExpr) {
	if(pExpr == NULL)
		return ;
	MiaDisjunction* pCondition = new MiaDisjunction(pConditions, pExpr) ;
	pCondition->create() ;
	pConditions->addCondition(pCondition) ;
	parseConditions(pCondition, pExpr) ;
}
void MiaRuleParser::parseTopicSelect(MiaConditions* pConditions, AiPair* pExpr) {
	if(pExpr == NULL)
		return ;
	MiaSelect* pCondition = new MiaTopicSelect(pConditions, pExpr) ;
	pCondition->create() ;
	pConditions->addCondition(pCondition) ;
}
void MiaRuleParser::parseSpaceSelect(MiaConditions* pConditions, AiPair* pExpr) {
	if(pExpr == NULL)
		return ;
	MiaSelect* pCondition = new MiaSpaceSelect(pConditions, pExpr) ;
	pCondition->create() ;
	pConditions->addCondition(pCondition) ;
	//
	//TODO:assumes (space ?? (topic
	parseConditions(pCondition, pairCdr(pExpr)) ;
}
MiaLhs* MiaRuleParser::parseLhs(AiPair* pExpr) {
	if(pExpr == NULL) //Still need to create an LHS even if there are no conditions
		return NULL ;
	//else
	MiaLhs* pLhs = new MiaLhs(p_reader->getRuleFactory(), pExpr) ;
	pLhs->create() ;
	parseConditions(pLhs, pExpr) ;
	return pLhs ;
}
//
//MiaRuleParser - Action Parsing
//
void MiaRuleParser::parseSimpleMakeAction(MiaActions* pActions, AiPair* pExpr, makerType type) {
	MiaSimpleMakeAction* pAction = new MiaSimpleMakeAction(pActions, pExpr, type) ;
	pAction->create() ;
	pActions->addAction(pAction) ;
}
void MiaRuleParser::parseComplexMakeAction(MiaActions* pActions, AiPair* pExpr, makerType type) {
	MiaComplexMakeAction* pAction = new MiaComplexMakeAction(pActions, pExpr, type) ;
	pAction->create() ;
	pActions->addAction(pAction) ;
}
void MiaRuleParser::parseTopicMakeAction(MiaActions* pActions, AiPair* pExpr, makerType type) {
	pExpr = pairCdr(pExpr) ; //strip 'make'
	MiaTopicMakeAction* pAction = new MiaTopicMakeAction(pActions, pExpr, type) ;
	pAction->create() ;
	pActions->addAction(pAction) ;
}
//Right Hand Side
void MiaRuleParser::parseMakeAction(MiaActions* pActions, BwCell* pExpr, makerType type) {
	AiPair* pActionExpr = asPair(pExpr) ;
	BwCell* pHead = car(pActionExpr) ;
	if(pHead == SYM_CREATE)
		parseTopicMakeAction(pActions, pActionExpr, type) ;
	else
	if(isPair(pHead))
		parseComplexMakeAction(pActions, pActionExpr, type) ;
	else
		parseSimpleMakeAction(pActions, pActionExpr, type) ;
}
void MiaRuleParser::parseSymbolAction(MiaActions* pActions, BwCell* pExpr) {
	MiaSymbolAction* pAction = new MiaSymbolAction(pActions, pExpr) ;
	pAction->create() ;
	pActions->addAction(pAction) ;
}
//
void MiaRuleParser::parseMakeActions(MiaActions* pActions, AiPair* pExprs, makerType type) {
	if(pExprs == NULL)
		return ;
	//else
	pExprs = pairCdr(pExprs) ;
	BwCell* pExpr = NULL ;
	MiaAction* pAction = NULL ;
	bool success = false ;
	for(; pExprs != NIL ; pExprs = pairCdr(pExprs)) {
		pExpr = car(pExprs) ;
		parseMakeAction(pActions, pExpr, type) ;
	}
}
void MiaRuleParser::parseAssert(MiaActions* pActions, AiPair* pExpr) {
	parseMakeActions(pActions, pExpr, MAKER_ASSERTION) ;
}
void MiaRuleParser::parseTemporary(MiaActions* pActions, AiPair* pExpr) {
	parseMakeActions(pActions, pExpr, MAKER_TEMPORARY) ;
}
void MiaRuleParser::parseRetract(MiaActions* pActions, AiPair* pExpr) {
	parseMakeActions(pActions, pExpr, MAKER_RETRACTION) ;
}
void MiaRuleParser::parsePropose(MiaActions* pActions, AiPair* pExpr) {
	parseMakeActions(pActions, pExpr, MAKER_PROPOSAL) ;
}
void MiaRuleParser::parseDestroy(MiaActions* pActions, AiPair* pExpr) {
	AiSymbol* pSymbol = asSymbol(cadr(pExpr)) ; //strip 'destroy'
	MiaDestroyAction* pAction = new MiaDestroyAction(pActions, pSymbol) ;
	pAction->create() ;
	pActions->addAction(pAction) ;
}
void MiaRuleParser::parsePrint(MiaActions* pActions, AiPair* pExpr) {
	AiSymbol* pKeyword = asSymbol(car(pExpr)) ; //
	pExpr = pairCdr(pExpr) ;
	MiaPrintAction* pAction = new MiaPrintAction(pActions, pExpr) ;
	pAction->create() ;
	pActions->addAction(pAction) ;
}
//
void MiaRuleParser::parseAction(MiaActions* pActions, BwCell* pExpr) {
	if(isSymbol(pExpr)) {
		parseSymbolAction(pActions, pExpr) ;
		return ;
	}
	//else
	AiPair* pList = asPair(pExpr) ;
	BwCell* pHead = car(asPair(pExpr)) ;
	if(pHead == SYM_ASSERT)
		parseAssert(pActions, pList) ;
	else
	if(pHead == SYM_TEMPORARY)
		parseTemporary(pActions, pList) ;
	else
	if(pHead == SYM_RETRACT)
		parseRetract(pActions, pList) ;
	else
	if(pHead == SYM_PROPOSE)
		parsePropose(pActions, pList) ;
	else
	if(pHead == SYM_DESTROY)
		parseDestroy(pActions, pList) ;
	else
	if(pHead == SYM_PRINT)
		parsePrint(pActions, pList) ;
	else
		parseMakeAction(pActions, pList, MAKER_ASSERTION) ;
}
//
void MiaRuleParser::parseActions(MiaActions* pActions, AiPair* pExprs) {
	if(pExprs == NULL)
		return ;
	BwCell* pExpr = NULL ;
	bool success = false ;
	for(; pExprs != NIL ; pExprs = pairCdr(pExprs)) {
		pExpr = car(pExprs) ;
		parseAction(pActions, pExpr) ;
	}
}
MiaRhs* MiaRuleParser::parseRhs(AiPair* pExpr) {
	if(pExpr == NULL)
		return NULL ;
	MiaRhs* pRhs = new MiaRhs(p_reader->getRuleFactory(), pExpr) ;
	pRhs->create() ;
	parseActions(pRhs, pExpr) ;
	return pRhs ;
}
///
void MiaRuleParser::addCondition(BwCell* pCondition) {
	AiPair* pConditions = getConditions() ;
	AiPair* pPair = consa(pCondition) ;
	if(isNil(pConditions))
		pConditions = pPair ;
	else
		pConditions = appendList(pConditions, pPair) ;
	p_conditions = pConditions ;
}
//These are on a per match basis
void MiaRuleParser::addMatchSuccessAction(BwCell* pAction) {
	AiPair* pActions = getMatchSuccess() ;
	AiPair* pPair = consa(pAction) ;
	if(isNil(pActions))
		pActions = pPair ;
	else
		pActions = appendList(pActions, pPair) ;
	p_matchSuccess = pActions ;
}
void MiaRuleParser::addMatchFailureAction(BwCell* pAction) {
	AiPair* pActions = getMatchFailure() ;
	AiPair* pPair = consa(pAction) ;
	if(isNil(pActions))
		pActions = pPair ;
	else
		pActions = appendList(pActions, pPair) ;
	p_matchFailure = pActions ;
}
//These are for success or failure of the whole rule.
void MiaRuleParser::addSuccessAction(BwCell* pAction) {
	AiPair* pActions = getSuccess() ;
	AiPair* pPair = consa(pAction) ;
	if(isNil(pActions))
		pActions = pPair ;
	else
		pActions = appendList(pActions, pPair) ;
	p_success = pActions ;
}
void MiaRuleParser::addFailureAction(BwCell* pAction) {
	AiPair* pActions = getFailure() ;
	AiPair* pPair = consa(pAction) ;
	if(isNil(pActions))
		pActions = pPair ;
	else
		pActions = appendList(pActions, pPair) ;
	p_failure = pActions ;
}
bool isArrow(BwCell* pCell) {
	return pCell == SYM_ARROW || pCell == SYM_FATARROW ;
}
AiPair* MiaRuleParser::parseRuleSuccess(AiPair* pExpr) {
	for(; (pExpr != NIL) && (!isArrow(car(pExpr))) ; pExpr = pairCdr(pExpr)) {
		addSuccessAction(car(pExpr)) ;
	}
	return pExpr ;
}
AiPair* MiaRuleParser::parseRuleFailure(AiPair* pExpr) {
	for(; (pExpr != NIL) && (!isArrow(car(pExpr))) ; pExpr = pairCdr(pExpr)) {
		addFailureAction(car(pExpr)) ;
	}
	return pExpr ;
}
AiPair* MiaRuleParser::parseRuleMatchSuccess(AiPair* pExpr) {
	for(; (pExpr != NIL) && (!isArrow(car(pExpr))) ; pExpr = pairCdr(pExpr)) {
		addMatchSuccessAction(car(pExpr)) ;
	}
	return pExpr ;
}
AiPair* MiaRuleParser::parseRuleMatchFailure(AiPair* pExpr) {
	for(; (pExpr != NIL) && (!isArrow(car(pExpr))) ; pExpr = pairCdr(pExpr)) {
		addMatchFailureAction(car(pExpr)) ;
	}
	return pExpr ;
}
AiPair* MiaRuleParser::parseRuleConditions(AiPair* pExpr) {
	for(; (pExpr != NIL) && (!isArrow(car(pExpr))) ; pExpr = pairCdr(pExpr)) {
		addCondition(car(pExpr)) ;
	}
	return pExpr ;
}
AiPair* MiaRuleParser::parseRuleHead(AiPair* pExpr) {
	AiSymbol* pKey = asSymbol(car(pExpr)) ; //> { rule
	bwAssert(pKey == SYM_RULE) ;

	pExpr = pairCdr(pExpr) ; //advance

	return pExpr ;
}
AiPair* MiaRuleParser::parseRuleBody(AiPair* pExpr) {
	AiPair* pBody = parseRuleConditions(pExpr) ;
	return pBody ;
}
AiPair* MiaRuleParser::parseRuleTail(AiPair* pExpr) {
	if(pExpr == NULL)
		return pExpr ;
	BwCell* pCell = car(pExpr) ;
	if(pCell == SYM_ARROW) {
		pExpr = asPair(cdr(pExpr)) ; //skip over the -->
		if(isNil(p_matchSuccess))
			pExpr = parseRuleMatchSuccess(pExpr) ;
		else
			pExpr = parseRuleMatchFailure(pExpr) ;
	}
	else
	if(pCell == SYM_FATARROW) {
		pExpr = asPair(cdr(pExpr)) ; //skip over the ==>
		if(isNil(p_success))
			pExpr = parseRuleSuccess(pExpr) ;
		else
			pExpr = parseRuleFailure(pExpr) ;
	}
	return parseRuleTail(pExpr) ;
}
AiPair* MiaRuleParser::parse(AiPair* pExpr) {
	//Phase 1
	pExpr = parseRuleHead(pExpr) ;
	pExpr = parseRuleBody(pExpr) ;
	pExpr = parseRuleTail(pExpr) ;
	//Phase 2
	MiaRuleFactory* pRuleFactory = p_reader->getRuleFactory() ;
	MiaLhs* pLhs = parseLhs(getConditions()) ;
	pRuleFactory->setLhs(pLhs) ;
	//
	MiaRhs* pSuccessRhs = parseRhs(getSuccess()) ;
	pRuleFactory->setSuccessRhs(pSuccessRhs) ;
	MiaRhs* pFailureRhs = parseRhs(getFailure()) ;
	pRuleFactory->setFailureRhs(pFailureRhs) ;
	//
	MiaRhs* pMatchSuccessRhs = parseRhs(getMatchSuccess()) ;
	pRuleFactory->setMatchSuccessRhs(pMatchSuccessRhs) ;
	MiaRhs* pMatchFailureRhs = parseRhs(getMatchFailure()) ;
	pRuleFactory->setMatchFailureRhs(pMatchFailureRhs) ;

	return pExpr ;
}
//
//MiaMethodParser
//
AiPair* MiaMethodParser::parseRule(AiPair* pExpr) {

	setRuleFactory(new MiaRuleFactory()) ;
	MiaRuleParser parser(p_reader) ;
	pExpr = parser.parse(pExpr) ;
	methodFactory().addRuleFactory(getRuleFactory()) ;

	return pExpr ;
}
AiPair* MiaMethodParser::parseRules(AiPair* pExpr) {
	AiPair* pRuleExpr ;
	for(; pExpr != NIL ; pExpr = pairCdr(pExpr)) {
		pRuleExpr = asPair(car(pExpr)) ;
		parseRule(pRuleExpr) ;
	}
	return pExpr ;
}
AiPair* MiaMethodParser::parse(AiPair* pExpr) {
	AiSymbol* pKeyWord = asSymbol(car(pExpr)) ; //Get keyword
	pExpr = asPair(cdr(pExpr)) ; //move ahead
	AiSymbol* pName = asSymbol(car(pExpr)) ; //Get name
	pExpr = asPair(cdr(pExpr)) ; //move ahead
	AiPair* pSignature = asPair(car(pExpr)) ; //Get signature of operator
	pExpr = asPair(cdr(pExpr)) ; //move ahead

	MiaMethodFactory *pFactory = new MiaMethodFactory(p_reader->getDomain(), pName, pSignature) ;
	p_reader->setMethodFactory(pFactory) ;
	parseRules(pExpr) ;
	getDomain().addMethodFactory(&methodFactory()) ;
	return pExpr ;
}
AiPair* MiaDomainParser::parse(AiPair* pExpr) {
	AiSymbol* pKeyWord = asSymbol(car(pExpr)) ; //Get keyword
	pExpr = asPair(cdr(pExpr)) ; //move ahead
	AiSymbol* pName = asSymbol(car(pExpr)) ; //Get name
	pExpr = asPair(cdr(pExpr)) ; //move ahead
	AiPair* pSignature = asPair(car(pExpr)) ; //Get signature of operator
	pExpr = asPair(cdr(pExpr)) ; //move ahead

	MiaDomainPtr pParentDomain = &p_reader->getDomain() ;
	MiaDomainPtr pDomain = new MiaDomain(pParentDomain.get(), pName, pSignature) ;
	p_reader->pushDomain(pDomain.get()) ;
	parseItems(asPair(pExpr)) ;
	pParentDomain->addDomain(pDomain.get()) ;
	p_reader->popDomain() ;
	return NULL ;
}
//
//MiaProblemParser
//
AiPair* MiaProblemParser::parse(AiPair* pExpr) {
	AiSymbol* pKeyWord = asSymbol(car(pExpr)) ; //Get keyword
	pExpr = pairCdr(pExpr) ; //move ahead
	AiSymbol* pName = asSymbol(car(pExpr)) ; //Get name
	pExpr = pairCdr(pExpr) ; //move ahead
	//
	MiaProblem* pProblem = k_agent().createProblem(pName) ;
	MiaMind* pRoot = pProblem->getRoot() ;
	p_reader->pushMind(pRoot) ;
	parseItems(asPair(pExpr)) ;
	p_reader->popMind() ;
	k_agent().addProblem(pProblem) ;
	return NULL ;
}
//
//MiaFrameParser
//
AiPair* MiaFrameParser::parse(AiPair* pExpr) {
	pExpr = pairCdr(pExpr) ; //move ahead
	AiSymbol* pSymbol = asSymbol(car(pExpr)) ; //Get name
	bwString nameStr = pSymbol->getString() ;
	if(nameStr[0] != '/')
		nameStr = "/" + nameStr ;
	AiSymbol* pName = new AiSymbol(nameStr) ;
	//
	pExpr = pairCdr(pExpr) ; //move ahead
	//
	MiaMind* pMind = new MiaFrame(&getMind(), pName) ;
	pMind->create() ; //don't wan't to schedule it!!!
	p_reader->pushMind(pMind) ;
	parseItems(asPair(pExpr)) ;

	p_reader->popMind() ;
	return NULL ;
}
//
//MiaTopicParser
//
AiPair* MiaTopicParser::parse(AiPair* pExpr) {
	AiSymbol* pKeyWord = asSymbol(car(pExpr)) ;
	pExpr = asPair(cdr(pExpr)) ; //move ahead
	BwCell* pName = car(pExpr) ;
	MiaFact* pSubject = NULL ;
	if(!isPair(pName)) {
		pSubject = internId(asSymbol(pName)) ;
		//MiaTopic* pTopic = new MiaTopic(state().getSpace(), pSubject, makeId(pSubject, state().getSpace())) ;
		MiaTopic* pTopic = new MiaTopic(getMind(), pSubject) ;
		getMind().addTopic(pTopic) ;
	}
	else
		pSubject = parseFact(asPair(pName)) ; //it's a signature

	pExpr = asPair(cdr(pExpr)) ; //move ahead
	if(pExpr != NIL)
		parseShortFacts(pSubject, pExpr) ;
	return NULL ;
}
//
//MiaFileParser
//
AiPair* MiaFileParser::parse(AiPair *pExpr) {
	parseItem(pExpr) ;
	return NULL ;
}
//
//MiaParser
//
MiaFact* MiaParser::parseFact(AiPair* pExpr) {
	MiaMethod method(getMind()) ;
	MiaBinder& binder = *method.getBinder() ;

	MiaAssertion assertion ;
	assertion.makeSimple(binder, pExpr) ;

	MiaFact* pResult = NULL ;
	AiPair* pResults = assertion.getResults() ;
	if( pResults != NULL ) {
		pResult = asFact(car(pResults)) ;
		assertion.output(binder) ;
	}
	return pResult ;
}
void MiaParser::parseShortFact(MiaFact* pSubject, AiPair* pExpr) {
	MiaMethod method(getMind()) ;
	MiaBinder& binder = *method.getBinder() ;

	MiaAssertion assertion(pSubject) ;
	assertion.makeShort(binder, pExpr) ;
	assertion.output(binder) ;
}
void MiaParser::parseShortFacts(MiaFact* pSubject, AiPair* pExpr) {
	AiPair* pShort = NULL ;
	for(; pExpr != NIL ; pExpr = pairCdr(pExpr)) {
		pShort = pairCar(pExpr) ;
		parseShortFact(pSubject, pShort) ;
	}
}
void MiaParser::parseItems(AiPair *pExpr) {
	for(; pExpr != NIL ; pExpr = pairCdr(pExpr)) {
		parseItem(pairCar(pExpr)) ;
	}
}
void MiaParser::parseItem(AiPair *pExpr) {
	ThingTT cellType = getTT(pExpr) ;
	switch(cellType) {
		case TT_SYMBOL :
			bwAssert(0) ;
			break ;
		case TT_PAIR : {
			BwCell* pHead = car(asPair(pExpr)) ;

			if(pHead == SYM_METHOD) {
				MiaMethodParser parser(p_reader) ;
				parser.parse(pExpr) ;
			}
			else if(pHead == SYM_TOPIC) {
				MiaTopicParser parser(p_reader) ;
				parser.parse(pExpr) ;
			}
			else if(pHead == SYM_DOMAIN) {
				MiaDomainParser parser(p_reader) ;
				parser.parse(pExpr) ;
			}
			else if(pHead == SYM_PROBLEM) {
				MiaProblemParser parser(p_reader) ;
				parser.parse(pExpr) ;
			}
			else if(pHead == SYM_FRAME) {
				MiaFrameParser parser(p_reader) ;
				parser.parse(pExpr) ;
			}
			else
				parseShortFact(getMind().getId(), pExpr) ; //assume this is an augmentation of current frame.
		}
			break ;
		default: throw BwException();
			break;
	}
}
