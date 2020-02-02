/*Botworx AI - An Artificial Intelligence Framework
Copyright (C) 2004  Kurtis Fields. See BotworxAI_License.txt for details.
*/
#include "stdafx.h"
#include <bwai/AiPrinter.h>
//
//AiSymbol
//
void AiSymbol::purge() {
	AiSymbol::~AiSymbol() ;
#if AI_OPTION_POOLING
	k_symbol().release(this) ;
#else
	BW_USERFREE(this, TT_SYMBOL) ;
#endif
}
//
//AiSymbolKit
//
void AiSymbolKit::doPostDisable(bool sleeping) {
	if(!sleeping) {
		for(AiSymbolHashMap::iterator iter = m_map.begin() ; iter != m_map.end() ; ++iter) {
			AiSymbol* pSymbol = iter->second ;
			if(pSymbol != NULL) {
				pSymbol->setVal(NULL) ;
			}
		}
		for(AiSymbolHashMap::iterator iter = m_map.begin() ; iter != m_map.end() ; ++iter) {
			AiSymbol* pSymbol = iter->second ;
			if(pSymbol != NULL) {
				pSymbol->purge() ;
				iter->second = NULL ;
			}
		}
	}
	AiKit::doPostDisable(sleeping) ;
}
AiSymbol* AiSymbolKit::internalize(const bwString& string) {
	AiSymbol* pSymbol = m_map[string] ;
	if(pSymbol== NULL) {
		pSymbol = new AiSymbol(string) ;
		pSymbol->setIsInterned(true) ;
		pSymbol->m_refCount = 100000 ;
		m_map[string] = pSymbol ;
	}
	return pSymbol ;
}
void AiSymbolKit::uninternalize(AiSymbol* pSym) {
	m_map.erase(pSym->getString()) ;
}
AiSymbol* AiSymbolKit::generateSymbol(const bwString& string) {
	/*char buffer[32] ;
	strcpy(buffer, string.c_str()) ;
	char buffer2[32] ;
	itoa(m_genSymCounter++, buffer2, 10) ;
	strcat(buffer, buffer2) ;
	size_t strLen = strlen(buffer) ;
	AiSymbol* pSymbol = internalize(buffer) ;*/
	AiPrinter printer ;
	BwStringSink printSink(true) ;
	bwString tempBuffer ;
	printSink.setString(tempBuffer) ;
	printer.pushSink(&printSink) ;
	//
	printer << string << m_genSymCounter++ ;
	AiSymbol* pSymbol = internalize(tempBuffer) ;
	//
	return pSymbol ;
}
//
//AiSymbol Meta
//
MBINFO_NONE(AiSymbol) ;
//
//AiSymbolKit Meta
//
//TODO:this is all wrong.
DEFINE_AIVALUETYPE(AiSymbol) ;

DEFINE_KITTYPE(AiSymbolKit) ;

TYPEINFO_BEGIN(AiSymbolKit)
	TYPEINFO("SYMBOL-TYPE", AiSymbol, TT_SYMBOL, MBF_DEFAULT)
TYPEINFO_END

NO_KITINFO(AiSymbolKit) ;

KITINFO("symbol", KT_SYMBOL, AiSymbolKit) ;

