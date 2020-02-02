/*Botworx AI - An Artificial Intelligence Framework
Copyright (C) 2004  Kurtis Fields. See BotworxAI_License.txt for details.
*/
#ifndef _AiSlot_H
#define _AiSlot_H

#include "AiMetabit.h"

class AiBlobType ;
class AiBlob ;
//
//AiSlot
//
class AiSlot : public AiMetabit {
public:
	AiSlot(AiMetabit* pParent, AiSlotInfo &pInfo, ThingTT typeId = TT_SLOT) : AiMetabit(pParent, pInfo, typeId) {
		p_elMeta = TYPEDIR(pInfo.m_elTT) ;
	}
	void *operator new(size_t count) throw() {
		return BW_USERMALLOC(count, TT_SLOT) ;
	}
	virtual void purge() ;
	virtual void init() ;
	//
	BwCell* setVal(AiBlobType* pMeta, AiBlob* pBlob, BwCell* pVal) ;
	BwCell* getVal(AiBlobType* pMeta, AiBlob* pBlob) ;
	//Data Members
	AiType* p_elMeta ; // info about actual val container
	ThingPos m_elPos ;
} ;
#define asSlot(X) (static_cast<AiSlot*>(X))
#define ofSlot(X) (ofTT(X, TT_SLOT))
#define getSlotTT(X) (ifOfTT(X, SLOT_B) : ifOfTT(X, SLOT_A) : TT_NIL )

#endif //_AiSlot_H