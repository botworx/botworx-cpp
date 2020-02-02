/*Botworx AI - An Artificial Intelligence Framework
Copyright (C) 2004  Kurtis Fields. See BotworxAI_License.txt for details.
*/
#include "stdafx.h"
//
//AiString
//
void AiString::purge() {
	AiString::~AiString() ;
#if AI_OPTION_POOLING
	k_string().release(this) ;
#else
	BW_USERFREE(this, TT_STRING) ;
#endif
}

//
RawHash AiString_rawHash(AiString* pThis) {
	const char *pString = pThis->getCstring();
	unsigned long	h = 0, g ;
	while(*pString)
	{
		h = (h << 4)+ *pString++ ;
		if((g = (h & 0xf0000000)))
		{
			h ^= g >> 24 ;
		}
		h &= ~g ;
	}
	return h ;
}

bool AiString_rawComparison(AiString* pThis, BwCell* pThat) {
	ThingTT cellTT = getTT(pThat) ;
	switch(cellTT) {
		case TT_STRING :
		case TT_SYMBOL : {
			AiString* pString = asString(pThat) ;
			const char *pThisRawString = pThis->getCstring();
			const char *pThatRawString = pString->getCstring();
			return strcmp(pThisRawString, pThatRawString) == 0 ;
						  }
		default :
			bwAssert(0) ;
			return false ;
	}
}
//
//AiString Meta
//
DEFINE_AIVALUETYPE(AiString) ;
MBINFO_NONE(AiString) ;
//
//AiStringKit Meta
//
DEFINE_KITTYPE(AiStringKit) ;

TYPEINFO_BEGIN(AiStringKit)
	TYPEINFO("STRING-TYPE", AiString, TT_STRING, MBF_DEFAULT)
TYPEINFO_END

NO_KITINFO(AiStringKit) ;

KITINFO("string", KT_STRING, AiStringKit) ;
