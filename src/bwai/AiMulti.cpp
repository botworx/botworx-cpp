/*Botworx AI - An Artificial Intelligence Framework
Copyright (C) 2004  Kurtis Fields. See BotworxAI_License.txt for details.
*/
#include "stdafx.h"

#include <bwai/AiMulti.h>
//
//AiMulti
//
void AiMulti::purge() {
	AiMulti::~AiMulti() ;
#if AI_OPTION_POOLING
	k_multi().release(this) ;
#else
	BW_USERFREE(this, TT_MULTI) ;
#endif
}
//
//AiMulti Meta
//
DEFINE_AIVALUETYPE(AiMulti) ;
MBINFO_NONE(AiMulti) ;
//
//AiMultiKit Meta
//
DEFINE_KITTYPE(AiMultiKit) ;

TYPEINFO_BEGIN(AiMultiKit)
	TYPEINFO("MULTI-TYPE", AiMulti, TT_MULTI, MBF_DEFAULT)
TYPEINFO_END

NO_KITINFO(AiMultiKit) ;

KITINFO("multi", KT_MULTI, AiMultiKit) ;

