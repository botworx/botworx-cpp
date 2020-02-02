/*Botworx AI - An Artificial Intelligence Framework
Copyright (C) 2004  Kurtis Fields. See BotworxAI_License.txt for details.
*/
#ifndef _Mia_access_H
#define _Mia_access_H

#if !defined(_access_H)
	#define _access_H
	#if AI_OPTION_TLS_CORE
		inline MiaCore& k_core() { return *static_cast<MiaCore*>(g_core.get()) ; }
		inline MiaAgent& k_agent() { return *((MiaAgent*)g_core.get()) ; }
	#else
		inline MiaCore& k_core() { return *static_cast<MiaCore*>(g_core) ; }
		inline MiaAgent& k_agent() { return *((MiaAgent*)g_core) ; }
	#endif

	inline MiaPrinter& k_printer() { return *(MiaPrinter*)(k_core().p_printer) ; }
	inline MiaPrinter& k_logger() { return *(MiaPrinter*)(k_core().p_logger) ; }

#endif

#include <bwaxl/config/access.h>

inline MiaFactKit& k_fact() { return *(k_core().p_factKit) ; }
inline MiaIdentifierKit& k_identifier() { return *(k_core().p_identifierKit) ; }
inline MiaStateKit& k_state() { return *(k_core().p_stateKit) ; }
inline MiaMethodKit& k_method() { return *(k_core().p_methodKit) ; }
inline MiaRuleKit& k_rule() { return *(k_core().p_ruleKit) ; }
inline MiaTopicKit& k_topic() { return *(k_core().p_topicKit) ; }
inline MiaDomainKit& k_domain() { return *(k_core().p_domainKit) ; }

#endif //_Mia_access_H