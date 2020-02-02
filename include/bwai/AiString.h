#ifndef _AiString_H
#define _AiString_H

class AiString : public BwCell {
public:
	AiString(const bwString& str) : BwCell(TT_STRING) {
		m_string = str ;
	}
	//For derived classes...
	AiString(ThingTT thingType, const bwString& str) : BwCell(thingType) {
		m_string = str ;
	}
	void *operator new(size_t count) throw() ;
	virtual void purge() ;
	//
	const bwString& getString() const { return m_string ; }
	const char* getCstring() const { return m_string.c_str() ; }
	//Data Members
protected:
	bwString m_string ;
} ;
//
inline bool isString(BwCell* pCell) { return pCell->getTypeId() == TT_STRING ; }
#define asString(C) (static_cast<AiString*>(C))
#define asConstString(C) (static_cast<const AiString*>(C))
//
//
#include "AiKit.h"
class AiStringKit : public AiPoolKitT<AiKit, AiString> {
public:
	AiStringKit(AiKit*  pSuperKit, AiKitInfo *pKitInfo) 
		: AiPoolKitT<AiKit, AiString>(KT_STRING, pSuperKit, pKitInfo) {}
} ;
DECLARE_KITINFO(AiStringKit) ;
///////////////////
inline void* AiString::operator new(size_t count) throw() {
#if AI_OPTION_POOLING
	return k_string().rent() ;
#else
	return BW_USERMALLOC(sizeof(AiString), TT_STRING) ;
#endif
}

extern RawHash AiString_rawHash(AiString* pThis) ;
extern bool AiString_rawComparison(AiString* pThis, BwCell* pThat) ;

#endif //_AiString_H