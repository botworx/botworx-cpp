/*Botworx AI - An Artificial Intelligence Framework
Copyright (C) 2004  Kurtis Fields. See BotworxAI_License.txt for details.
*/
#include "stdafx.h"

#include <bwai/AiSlot.h>
#include <bwai/AiBlob.h>
//
//AiSlot
//
void AiSlot::purge() {
	AiSlot::~AiSlot() ;
	BW_USERFREE(this, TT_SLOT) ;
}
//
void AiSlot::init() {
	AiMetabit::init() ;
	AiSlotInfo *pInfo = (AiSlotInfo*)p_info ;
	p_elMeta = TYPEDIR(pInfo->m_elTT) ;
	AiBlobType* pMeta = asBlobType(p_parent) ;
	ThingSize oldBSize = pMeta->m_thingBSize ;
	ThingSize elSize = getThingSize(p_elMeta) ;
	ThingSize newBSize = oldBSize + elSize ;
	pMeta->m_thingBSize = newBSize ;
	//f6:newstuff
	pMeta->m_thingSize = pMeta->m_thingASize + pMeta->m_thingBSize ;

	ThingCount elCount = pMeta->m_bFldCount ;
	pMeta->m_bFldCount++ ;
	m_elPos = elCount ;
}
BwCell* AiSlot::setVal(AiBlobType* pMeta, AiBlob* pBlob, BwCell* pVal) {
	ThingPos elPos = m_elPos ;
	ThingSize thingSize = getThingASize(pMeta) ;
	BwCell **pNextVal = NULL ;
	//TODO: ... assuming homogenous here ...
	if(pMeta->f_reverseIndexed)
		pNextVal = ((BwCell**) ( ((char*)pBlob) + thingSize + ( (pBlob->m_length-(elPos+1)) * (sizeof(BwCell*)) ) ) ) ;
	else
		pNextVal = (BwCell**)( ((char*)pBlob) + thingSize + elPos ) ;

	removeRef(*pNextVal) ;
	addRef(pVal) ;
	*pNextVal = pVal ;
	return pVal ;
}
//
BwCell* AiSlot::getVal(AiBlobType* pMeta, AiBlob* pBlob) {
	ThingSize elPos = m_elPos ;
	ThingSize thingSize = getThingASize(pMeta) ;
	BwCell **pNextVal = NULL ;
	//TODO: ... assuming homogenous here ...
	if(pMeta->f_reverseIndexed)
		pNextVal = ((BwCell**) ( ((char*)pBlob) + thingSize + ( (pBlob->m_length-(elPos+1)) * (sizeof(BwCell*)) ) ) ) ;
	else
		pNextVal = (BwCell**)( ((char*)pBlob) + thingSize + elPos ) ;

	return *pNextVal ;
}
