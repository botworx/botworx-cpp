/*Botworx AI - An Artificial Intelligence Framework
Copyright (C) 2004  Kurtis Fields. See BotworxAI_License.txt for details.
*/
#ifndef _MiaCore_H
#define _MiaCore_H

#include <bwaxl/AxlCore.h>
#include <bwmessaging/BwMailCenter.h>

class MiaFrame ;
class BwIoSlot ;
class MiaFact ;
class MiaCommander ;
class MiaMindMailBox ;

typedef std::list<MiaFrame*> MiaFrameContainer ;
typedef MiaFrameContainer::iterator MiaFrameIter ;

class MiaCore : public AxlCore {
public:
	MiaCore(AiKit* pSuperKit, AiKitInfo *pKitInfo) ;
	virtual void doPostDisable(bool sleeping = true) ;
	virtual void doConfig() ;
	virtual void doPostConfig() ;
	virtual void addKit(BwKit *pKit) throw() ;
	//
	virtual void createSymbols() ;
	virtual void createSubjects() ;
	//
	void addFrame(MiaFrame* pFrame) { m_frames.push_back(pFrame) ; }
	MiaFrameContainer& getFrames() { return m_frames ; }
	MiaFrameContainer m_frames ;
	//
	virtual void createCommander() = 0 ; //agent implements this
	////////
	//Kits
	MiaFactKit* p_factKit ;
	MiaIdentifierKit* p_identifierKit ;
	MiaStateKit* p_stateKit ;
	MiaMethodKit* p_methodKit ;
	MiaRuleKit* p_ruleKit ;
	MiaTopicKit* p_topicKit ;
	MiaDomainKit* p_domainKit ;
	//Messaging
	BwMailSlot& getInSlot() { return *p_inSlot ; }
	BwMailSlot& getOutSlot() { return *p_outSlot ; }
	BwMailSlot& getEventSlot() { return *p_eventSlot ; }
	BwMailSlot& getLogSlot() { return *p_logSlot ; }
	BwIoSlot& getIoSlot() { return *p_ioSlot ; }
	//Data Members
	//Messaging
	BwMailSlot *p_inSlot ;
	BwMailSlot *p_outSlot ;
	BwMailSlot *p_eventSlot ;
	BwMailSlot *p_logSlot ;
	BwIoSlot *p_ioSlot ;
	//Messaging
	BwMailBox& getMailBox() { return m_mailBox ; }
	BwMailCenter& getMailCenter() { return m_mailCenter ; }
	//
	MiaMindMailBox& getMindMailBox() { return *p_mindMailBox ; }
	MiaMindMailBox* p_mindMailBox ;
	//Data Members
	//Messaging
	BwMailBox m_mailBox ;
	BwMailCenter m_mailCenter ;
	//
	MiaCommander* p_commander ; //scripting agent wrapper
	//Conditional Symbols
	AiSymbol* p_sym_not ;
	AiSymbol* p_sym_or ;
	AiSymbol* p_sym_and ;
	AiSymbol* p_sym_select ;
	AiSymbol* p_sym_star ;
	AiSymbol* p_sym_unknown ;
	//Relational Symbols
	AiSymbol* p_sym_eq ;
	AiSymbol* p_sym_neq ;
	AiSymbol* p_sym_lt ;
	AiSymbol* p_sym_le ;
	AiSymbol* p_sym_gt ;
	AiSymbol* p_sym_ge ;
	//Symbols
	AiSymbol* p_sym_name ;
	AiSymbol* p_sym_type ;
	AiSymbol* p_sym_topic ;
	AiSymbol* p_sym_in ;
	AiSymbol* p_sym_method ;
	AiSymbol* p_sym_state ;
	AiSymbol* p_sym_domain ;
	AiSymbol* p_sym_problem ;
	AiSymbol* p_sym_agent ;
	AiSymbol* p_sym_frame ;
	AiSymbol* p_sym_space ;
	AiSymbol* p_sym_mode ;
	AiSymbol* p_sym_rule ;
	AiSymbol* p_sym_assert ;
	AiSymbol* p_sym_temporary ;
	AiSymbol* p_sym_retract ;
	AiSymbol* p_sym_propose ;
	AiSymbol* p_sym_create ;
	AiSymbol* p_sym_destroy ;
	AiSymbol* p_sym_print ;
	AiSymbol* p_sym_arrow ;
	AiSymbol* p_sym_fatarrow ;
	//Action/Event Symbols
	AiSymbol* p_sym_input ;
	AiSymbol* p_sym_main ;
	AiSymbol* p_sym_output ;
	AiSymbol* p_sym_return ;

	AiSymbol* p_sym_failure ;
	AiSymbol* p_sym_succeed ;
	AiSymbol* p_sym_fail ;
	AiSymbol* p_sym_break ;
	AiSymbol* p_sym_monitor ;
	AiSymbol* p_sym_halt ;
	AiSymbol* p_sym_solution ;
	//Misc Symbols
	AiSymbol* p_sym_script ;
	AiSymbol* p_sym_cost ;
	AiSymbol* p_sym_benefit ;
	//Property Symbols
	AiSymbol* p_psym_subject ;
	AiSymbol* p_psym_link ;
	AiSymbol* p_psym_value ;
	AiSymbol* p_psym_name ;
	AiSymbol* p_psym_agent ;
	AiSymbol* p_psym_state ;
	AiSymbol* p_psym_domain ;
	AiSymbol* p_psym_task ;
	AiSymbol* p_psym_this ;
	AiSymbol* p_psym_id ;
	AiSymbol* p_psym_thought ;
	AiSymbol* p_psym_goal ;
	AiSymbol* p_psym_parent ;
	//
	AiSymbol* p_lsym_wildcard ;
	//Facts
	MiaFact* p_subject_agent ;
	MiaFact* p_subject_name ;
	MiaFact* p_subject_type ;
	MiaFact* p_subject_topic ;
	MiaFact* p_subject_script ;
	MiaFact* p_subject_cost ;
	MiaFact* p_subject_benefit ;
	//
	MiaFact* p_subject_in ;
} ;
#define asMiaCore(X) (static_cast<MiaCore*>(X)))
//
#define SYM_NOT (k_core().p_sym_not)
#define SYM_OR (k_core().p_sym_or)
#define SYM_AND (k_core().p_sym_and)
#define SYM_SELECT (k_core().p_sym_select)
#define SYM_STAR (k_core().p_sym_star) //TODO:should go down into AiCore
#define SYM_UNKNOWN (k_core().p_sym_unknown)
//
#define SYM_EQ (k_core().p_sym_eq)
#define SYM_NEQ (k_core().p_sym_neq)
#define SYM_LT (k_core().p_sym_lt)
#define SYM_LE (k_core().p_sym_le)
#define SYM_GT (k_core().p_sym_gt)
#define SYM_GE (k_core().p_sym_ge)
//
#define SYM_METHOD (k_core().p_sym_method)
#define SYM_STATE (k_core().p_sym_state)
#define SYM_DOMAIN (k_core().p_sym_domain)
#define SYM_PROBLEM (k_core().p_sym_problem)
#define SYM_AGENT (k_core().p_sym_agent)
#define SYM_FRAME (k_core().p_sym_frame)
#define SYM_SPACE (k_core().p_sym_space)
#define SYM_MODE (k_core().p_sym_mode)
#define SYM_RULE (k_core().p_sym_rule)
#define SYM_ASSERT  (k_core().p_sym_assert)
#define SYM_TEMPORARY  (k_core().p_sym_temporary)
#define SYM_RETRACT (k_core().p_sym_retract)
#define SYM_PROPOSE (k_core().p_sym_propose)
#define SYM_CREATE (k_core().p_sym_create)
#define SYM_DESTROY (k_core().p_sym_destroy)
#define SYM_PRINT (k_core().p_sym_print)
#define SYM_ARROW (k_core().p_sym_arrow)
#define SYM_FATARROW (k_core().p_sym_fatarrow)
//Mode Symbols
#define SYM_INPUT (k_core().p_sym_input)
#define SYM_MAIN (k_core().p_sym_main)
#define SYM_OUTPUT (k_core().p_sym_output)
#define SYM_RETURN (k_core().p_sym_return)
//Action Symbols
#define SYM_SUCCEED (k_core().p_sym_succeed)
#define SYM_FAIL (k_core().p_sym_fail)
#define SYM_BREAK (k_core().p_sym_break)
#define SYM_MONITOR (k_core().p_sym_monitor)
#define SYM_HALT (k_core().p_sym_halt)
#define SYM_SOLUTION (k_core().p_sym_solution)
//
#define	PSYM_SUBJECT (k_core().p_psym_subject)
#define	PSYM_LINK (k_core().p_psym_link)
#define	PSYM_VALUE (k_core().p_psym_value)
#define	PSYM_NAME (k_core().p_psym_name)
#define	PSYM_ID (k_core().p_psym_id)
#define PSYM_AGENT (k_core().p_psym_agent)
#define	PSYM_STATE (k_core().p_psym_state)
#define	PSYM_DOMAIN (k_core().p_psym_domain)
#define	PSYM_PROBLEM (k_core().p_psym_task)
#define	PSYM_THIS (k_core().p_psym_this)
#define	PSYM_THOUGHT (k_core().p_psym_thought)
#define	PSYM_GOAL (k_core().p_psym_goal)
#define	PSYM_PARENT (k_core().p_psym_parent)
//
#define	LSYM_WILDCARD (k_core().p_lsym_wildcard)

//Linking Mind Symbols
#define SYM_NAME (k_core().p_sym_name)
#define SYM_TYPE (k_core().p_sym_type)
#define SYM_TOPIC (k_core().p_sym_topic)
#define SYM_IN (k_core().p_sym_in)
#define SYM_SCRIPT (k_core().p_sym_script)
#define SYM_COST (k_core().p_sym_cost)
#define SYM_BENEFIT (k_core().p_sym_benefit)

//Linking Mind Identities
#define SUBJECT_AGENT (k_core().p_subject_agent)
#define SUBJECT_NAME (k_core().p_subject_name)
#define SUBJECT_TYPE (k_core().p_subject_type)
#define SUBJECT_TOPIC (k_core().p_subject_topic)
#define SUBJECT_SCRIPT (k_core().p_subject_script)
#define SUBJECT_COST (k_core().p_subject_cost)
#define SUBJECT_BENEFIT (k_core().p_subject_benefit)
//
#define SUBJECT_IN (k_core().p_subject_in)

#endif //_MiaCore_H
