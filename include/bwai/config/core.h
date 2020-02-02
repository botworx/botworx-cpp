/*Botworx AI - An Artificial Intelligence Framework
Copyright (C) 2004  Kurtis Fields. See BotworxAI_License.txt for details.
*/
#ifndef _Ai_core_H
#define _Ai_core_H

#include <bwai/AiCore.h>

#if AI_OPTION_TLS_CORE
	extern boost::thread_specific_ptr<AiCore> g_core ;
#else
	extern AiCore* g_core ;
#endif

#endif //_Ai_core_H