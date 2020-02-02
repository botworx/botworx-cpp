#ifndef _AxlFn_h
#define _AxlFn_h

#include <bwai/AiKit.h>
#include "AxlForm.h"

//
//AxlFnType
//
class AxlFnType : public AxlFormType {
public:
	AxlFnType(AiSymbol *pSym, AiPair *pArgs, AiPair *pBody, ThingTT typeId = TT_FNTYPE) ;
	void* operator new(size_t count) throw() {
		return BW_USERMALLOC(count, TT_FNTYPE) ;
	}
	virtual void purge() ;
	void createArgs(AiPair* pArgs) ;
	//
	virtual void* produce(ThingLength length) ;
} ;
#define isFnType(C) (asMeta(C)->m_thingTT == TT_FNTYPE)
#define asFnType(C) ((AxlFnType*)C)
//
//AxlFn
//
class AxlFn : public AxlForm {
public:
	AxlFn(AxlFnType *pMeta, ThingLength length) : AxlForm(pMeta, length) {
	}
	virtual AxlOpcode exec() ;
	AiPair* getActions() { return p_actions.get() ; }
	//Data Members
	AiPairPtr p_actions ;
} ;
//
//AxlDefunBx
//
class DefunBx : public AxlBx {
public:
	DefunBx(AxlBxType *pMeta, ThingLength length) : AxlBx(pMeta, length) {
	}
	virtual AxlOpcode exec() ;
} ;
//
//AxlFnKit
//
class AxlFnKit : public AiKit {
public:
	AxlFnKit(AiKit* pSuperKit, AiKitInfo *pKitInfo)
		: AiKit(AXL_KT_FN, pSuperKit, pKitInfo) {
	}
} ;
DECLARE_KITINFO(AxlFnKit) ;

#endif //_AxlFn_h
