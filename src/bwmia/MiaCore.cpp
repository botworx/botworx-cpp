/*Botworx AI - An Artificial Intelligence Framework
Copyright (C) 2004  Kurtis Fields. See BotworxAI_License.txt for details.
*/
#include "stdafx.h"

#include <bwmia/MiaFrame.h>
#include <bwmia/MiaPrinter.h>
#include <bwmia/MiaIdentifier.h>
#include <bwmia/MiaBinder.h>

#include <bwmia/MiaRule.h>
#include <bwmia/MiaTopic.h>
#include <bwmia/MiaState.h>
#include <bwmia/MiaSpace.h>
//
// MiaCore
//
MiaCore::MiaCore(AiKit* pKit, AiKitInfo *pKitInfo) : AxlCore(pKit, pKitInfo), m_mailBox(NULL)  {
	m_mailBox.setOwner(this) ;
	p_factKit = NULL ;
	p_identifierKit = NULL ;
	p_topicKit = NULL ;
	p_stateKit = NULL ;
	p_methodKit = NULL ;
	p_ruleKit = NULL ;
	p_domainKit = NULL ;
}
void MiaCore::doPostDisable(bool sleeping) {
	AxlCore::doPostDisable(sleeping) ;
}
void MiaCore::doConfig() {
	//This is the place to add kits, if not using meta data.
	AxlCore::doConfig() ;
	createSubjects() ;
}
void MiaCore::doPostConfig() {
	AxlCore::doPostConfig() ;
	createCommander() ;
	k_printer().flush() ; //f6:TODO:?:should we implement a flush function on Agents/Cores themselves?
}
void MiaCore::createSymbols() {
	AxlCore::createSymbols() ;
	//Condition Symbols
	SYM_NOT = intern("NOT") ;
	SYM_OR = intern("OR") ;
	SYM_AND = intern("AND") ;
	SYM_SELECT = intern("SELECT") ;
	SYM_STAR = intern("*") ;
	SYM_UNKNOWN = intern("UNKNOWN") ;
	//Relational Symbols
	SYM_EQ = intern("=") ;
	SYM_NEQ = intern("<>") ;
	SYM_LT = intern("<") ;
	SYM_LE = intern("<=") ;
	SYM_GT = intern(">") ;
	SYM_GE = intern(">=") ;
	//
	SYM_NAME = intern("NAME") ;
	SYM_TYPE = intern("TYPE") ;
	SYM_TOPIC = intern("TOPIC") ;
	SYM_IN = intern("IN") ;
	//
	SYM_METHOD = intern("METHOD") ;
	SYM_STATE = intern("STATE") ;
	SYM_DOMAIN = intern("DOMAIN") ;
	SYM_PROBLEM = intern("PROBLEM") ;
	SYM_AGENT = intern("AGENT") ;
	SYM_FRAME = intern("FRAME") ;
	SYM_SPACE = intern("SPACE") ;
	SYM_MODE = intern("MODE") ;
	//Rule Symbols
	SYM_RULE = intern("RULE") ;
	SYM_ARROW = intern("-->") ;
	SYM_FATARROW = intern("==>") ;
	//MakeAction Symbols
	SYM_ASSERT = intern("ASSERT") ;
	SYM_TEMPORARY = intern("TEMPORARY") ;
	SYM_RETRACT = intern("RETRACT") ;
	SYM_PROPOSE = intern("PROPOSE") ;
	SYM_CREATE = intern("CREATE") ;
	SYM_DESTROY = intern("DESTROY") ;
	SYM_PRINT = intern("PRINT") ;
	//Action/Event Symbols
	SYM_INPUT = intern("INPUT") ;
	SYM_MAIN = intern("MAIN") ;
	SYM_OUTPUT = intern("OUTPUT") ;

	//Operator Success/Failure
	SYM_RETURN = intern("RETURN") ;
	//State Success/Failure
	SYM_SUCCEED	= intern("SUCCEED") ;
	SYM_FAIL = intern("FAIL") ;

	SYM_BREAK = intern("BREAK") ;
	SYM_MONITOR = intern("MONITOR") ;
	SYM_HALT = intern("HALT") ;
	SYM_SOLUTION = intern("SOLUTION") ;
	//
	SYM_COST = intern("COST") ;
	SYM_BENEFIT = intern("BENEFIT") ;
	SYM_SCRIPT = intern("SCRIPT") ;
	//Property Symbols
	PSYM_SUBJECT = intern(".SUBJECT") ;
	PSYM_LINK = intern(".LINK") ;
	PSYM_VALUE = intern(".VALUE") ;
	PSYM_NAME = intern(".NAME") ;
	PSYM_ID = intern(".ID") ;
	PSYM_AGENT = intern(".AGENT") ;
	PSYM_STATE = intern(".STATE") ;
	PSYM_DOMAIN = intern(".DOMAIN") ;
	PSYM_PROBLEM = intern(".PROBLEM") ;
	PSYM_THIS = intern(".THIS") ;
	PSYM_THOUGHT = intern(".THOUGHT") ;
	PSYM_GOAL = intern(".GOAL") ;
	PSYM_PARENT = intern(".PARENT") ;
	//Special Logic Symbols
	LSYM_WILDCARD = intern("$$") ;
}
void MiaCore::createSubjects() {
	//need to do this one manually
	SUBJECT_NAME = new MiaFact(NULL, NULL, SYM_NAME) ;
	//SUBJECT_NAME->setSubject(SUBJECT_NAME) ;
	//SUBJECT_NAME->setLink(SUBJECT_NAME) ; //basically (name name name) the name of name is name
	SetGlobalVal(SYM_NAME, SUBJECT_NAME) ;

	//TODO:need to release these on destruction!
	SUBJECT_AGENT = new MiaIdentifier(PSYM_AGENT) ;
	SUBJECT_TYPE = new MiaIdentifier(SYM_TYPE) ;
	SUBJECT_TOPIC = new MiaIdentifier(SYM_TOPIC) ;
	SUBJECT_SCRIPT = new MiaIdentifier(SYM_SCRIPT) ;
	SUBJECT_COST = new MiaIdentifier(SYM_COST) ;
	SUBJECT_BENEFIT = new MiaIdentifier(SYM_BENEFIT) ;
	//
	SUBJECT_IN = new MiaIdentifier(SYM_IN) ;
}
void MiaCore::addKit(BwKit *pKit) throw() {
	KitTT kitTypeID = static_cast<AiKit*>(pKit)->getKitTypeID() ;
	switch(kitTypeID) {
		case MIA_KT_FACT :
			bwAssert(p_factKit == NULL) ;
			p_factKit = static_cast<MiaFactKit*>(pKit) ;
			break ;
		case MIA_KT_IDENTIFIER :
			bwAssert(p_identifierKit == NULL) ;
			p_identifierKit = static_cast<MiaIdentifierKit*>(pKit) ;
			break ;
		case MIA_KT_STATE :
			bwAssert(p_stateKit == NULL) ;
			p_stateKit = static_cast<MiaStateKit*>(pKit) ;
			break ;
		case MIA_KT_METHOD :
			bwAssert(p_methodKit == NULL) ;
			p_methodKit = static_cast<MiaMethodKit*>(pKit) ;
			break ;
		case MIA_KT_RULE :
			bwAssert(p_ruleKit == NULL) ;
			p_ruleKit = static_cast<MiaRuleKit*>(pKit) ;
			break ;
		case MIA_KT_TOPIC :
			bwAssert(p_topicKit == NULL) ;
			p_topicKit = static_cast<MiaTopicKit*>(pKit) ;
			break ;
		case MIA_KT_DOMAIN :
			bwAssert(p_domainKit == NULL) ;
			p_domainKit = static_cast<MiaDomainKit*>(pKit) ;
			break ;
		default:
			break;
	}
	AxlCore::addKit(pKit) ;
}
