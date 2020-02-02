#include "stdafx.h"

//
//AiKit
//
AiKit::AiKit(KitTT typeID, AiKit*  pSuperKit, AiKitInfo *pKitInfo) : BwKit(pSuperKit) {
	m_kitTypeID = typeID ;
	setKitInfo(pKitInfo) ;
	p_superKit = pSuperKit ;
}
AiKit::~AiKit() {
}
void AiKit::doPostDisable(bool sleeping) {
	BwKit::doPostDisable(sleeping) ;
}
void AiKit::doCreate(const BwPartInfo& info) {
	BwKit::doCreate(info) ;
}
void AiKit::doConfig() {
	buildKits(getKitInfo()) ;
	buildMetas(getKitInfo()) ;
	BwKit::doConfig() ;
	initMetas(getKitInfo().p_metaInfoZ) ;
}
AiKitInfo* AiKit::findExtendingKitInfo(AiKitInfo& pInfo) {
	AiKitInfoRefs &kitInfos = pInfo.p_kitRefs;
	for(auto pKitInfo: kitInfos) {
		if(asTypeInfo(pInfo).p_superInfo == pKitInfo)
			return &pInfo ;
	}
	if(asTypeInfo(pInfo).p_superInfo != NULL)
		return findExtendingKitInfo(asKitInfo(*asTypeInfo(pInfo).p_superInfo)) ;

	return NULL ;
}
void AiKit::buildKits(AiKitInfo& pInfo) {
	if(pInfo.p_superInfo != NULL)
		buildKits(asKitInfo(*pInfo.p_superInfo)) ;
		
	AiKitInfoRefs &kitInfos = pInfo.p_kitRefs;
	AiKit *pKit = NULL ;
	AiKitType *pKitType = NULL ;
	for(auto pKitInfo: kitInfos) {
		if(findExtendingKitInfo((*pKitInfo)) != NULL)
			continue ;
		pKitType = asAiKitType(pKitInfo->produce(*pKitInfo)) ; //TODO:leaking types here!!!
		pKit = pKitType->produce(this, pKitInfo) ;
		addKit(pKit) ;
	}
}
void AiKit::buildMetas(AiKitInfo& pKitInfo) {
	if(asTypeInfo(pKitInfo).p_superInfo != NULL)
		buildMetas(asKitInfo(*asTypeInfo(pKitInfo).p_superInfo)) ;

	AiMeta* pMeta = NULL ;
	for(auto &pInfo: pKitInfo.p_metaInfoZ) {
		pMeta = k_core().buildType(pInfo) ;
		pMeta->buildMetabits(getMbitz(pInfo)) ;
	}
}
void AiKit::initMetas(AiTypeInfos typeInfos) {
	for(auto &pInfo: typeInfos) {
		k_core().initType(pInfo) ;
	}
}