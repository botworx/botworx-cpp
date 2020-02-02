/*Botworx AI - An Artificial Intelligence Framework
Copyright (C) 2004  Kurtis Fields. See BotworxAI_License.txt for details.
*/
#ifndef _MiaParser_h
#define _MiaParser_h

class MiaParser {
public:
	MiaParser(MiaReader* pReader) : p_reader(pReader) {}
	//Accessors
	MiaMind& getMind() { return p_reader->getMind() ; }
	MiaDomain& getDomain() { return p_reader->getDomain() ; }
	MiaMethodFactory& methodFactory() { return *(p_reader->getMethodFactory()) ; }
	//
	void setRuleFactory(MiaRuleFactory* pFactory) { p_reader->setRuleFactory(pFactory) ; }
	MiaRuleFactory* getRuleFactory() { return p_reader->getRuleFactory() ; }
	MiaRuleFactory& ruleFactory() { return *(p_reader->getRuleFactory()) ; }
	//
	virtual AiPair* parse(AiPair* pExpr) = 0 ;
	virtual void parseItems(AiPair *pExpr) ;
	virtual void parseItem(AiPair *pExpr) ;
	//
	MiaFact* parseFact(AiPair* pExpr) ;
	void parseShortFact(MiaFact* pSubject, AiPair* pExpr) ;
	void parseShortFacts(MiaFact* pSubject, AiPair* pExpr) ;
	//Data Member
	MiaReader* p_reader ;
};
class MiaFileParser : public MiaParser {
public:
	MiaFileParser(MiaReader* pReader) : MiaParser(pReader) {}
	virtual AiPair* parse(AiPair* pExpr) ;
};
class MiaDomainParser : public MiaParser {
public:
	MiaDomainParser(MiaReader* pReader) : MiaParser(pReader) {}
	virtual AiPair* parse(AiPair* pExpr) ;
};
class MiaProblemParser : public MiaParser {
public:
	MiaProblemParser(MiaReader* pReader) : MiaParser(pReader) {}
	virtual AiPair* parse(AiPair* pExpr) ;
};
class MiaFrameParser : public MiaParser {
public:
	MiaFrameParser(MiaReader* pReader) : MiaParser(pReader) {}
	virtual AiPair* parse(AiPair* pExpr) ;
};
class MiaTopicParser : public MiaParser {
public:
	MiaTopicParser(MiaReader* pReader) : MiaParser(pReader) {}
	virtual AiPair* parse(AiPair* pExpr) ;
};
////////////////
class MiaMethodParser : public MiaParser {
public:
	MiaMethodParser(MiaReader* pReader) : MiaParser(pReader) {}
	virtual AiPair* parse(AiPair* pExpr) ;
	//
	AiPair* parseRules(AiPair* pExpr) ;
	AiPair* parseRule(AiPair* pExpr) ;
};
class MiaRuleParser : public MiaParser {
public:
	MiaRuleParser(MiaReader* pReader) : MiaParser(pReader) {
		p_conditions = NULL ;
		p_matchSuccess = NULL ;
		p_matchFailure = NULL ;
		p_success = NULL ;
		p_failure = NULL ;
	}
	virtual AiPair* parse(AiPair* pExpr) ;
	//
	AiPair* parseRuleHead(AiPair* pExpr) ;
	AiPair* parseRuleBody(AiPair* pExpr) ;
	AiPair* parseRuleTail(AiPair* pExpr) ;
	//
	AiPair* parseRuleMatchSuccess(AiPair* pExpr) ;
	AiPair* parseRuleMatchFailure(AiPair* pExpr) ;
	AiPair* parseRuleSuccess(AiPair* pExpr) ;
	AiPair* parseRuleFailure(AiPair* pExpr) ;
	AiPair* parseRuleConditions(AiPair* pExpr) ;
	AiPair* parseRule(AiPair* pExpr) ;
	//
	void parseSymbolCondition(MiaConditions* pConditions, BwCell* pExpr) ;
	void parseRelationalTest(MiaConditions* pConditions, AiPair* pExpr) ;
	void parseMatchTest(MiaConditions* pConditions, AiPair* pExpr) ;
	void parseTest(MiaConditions* pConditions, AiPair* pExpr) ;
	void parseCondition(MiaConditions* pConditions, BwCell* pExpr) ;
	void parseConjunction(MiaConditions* pConditions, AiPair* pExprs) ;
	void parseNegation(MiaConditions* pConditions, AiPair* pExprs) ;
	void parseDisjunction(MiaConditions* pConditions, AiPair* pExprs) ;
	void parseTopicSelect(MiaConditions* pConditions, AiPair* pExpr) ;
	void parseSpaceSelect(MiaConditions* pConditions, AiPair* pExpr) ;
	void parseConditions(MiaConditions* pConditions, AiPair* pExprs) ;
	void parseFramedConditions(MiaConditions* pConditions, AiPair* pExpr) ;
	MiaLhs* parseLhs(AiPair* pExprs) ;
	//
	void parseSymbolAction(MiaActions* pActions, BwCell* pExpr) ;
	void parseSimpleMakeAction(MiaActions* pActions, AiPair* pExpr, makerType type) ;
	void parseComplexMakeAction(MiaActions* pActions, AiPair* pExpr, makerType type) ;
	void parseTopicMakeAction(MiaActions* pActions, AiPair* pExpr, makerType type) ;
	void parseMakeAction(MiaActions* pActions, BwCell* pExpr, makerType type) ;
	void parseMakeActions(MiaActions* pActions, AiPair* pExprs, makerType type) ;
	void parseAssert(MiaActions* pActions, AiPair* pExpr) ;
	void parseTemporary(MiaActions* pActions, AiPair* pExpr) ;
	void parseRetract(MiaActions* pActions, AiPair* pExpr) ;
	void parsePropose(MiaActions* pActions, AiPair* pExpr) ;
	//
	void parseDestroy(MiaActions* pActions, AiPair* pExpr) ;
	void parsePrint(MiaActions* pActions, AiPair* pExpr) ;

	void parseAction(MiaActions* pActions, BwCell* pExpr) ;
	void parseActions(MiaActions* pActions, AiPair* pExprs) ;
	MiaRhs* parseRhs(AiPair* pExprs) ;
	//
	//
	void addCondition(BwCell* pCondition) ;
	void addMatchSuccessAction(BwCell* pAction) ;
	void addMatchFailureAction(BwCell* pAction) ;
	void addSuccessAction(BwCell* pAction) ;
	void addFailureAction(BwCell* pAction) ;
	//Access
	AiPair* getConditions() { return p_conditions.get() ; }
	AiPair* getSuccess() { return p_success.get() ; }
	AiPair* getFailure() { return p_failure.get() ; }
	AiPair* getMatchSuccess() { return p_matchSuccess.get() ; }
	AiPair* getMatchFailure() { return p_matchFailure.get() ; }
	//Data Members
	AiPairPtr p_conditions ; //list of conditions needed to fire this rule
	AiPairPtr p_matchSuccess ; //success actions
	AiPairPtr p_matchFailure ; //failure actions
	AiPairPtr p_success ; //success actions
	AiPairPtr p_failure ; //failure actions
};
#endif //_MiaParser_h
