#ifndef _AiMeta_h
#define _AiMeta_h

#include "AiMetabit.h"

class AiType ;
class AiSlot ;
struct AiTypeInfo ;
//
//AiMeta
//
class AiMeta : public AiMetabit {
public:
	AiMeta(AiTypeInfo& pInfo, ThingTT typeId) ;
	virtual void init(AiTypeInfo& pInfo) ;
	//
	void initMetabits(AiMbInfoZs& infozs) ;
	virtual AiMetabit* initMetabit(AiMbInfoZ& zInfo) ;
	void buildMetabits(AiMbInfoZs& infozs) ;
	AiMetabit* buildMetabit(AiMbInfoZ& zInfo) ;
	//
	AiSlot* buildSlot(AiSlotInfo& pInfo) ;
	void initSlots() ;
	//
	void addSlot(AiSlot* pSlot) ;
	AiSlot* findSlot(AiSymbol* pSym) ;
	AiPair* getSlots() { return p_slots.get() ; }
	//
	BwCell* setSlotVal(BwCell* pCell, AiSymbol* pSym, BwCell* pVal) ;
	BwCell* getSlotVal(BwCell* pCell, AiSymbol* pSym) ;
	//
	AiString* getDescription() { return p_description.get() ; }
	//Data
	AiStringPtr p_description ;
	//
	AiPairPtr p_slots ;
} ;

#define isMeta(X) (isTT(X,TT_META))
#define ofMeta(X) (ofTT(X, TT_META))
#define asMeta(C) ((AiMeta*)C)

#endif//_AiMeta_h