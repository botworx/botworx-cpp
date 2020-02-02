/*AXL - A Lispish interpreter for Botworx AI - An Artificial Intelligence Framework
Copyright (C) 2004  Kurtis Fields. See BotworxAI_License.txt for details.
*/
#include "stdafx.h"
#include <new>

#include <bwaxl/AxlFiber_impl.h>
#include <bwaxl/AxlFn.h>
#include <bwaxl/AxlPrinter.h>

DEFINE_AIVALUETYPE(AxlFnType) ;

void AxlFnType::purge() {
	AxlFnType::~AxlFnType() ;
	BW_USERFREE(this, TT_FNTYPE) ;
}

//TODO:what a nightmare.
extern AiTypeInfos s_AxlFnType_metaInfo;
//
//AxlFnType
//
void* AxlFnType::produce(ThingLength length) { 
	AxlFn* pThis = (AxlFn*)axlPushBx(getThingASize(this)) ;
	new(pThis) AxlFn(this, length) ;
	return pThis ;
}
void AxlFnType::createArgs(AiPair* pArgs) {
	AiSymbol* pArgSym = NULL ;
	//watchme - forgetting to set alloc type of info cost me a lot of time chasing this bug!!!
	AiSlotInfo slotInfo = MB_FORMALARG(NULL, MBF_DYNAMIC, TT_CELL) ;
	for(; pArgs != NULL ; pArgs = pairCdr(pArgs)) {
		pArgSym = asSymbol(car(pArgs)) ;
		asMbInfo(slotInfo).p_name = pArgSym->getCstring() ;
		AiSlot* pSlot = buildSlot(slotInfo) ;
		pSlot->init() ;
	}
}
//TODO:init inside constructor???
AxlFnType::AxlFnType(AiSymbol *pSym, AiPair *pArgs, AiPair *pBody, ThingTT typeId) 
	: AxlFormType(s_AxlFnType_metaInfo[0], typeId) {
	init(asTypeInfo(s_AxlFnType_metaInfo[0])) ; //TODO:what an ungodly hack.
	setMbSymbol((*this), pSym) ;
	createArgs(pArgs) ;
	p_body = pBody ;
}
//
//AxlFn
//
AxlOpcode AxlFn::exec() {
	switch(m_xdx) {
		case 0 : {
			p_actions = getBody() ;
			beginScope(this) ;
			setXdx(this, 1) ;
				 }
		case 1 : {
			AiPair* pAction = pairCar(getActions()) ;
			setXdx(this, 2) ;
			callEval1(pAction) ;
				 }
		case 2 : {
			AiPair* pActions = pairCdr(getActions()) ;
			if(pActions != NULL) {
				p_actions = pActions ;
				setXdx(this, 1) ;
				bxAgain() ;
			}
			else {
			endScope() ;
			bxEnd() ;
			}
				 }
	}
	bxError() ;
}
//TODO: - this is being used as a template of some kind...
MBINFO_NONE(AxlFnType) ;
//
TYPEINFO_BEGIN(AxlFnType)
	TYPEINFO("FN-TYPE-TYPE", AxlFnType, TT_FN_UNKNOWN, MBF_DEFAULT)
TYPEINFO_END
//
//DefunBx
//
DEFINE_BXTYPE(DefunBx) ;

AxlOpcode DefunBx::exec() {
	switch(m_xdx) {
		case 0 : {
			AiSymbol *pSym = asSymbol(getBxCellAt(0)) ;
			AiPair *pArgs = asPair(getBxCellAt(1)) ;
			AiPair *pBody = asPair(getBxCellAt(2)) ;
			AxlFnType *pFnType = new AxlFnType(pSym, pArgs, pBody) ;
			SetGlobalVal(pSym, pFnType) ; //TODO:lexical ... packages?
			axlSetResult(pFnType) ;
			bxEnd() ;
				 }
	}
	bxError() ;
}
//
MBINFO_BEGIN(DefunBx)
	MB_FORMALARG("*FNNAME*", MBF_SUPPRESSED, TT_CELL),
	MB_FORMALARG("*FNARGS*", MBF_SUPPRESSED, TT_PAIR),
	MB_RESTARG("*FNBODY*", MBF_SUPPRESSED) //testme !!!
MBINFO_END
//
//AxlFnKit
//
AiKit* AxlFnKit_produce(AiKit* pSuperKit, AiKitInfo *pKitInfo) {
	AxlFnKit* pKit = new AxlFnKit(pSuperKit, pKitInfo) ;
	pKit->create() ;
	return pKit ;
}
//
DEFINE_KITTYPE(AxlFnKit) ;

TYPEINFO_BEGIN(AxlFnKit)
	TYPEINFO("DEFUN", DefunBx, BX_DEFUN, MBF_DEFAULT)
TYPEINFO_END

NO_KITINFO(AxlFnKit) ;

KITINFO("fn", AXL_KT_FN, AxlFnKit) ;
