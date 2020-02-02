/*Botworx AI - An Artificial Intelligence Framework
Copyright (C) 2004  Kurtis Fields. See BotworxAI_License.txt for details.
*/
#ifndef _AiFloat_H
#define _AiFloat_H

#include "AiNumber.h"
//
//AiFloat
//
class AiFloat : public AiNumber {
public:
	AiFloat(float value) : AiNumber(TT_FLOAT) {
		m_value = value ;
	}
	void *operator new(size_t count) throw() ;
	virtual void purge() ;
	//Data Members
	float m_value ;
} ;
inline bool isFloat(BwCell* pCell) { return pCell->getTypeId() == TT_FLOAT ; }
#define asFloat(C) ((AiFloat*)C)
#define asConstFloat(C) (static_cast<const AiFloat*>(C))
//
//AiFloatKit
//
#include "AiKit.h"

class AiFloatKit : public AiPoolKitT<AiKit, AiFloat> {
public:
	AiFloatKit(AiKit*  pSuperKit, AiKitInfo *pKitInfo) 
		: AiPoolKitT<AiKit, AiFloat>(KT_FLOAT, pSuperKit, pKitInfo) {}
} ;
DECLARE_KITINFO(AiFloatKit) ;
//
//AiFloat
//
inline void* AiFloat::operator new(size_t count) throw() {
#if AI_OPTION_POOLING
	return k_float().rent() ;
#else
	return BW_USERMALLOC(sizeof(AiFloat), TT_FLOAT) ;
#endif
}

AiNumber* AiFloat_add(AiFloat *pThis, AiNumber *pThat) ;


#endif //_AiFloat_H