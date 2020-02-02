#ifndef _AxlForm_h
#define _AxlForm_h

#include <bwai/AiKit.h>
#include "AxlBx.h"

class AxlFormType : public AxlBxType {
public:
	AxlFormType(AiTypeInfo& pInfo, ThingTT typeId)
		: AxlBxType(pInfo, typeId) { //Uses base Bx Meta as starting point
	}
	AiPair* getBody() { return p_body.get() ; }
	AiPairPtr p_body ;
} ;
#define asFormType(M) ((AxlFormType*)M)

class AxlForm : public AxlBx {
public:
	AxlForm(AxlFormType *pMeta, ThingLength length) : AxlBx(pMeta, length) {
	}
	AiPair* getBody() { return asFormType(getMeta())->getBody() ; }
} ;
#define asForm(M) ((AxlForm*)M)
#define setFormBody(M,B) (asForm(M)->p_body = B)
#define getFormBody(M) (asForm(M)->p_body)

class AxlInnerForm : public AxlForm {
public:
} ;
////////////////////////////
//AxlFormKit
class AxlFormKit : public AiKit {
public:
	AxlFormKit(AiKit* pSuperKit, AiKitInfo *pKitInfo)
		: AiKit(AXL_KT_FORM, pSuperKit, pKitInfo) {
	}

} ;
DECLARE_KITINFO(AxlFormKit) ;

#endif //_AxlForm_h
