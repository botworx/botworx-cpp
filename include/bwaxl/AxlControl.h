#ifndef _AxlControl_h
#define _AxlControl_h

#include "AxlBx.h"
//
//CondBx
//
class CondBx : public AxlBx {
public:
	CondBx(AxlBxType *pMeta, ThingLength length) : AxlBx(pMeta, length) {
	}
	//
	virtual AxlOpcode exec() ;
	AiPair* getConds() { return p_conds.get() ; }
	AiPair* getActions() { return p_actions.get() ; }
	//Data Members
	AiPairPtr p_conds ;
	AiPairPtr p_actions ;
} ;
//
//AndBx
//
class AndBx : public AxlBx {
public:
	AndBx(AxlBxType *pMeta, ThingLength length) : AxlBx(pMeta, length) {
	}
	//
	virtual AxlOpcode exec() ;
	AiPair* getConds() { return p_conds.get() ; }
	//AiPair* p_conds ;
	AiPairPtr p_conds ;
} ;

//
//OrBx
//
class OrBx : public AxlBx {
public:
	OrBx(AxlBxType *pMeta, ThingLength length) : AxlBx(pMeta, length) {
	}
	//
	virtual AxlOpcode exec() ;
	AiPair* getConds() { return p_conds.get() ; }
	//Data Members
	//AiPair* p_conds ;
	AiPairPtr p_conds ;
} ;
//
//TagBodyBx
//
class TagBodyBx : public AxlBx {
public:
	TagBodyBx(AxlBxType *pMeta, ThingLength length) : AxlBx(pMeta, length) {
		m_xdx = 0 ;
	}
	//
	virtual AxlOpcode exec() ;
	AiPair* getForms() { return p_forms.get() ; }
	//Data Members
	AiPairPtr p_forms ;
} ;
//
//WhileBx
//
class WhileBx : public AxlBx {
public:
	WhileBx(AxlBxType *pMeta, ThingLength length) : AxlBx(pMeta, length) {
	}
	//
	virtual AxlOpcode exec() ;
	BwCell* getTest() { return p_test.get() ; }
	AiPair* getBody() { return p_body.get() ; }
	AiPair* getActions() { return p_actions.get() ; }
	//Data Members
	BwCellPtr p_test ;
	AiPairPtr p_body ;
	AiPairPtr p_actions ;  //what's left to evaluate.
} ;
////////////////////////
//AxlControlKit
//
class AxlControlKit : public AiKit {
public:
	AxlControlKit(AiKit* pSuperKit, AiKitInfo *pKitInfo)
		: AiKit(AXL_KT_CONTROL, pSuperKit, pKitInfo) {
	}
} ;
DECLARE_KITINFO(AxlControlKit) ;

#endif //_AxlControl_h
