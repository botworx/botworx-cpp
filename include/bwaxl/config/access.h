/*Botworx AI - An Artificial Intelligence Framework
Copyright (C) 2004  Kurtis Fields. See BotworxAI_License.txt for details.
*/
#ifndef _Axl_access_H
#define _Axl_access_H

#if !defined(_access_H)
	#define _access_H
	#if AI_OPTION_TLS_CORE
		inline AxlCore& k_core() { return *static_cast<AxlCore*>(g_core.get()) ; }
	#else
		inline AxlCore& k_core() { return *static_cast<AxlCore*>(g_core) ; }
	#endif

	inline AxlPrinter& k_printer() { return *(AxlPrinter*)(k_core().p_printer) ; }
	inline AxlPrinter& k_logger() { return *(AxlPrinter*)(k_core().p_logger) ; }
#endif //

#include <bwai/config/access.h>

inline AxlFiber& k_fiber() { return *k_core().getFiber() ; }
inline AxlFiber* k_getFiber() { return k_core().getFiber() ; }


#endif //_Axl_access_H