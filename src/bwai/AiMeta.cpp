/*Botworx AI - An Artificial Intelligence Framework
Copyright (C) 2004  Kurtis Fields. See BotworxAI_License.txt for details.
*/
#include "stdafx.h"

#include <bwai/AiSlot.h>
#include <bwai/AiBlob.h>

//
//AiMeta
//
AiMeta::AiMeta(AiTypeInfo& pInfo, ThingTT typeId) : AiMetabit(NULL, asMbInfo(pInfo), typeId){
	if(m_typeId != TT_KITTYPE) {
		AiSymbol* pSymbol = getName() ;
		SetGlobalVal(pSymbol, this) ;
	}
}
void AiMeta::init(AiTypeInfo& pInfo) {
	AiMetabit::init() ;
	initMetabits(getMbitz(pInfo)) ;
}
void AiMeta::initMetabits(AiMbInfoZs& infozs) {
	for(auto &pInfo: infozs) {
		initMetabit(pInfo) ;
	}
	initSlots() ;
}
AiMetabit* AiMeta::initMetabit(AiMbInfoZ& zInfo) {
	ThingTT mbTT = getMbTT(asMbInfo(zInfo).m_mbTT) ;
	AiMetabit* pMb = NULL ;
	switch(mbTT) {
		case TT_SLOT :
			break ;
		case TT_DESC :
			//TODO: ... static, dynamic if
			p_description = new AiString((char*)asMbInfo(zInfo).p_name) ;
			break ;
		default :
			bwAssert(0) ;
	}
	return pMb ; //TODO: ... what is the purpose?}
}
void AiMeta::addSlot(AiSlot* pSlot) {
	AiPair* pSlots = getSlots() ; //TODO: ... overly verbose ... good for debug though!
	AiPair* pSlotPair = consa(pSlot) ;
	if(isNil(pSlots))
		pSlots = pSlotPair ;
	else
		pSlots = appendList(pSlots, pSlotPair) ;
	p_slots = pSlots ;
}
AiSlot* AiMeta::findSlot(AiSymbol* pSym) {
	AiSlot* pSlot = NULL ;
	for(AiPair* pSlots = getSlots() ; pSlots != NULL ; pSlots = pairCdr(pSlots)) {
		pSlot = asSlot(car(pSlots)) ; // ( (name slot) (name slot) )
		if(pSlot->getName() == pSym)
			return pSlot ;
	}
	return NULL ;
}
BwCell* AiMeta::setSlotVal(BwCell* pCell, AiSymbol* pSym, BwCell* pVal) {
	AiSlot* pSlot = findSlot(pSym) ;
	bwAssert(pSlot) ;
	ThingTT slotTT = getSlotTT(getTT(pSlot)) ;
	BwCell* pNextVal = NULL ;
	switch(slotTT) {
		case SLOT_B :
			pNextVal = asSlot(pSlot)->setVal(asBlobType(this), asBlob(pCell), pVal) ;
			break ;
		default :
			bwAssert(0) ; //TODO: - implement!
	}
	return pNextVal ;
}
//
BwCell* AiMeta::getSlotVal(BwCell* pCell, AiSymbol* pSym) {
	AiSlot* pSlot = findSlot(pSym) ;
	//if(pSlot == NULL) return UNBOUND ;
	if(pSlot == NULL)
		bwAssert(0) ;

	ThingTT slotTT = getSlotTT(getTT(pSlot)) ;
	BwCell* pVal = NULL ;
	switch(slotTT) {
		case SLOT_B :
			pVal = asSlot(pSlot)->getVal(asBlobType(this), asBlob(pCell)) ;
			break ;
		default :
			bwAssert(0) ; //TODO: - implement!
	}
	return pVal ;
}
AiSlot* AiMeta::buildSlot(AiSlotInfo& pInfo) {
	ThingTT slotMI = getSlotTT(asMbInfo(pInfo).m_mbTT) ;
	AiSlot* pSlot = NULL ;
	switch(slotMI) {
		case SLOT_B :
			pSlot = asBlobType(this)->createBFld(pInfo) ;
			break ;
		default :
			bwAssert(0) ; //TODO: - implement
	}
	return pSlot ; //TODO: ... what is the purpose?
}
AiMetabit* AiMeta::buildMetabit(AiMbInfoZ& zInfo) {
	ThingTT mbTT = getMbTT(asMbInfo(zInfo).m_mbTT) ;
	AiMetabit* pMb = NULL ;
	switch(mbTT) {
		case TT_SLOT :
			pMb = buildSlot(asSlotInfo(zInfo)) ;
			break ;
		case TT_DESC :
			break ;
	}
	return pMb ; //TODO: ... what is the purpose?}
}
void AiMeta::buildMetabits(AiMbInfoZs& infozs) {
	for(auto &pInfo: infozs) {
		buildMetabit(pInfo) ;
	}
}
void AiMeta::initSlots() {
	AiSlot* pSlot = NULL ;
	for(AiPair* pSlots = getSlots() ; pSlots != NULL ; pSlots = pairCdr(pSlots)) {
		pSlot = asSlot(car(pSlots)) ; // ( (name slot) (name slot) )
		pSlot->init() ;
	}
}
