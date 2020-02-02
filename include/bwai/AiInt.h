/*Botworx AI - An Artificial Intelligence Framework
Copyright (C) 2004  Kurtis Fields. See BotworxAI_License.txt for details.
*/
#ifndef _AiInt_H
#define _AiInt_H

#include "AiNumber.h"

class AiInt : public AiNumber {
public:
	AiInt(int val) : AiNumber(TT_INT) { m_value = val ; }
	void *operator new(size_t count) throw() ;
	virtual void purge() ;
	//Data Members
	int m_value ;
} ;
#define isInt(C) (C->getTypeId() == TT_INT)
#define asInt(C) (static_cast<AiInt*>(C))
#define asConstInt(C) (static_cast<const AiInt*>(C))
/////////////
#include "AiKit.h"

class AiIntKit : public AiPoolKitT<AiKit, AiInt> {
public:
	AiIntKit(AiKit*  pSuperKit, AiKitInfo *pKitInfo) 
		: AiPoolKitT<AiKit, AiInt>(KT_INT, pSuperKit, pKitInfo) {}
} ;
DECLARE_KITINFO(AiIntKit) ;
//
inline void* AiInt::operator new(size_t count) throw() {
#if AI_OPTION_POOLING
	return k_int().rent() ;
#else
	return (AiInt*)BW_USERMALLOC(sizeof(AiInt), TT_INT) ;
#endif
}

AiNumber* AiInt_add(AiInt *pThis, AiNumber *pThat) ;

#endif //_AiInt_H