#ifndef _AxlLet_H
#define _AxlLet_H

#include <bwai/AiKit.h>
#include "AxlForm.h"
//
//AxlLetType
//
class AxlLetType : public AxlFormType {
public:
	AxlLetType(AiSymbol *pSym, AiPair *pArgs, AiPair *pBody, ThingTT typeId = TT_LETTYPE) ;
	void* operator new(size_t count) throw() {
		return BW_USERMALLOC(count, TT_LETTYPE) ;
	}
	virtual void purge() ;
	void createArgs(AiPair* pArgs) ;
	virtual void* produce(ThingLength length) ;
} ;
#define isLetMeta(C) (asMeta(C)->m_thingTT == TT_FNTYPE)
#define asLetMeta(C) ((AxlLetType*)C)
//
//AxlLet
//
class AxlLet : public AxlForm {
public:
	AxlLet(AxlLetType *pMeta, ThingLength length) : AxlForm(pMeta, length) {
	}
	virtual AxlOpcode exec() ;
	AiPair* getActions() { return p_actions.get() ; }
	//Data Members
	AiPairPtr p_actions ;
} ;
//
//DefLet
//
class DefLet : public AxlBx {
public:
	DefLet(AxlBxType *pMeta, ThingLength length) : AxlBx(pMeta, length) {
	}
	virtual AxlOpcode exec() ;
} ;
//
//AxlLetKit
//
class AxlLetKit : public AiKit {
public:
	AxlLetKit(AiKit* pSuperKit, AiKitInfo *pKitInfo)
		: AiKit(AXL_KT_FN, pSuperKit, pKitInfo) {
	}
} ;
DECLARE_KITINFO(AxlLetKit) ;

#endif //_AxlLet_H
