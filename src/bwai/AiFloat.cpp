/*Botworx AI - An Artificial Intelligence Framework
Copyright (C) 2004  Kurtis Fields. See BotworxAI_License.txt for details.
*/
#include "stdafx.h"

#include <bwai/AiFloat.h>
//
//AiFloat
//
void AiFloat::purge() {
	AiFloat::~AiFloat() ;
#if AI_OPTION_POOLING
	k_float().release(this) ;
#else
	BW_USERFREE(this, TT_FLOAT) ;
#endif
}
//
//AiFloat Meta
//
DEFINE_AIVALUETYPE(AiFloat) ;
MBINFO_NONE(AiFloat) ;
//
//AiFloatKit Meta
//
DEFINE_KITTYPE(AiFloatKit) ;

TYPEINFO_BEGIN(AiFloatKit)
	TYPEINFO("FLOAT-TYPE", AiFloat, TT_FLOAT, MBF_DEFAULT)
TYPEINFO_END

NO_KITINFO(AiFloatKit) ;

KITINFO("int", KT_FLOAT, AiFloatKit) ;
