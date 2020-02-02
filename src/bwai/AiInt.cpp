/*Botworx AI - An Artificial Intelligence Framework
Copyright (C) 2004  Kurtis Fields. See BotworxAI_License.txt for details.
*/
#include "stdafx.h"

#include <bwai/AiInt.h>
//
//AiInt
//
void AiInt::purge() {
	AiInt::~AiInt() ;
#if AI_OPTION_POOLING
	k_int().release(this) ;
#else
	BW_USERFREE(this, TT_INT) ;
#endif
}
//
//AiInt Meta
//
DEFINE_AIVALUETYPE(AiInt) ;
MBINFO_NONE(AiInt) ;
//
//AiIntKit Meta
//
DEFINE_KITTYPE(AiIntKit) ;

TYPEINFO_BEGIN(AiIntKit)
	TYPEINFO("INT-TYPE", AiInt, TT_INT, MBF_DEFAULT)
TYPEINFO_END

NO_KITINFO(AiIntKit) ;

KITINFO("int", KT_INT, AiIntKit) ;
