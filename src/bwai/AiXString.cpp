/*Botworx AI - An Artificial Intelligence Framework
Copyright (C) 2004  Kurtis Fields. See BotworxAI_License.txt for details.
*/
#include "stdafx.h"

#include <bwai/AiXString.h>
//
void AiXString::purge() {
	AiXString::~AiXString() ;
#if AI_OPTION_POOLING
	k_xstring().release(this) ;
#else
	BW_USERFREE(this, TT_XSTRING) ;
#endif
}
//
//AiXString Meta
//
DEFINE_AIVALUETYPE(AiXString) ;
MBINFO_NONE(AiXString) ;
//
//AiXStringKit Meta
//
DEFINE_KITTYPE(AiXStringKit) ;

TYPEINFO_BEGIN(AiXStringKit)
	TYPEINFO("XSTRING-TYPE", AiXString, TT_XSTRING, MBF_DEFAULT)
TYPEINFO_END

NO_KITINFO(AiXStringKit) ;

KITINFO("xstring", KT_XSTRING, AiXStringKit) ;

