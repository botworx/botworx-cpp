#ifndef _MiaDomain_H
#define _MiaDomain_H

#include "MiaFactory.h"
#include <bwai/AiPair.h>

class MiaBinder ;
class MiaMethodFactory ;
class MiaMind ;
class MiaPattern ;
class MiaDomain ;
class MiaCall ;

typedef std::vector<MiaDomain*> MiaDomainContainer ;
typedef MiaDomainContainer::iterator MiaDomainIter ;

typedef boost::intrusive_ptr<MiaMethodFactory> MiaMethodFactoryPtr ;
typedef boost::intrusive_ptr<MiaDomain> MiaDomainPtr ;

typedef std::pair<MiaPattern, MiaMethodFactoryPtr> MiaMethodPatternPair ;
typedef std::vector<MiaMethodPatternPair> MiaMethodPatternMap ;
typedef MiaMethodPatternMap::iterator MiaMethodPatternMapIter ;
//
typedef std::pair<AiSymbolPtr, MiaMethodFactoryPtr> MiaMethodFactoryMapPair ;
typedef std::vector<MiaMethodFactoryMapPair> MiaMethodFactoryMap ;
typedef MiaMethodFactoryMap::iterator MiaMethodFactoryMapIter ;
//
typedef std::pair<AiSymbolPtr, MiaMethodFactoryPtr> MiaMethodSymbolPair ;
typedef std::vector<MiaMethodSymbolPair> MiaMethodSymbolMap ;
typedef MiaMethodSymbolMap::iterator MiaMethodSymbolMapIter ;
//
typedef std::pair<AiSymbolPtr, MiaDomainPtr> MiaDomainSymbolPair ;
typedef std::vector<MiaDomainSymbolPair> MiaDomainSymbolMap ;
typedef MiaDomainSymbolMap::iterator MiaDomainSymbolMapIter ;
//
//MiaDomain
//
class MiaDomain : public MiaFactory {
public:
	MiaDomain(MiaDomain* pParent, AiSymbol* pName, AiPair* pSignature) ;
	void *operator new(size_t count) throw() ;
	virtual void purge() ;
	~MiaDomain() ;
	//
	void produceMethods(MiaMind& mind, MiaFact *pFact) ;
	//
	void addMethodFactory(MiaMethodFactory* pFactory) ;
	MiaMethodFactory* getDefaultModeFactory() { return m_methodFactories[0].second.get() ; }
	MiaMethodFactory* findMethodFactory(AiSymbol* pSymbol) ;
	//
	void addDomain(MiaDomain* pDomain) ;
	MiaDomain* findDomain(AiSymbol* pSymbol) ;
	//
	//Data Members
	MiaDomain* p_parent ;
	MiaMethodFactoryMap m_methodFactories ;
	//Data Members
	MiaMethodPatternMap m_methodPatternMap ; //to spawn meta-ops
	MiaMethodSymbolMap m_methodSymbolMap ;
	//
	MiaDomainSymbolMap m_domainSymbolMap ;
	MiaDomainContainer m_domains ;
} ;
//
//MiaDomainKit
//
#include <bwai/AiKit.h>

class MiaDomainKit : public AiPoolKitT<AiKit, MiaDomain> {
public:
	MiaDomainKit(AiKit*  pSuperKit, AiKitInfo *pKitInfo) 
		: AiPoolKitT<AiKit, MiaDomain>(MIA_KT_DOMAIN, pSuperKit, pKitInfo) {}
} ;
DECLARE_KITINFO(MiaDomainKit) ;
//
//MiaDomain
//
inline void* MiaDomain::operator new(size_t size) throw() {
#if AI_OPTION_POOLING
	return k_domain().rent() ;
#else
	return BW_USERMALLOC(size, MIA_TT_DOMAIN) ;
#endif
}

#endif//_MiaDomain_H
