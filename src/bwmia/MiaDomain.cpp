/*Botworx AI - An Artificial Intelligence Framework
Copyright (C) 2004  Kurtis Fields. See BotworxAI_License.txt for details.
*/
#include "stdafx.h"

#include <bwmia/MiaState.h>
#include <bwmia/MiaDomain.h>
#include <bwmia/MiaMethod.h>
#include <bwmia/MiaBinder.h>
#include <bwmia/MiaIdentifier.h>
#include <bwmia/MiaPattern.h>
//
#include <bwai/AiInt.h>
//
//MiaDomain
//
void MiaDomain::purge() {
	MiaDomain::~MiaDomain() ;
	#if AI_OPTION_POOLING
		k_domain().release(this) ;
	#else
		BW_USERFREE(this, MIA_TT_DOMAIN) ;
	#endif
}
//
MiaDomain::MiaDomain(MiaDomain* pParent, AiSymbol* pSymbol, AiPair* pSignature) 
: MiaFactory(pSymbol, MIA_TT_DOMAIN) {
	p_parent = pParent ;
}
MiaDomain::~MiaDomain() {
}
void MiaDomain::addMethodFactory(MiaMethodFactory* pFactory) {
	AiSymbol* pSymbol = pFactory->getSymbol() ;
	m_methodFactories.push_back(MiaMethodFactoryMapPair(pSymbol, pFactory)) ;
	//
	AiPair* pSignature = pFactory->getSignature() ;
	if(pSignature != NULL)
		m_methodPatternMap.push_back(MiaMethodPatternPair(MiaPattern(pSignature), pFactory)) ;
}
MiaMethodFactory*  MiaDomain::findMethodFactory(AiSymbol* pSymbol) {
	for(MiaMethodFactoryMapIter iter = m_methodFactories.begin() ; iter != m_methodFactories.end() ; ++iter) {
		if((*iter).first == pSymbol)
			return (*iter).second.get() ;
	}
	//else
	return NULL ;
}
void MiaDomain::addDomain(MiaDomain* pDomain) {
	AiSymbol* pSymbol = pDomain->getSymbol() ;
	m_domainSymbolMap.push_back(MiaDomainSymbolPair(pSymbol, pDomain)) ;
}
MiaDomain*  MiaDomain::findDomain(AiSymbol* pSymbol) {
	for(MiaDomainSymbolMapIter iter = m_domainSymbolMap.begin() ; iter != m_domainSymbolMap.end() ; ++iter) {
		if((*iter).first == pSymbol)
			return (*iter).second.get() ;
	}
	//else
	return NULL ;
}
void MiaDomain::produceMethods(MiaMind& mind, MiaFact *pFact) {
	for(MiaMethodPatternMapIter iter = m_methodPatternMap.begin() ; iter != m_methodPatternMap.end() ; ++iter) {
		MiaPattern& pattern = (*iter).first ;
		if(!pattern.matchSignature(pFact)) 
			continue ;
		MiaMethodFactory* pFactory = (*iter).second.get() ;
		AiPair* pSignature = pFactory->getSignature() ;
		MiaMethod method(mind) ;
		MiaBinder& binder = *method.getBinder() ;
		MiaFactoid result(*pFact) ;
		if(pattern.match(binder, result)) {
			mind.spawnMethod(binder, pFactory, pFact) ;
		}
	}
	if(p_parent != NULL)
		p_parent->produceMethods(mind, pFact) ;
}
//
//MiaDomainKit Meta
//
DEFINE_KITTYPE(MiaDomainKit) ;

TYPEINFO_NONE(MiaDomainKit) ;
NO_KITINFO(MiaDomainKit) ;

KITINFO("MiaDomainKit", MIA_KT_DOMAIN, MiaDomainKit) ;
