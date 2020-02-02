/*Botworx AI - An Artificial Intelligence Framework
Copyright (C) 2004  Kurtis Fields. See BotworxAI_License.txt for details.
*/
#ifndef _Ai_access_H
#define _Ai_access_H

#if !defined(_access_H)
	#define _access_H
	inline AiCore& k_core() { return *g_core ; }

	inline AiPrinter& k_printer() { return *(k_core().p_printer) ; }
	inline AiPrinter& k_logger() { return *(k_core().p_logger) ; }

#endif

#include <bwcore/config/access.h>

inline AiBufferKit& k_buffer() { return *(k_core().p_bufferKit) ; }
inline AiNumberKit& k_number() { return *(k_core().p_numberKit) ; }
inline AiIntKit& k_int() { return *(k_core().p_intKit) ; }
inline AiFloatKit& k_float() { return *(k_core().p_floatKit) ; }

inline AiPairKit& k_pair() { return *(k_core().p_pairKit) ; }
inline AiMultiKit& k_multi() { return *(k_core().p_multiKit) ; }
inline AiSymbolKit& k_symbol() { return *(k_core().p_symbolKit) ; }
inline AiStringKit& k_string() { return *(k_core().p_stringKit) ; }
inline AiXStringKit& k_xstring() { return *(k_core().p_xstringKit) ; }
//
inline BwFileKit& k_file() { return *(k_core().p_fileKit) ; }

#endif //_Ai_access_H