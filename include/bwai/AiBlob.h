#ifndef _AiBlob_H
#define _AiBlob_H

#include "AiType.h"

//
//AiBlobType
//
class AiBlobType : public AiValueType {
public:
	AiBlobType(AiTypeInfo& pInfo, ThingTT typeId = TT_BLOBTYPE) : AiValueType(pInfo, typeId) {
		m_isBlobType = true ;
		f_reverseIndexed = false ;
		m_thingBSize = 0 ;
		m_bFldCount = 0 ;
	}
	void *operator new(size_t count) throw() {
		return BW_USERMALLOC(count, TT_BLOBTYPE) ;
	}
	virtual void purge() ;
	//
	ThingSize calcSize(ThingLength length) {
		ThingSize thingSize = getThingSize(this) ;
		size_t arraySize = sizeof(BwCell*) * length ;
		return thingSize + arraySize ;
	}
	AiSlot* createBFld(AiSlotInfo &pInfo) {
		ThingTT slotMI = pInfo.m_mbTT ;
		AiSlot *pSlot = NULL ;
		pSlot = new AiSlot(this, pInfo, slotMI) ;
		addSlot(pSlot) ;
		return pSlot ;
	}
	//Data Members
	bool f_reverseIndexed ;
	ThingSize m_thingBSize ;
	int m_bFldCount ;
} ;
#define asBlobType(C) (static_cast<AiBlobType*>(C))
#define isBlobType(X) (X->m_isBlobType)
//
//AiBlobTypeT
//
template <typename C>
class AiBlobTypeT : public AiBlobType {
public:
	AiBlobTypeT(AiTypeInfo& pInfo) : AiBlobType(pInfo) {
	}
	static AiType* instantiate(AiTypeInfo& pInfo) {
		AiBlobTypeT<C>* pType = new AiBlobTypeT<C>(pInfo) ;
		pType->registerSelf(pInfo, s_typeId) ;
		return pType ;
	}
	//Data Members
	static ThingTT s_typeId ;
} ; 
#define DEFINE_AIBLOBTYPE(C) _DEFINE_TYPE(C, AiBlobTypeT)

class AiBlob : public BwCell {
public:
	AiBlob(AiBlobType* pMeta, ThingLength length) : BwCell(pMeta->m_thingTT) {
		m_isBlob = true ;
		p_meta = pMeta ;
		m_length = length ;
	}
	~AiBlob() ;
	AiBlobType* getMeta() const { return p_meta.get() ; }
	ThingSize getSize() {
		AiBlobType *pMeta = getMeta() ;
		ThingSize size = pMeta->calcSize(m_length) ;
		return size ;
	}
	void setSlotVal(AiSymbol* pSym, BwCell* pVal) {
		getMeta()->setSlotVal(this, pSym, pVal) ;
	}
	BwCell* getSlotVal(AiSymbol* pSym) {
		return getMeta()->getSlotVal(this, pSym) ;
	}
	//Data Members
	AiBlobTypePtr p_meta ;
	ThingLength	m_length ;
} ;
#define asBlob(C) (static_cast<AiBlob*>(C))
#define getBlobSize(A) (A->getSize())
#define setBlobLength(A,L) (((AiBlob*)A)->m_length = L)
#define getBlobLength(A) (((AiBlob*)A)->m_length)
//
//AiBlobKit
//
class AiBlobKit : public AiKit {
public:
	AiBlobKit(AiKit*  pSuperKit, AiKitInfo *pKitInfo) 
		: AiKit(KT_BLOB, pSuperKit, pKitInfo) {}
} ;
DECLARE_KITINFO(AiBlobKit) ;
//

//
//BwCell
//
#define getCellType(C) (C->m_isBlob ? TYPEDIR(getTT(pCell)) : asBlob(pCell)->getMeta())

#endif//_AiBlob_H
