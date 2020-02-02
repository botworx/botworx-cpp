/*Botworx AI - An Artificial Intelligence Framework
Copyright (C) 2004  Kurtis Fields. See BotworxAI_License.txt for details.
*/
#include "stdafx.h"
//
//AiPair
//
void AiPair::purge() {
	AiPair::~AiPair() ;
#if AI_OPTION_POOLING
	k_pair().release(this) ;
#else
	BW_USERFREE(this, TT_PAIR) ;
#endif
}
//
//AiPair Meta
//
DEFINE_AIVALUETYPE(AiPair) ;

MBINFO_NONE(AiPair) ;
//
//AiPairKit Meta
//
DEFINE_KITTYPE(AiPairKit) ;

TYPEINFO_BEGIN(AiPairKit)
	TYPEINFO("PAIR-TYPE", AiPair, TT_PAIR, MBF_DEFAULT)
TYPEINFO_END

NO_KITINFO(AiPairKit) ;

KITINFO("pair", KT_PAIR, AiPairKit) ;

