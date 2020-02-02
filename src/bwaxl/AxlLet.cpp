/*AXL - A Lispish interpreter for Botworx AI - An Artificial Intelligence Framework
Copyright (C) 2004  Kurtis Fields. See BotworxAI_License.txt for details.
*/
#include "stdafx.h"
#include <new>

#include <bwaxl/AxlFiber_impl.h>
#include <bwaxl/AxlLet.h>
#include <bwaxl/AxlPrinter.h>

//
DEFINE_AIVALUETYPE(AxlLetType) ;

void* AxlLetType::produce(ThingLength length) {
	AxlLet* pThis = (AxlLet*)axlPushBx(getThingASize(this)) ;
	new(pThis) AxlLet(this, length) ;
	return pThis ;
}

void AxlLetType::purge() {
	AxlLetType::~AxlLetType() ;
	BW_USERFREE(this, TT_LETTYPE) ;
}

extern AiTypeInfos s_AxlLetType_metaInfo ;
//
//AxlLetType
//
void AxlLetType::createArgs(AiPair* pArgs) {
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
AxlLetType::AxlLetType(AiSymbol *pSym, AiPair *pArgs, AiPair *pBody, ThingTT typeId) 
	: AxlFormType(asTypeInfo(s_AxlLetType_metaInfo[0]), typeId) {
	init(asTypeInfo(s_AxlLetType_metaInfo[0])) ; //TODO:what an ungodly hack.
	setMbSymbol((*this), pSym) ;
	createArgs(pArgs) ;
	p_body = pBody ;
}
//
//AxlLet
//
AxlOpcode AxlLet::exec() {
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
MBINFO_NONE(AxlLetType) ;
//
TYPEINFO_BEGIN(AxlLetType)
	TYPEINFO("LET-TYPE-TYPE", AxlLetType, TT_LETTYPE, MBF_DEFAULT)
TYPEINFO_END
//
//DefLet
//
AxlOpcode DefLet::exec() {
	switch(m_xdx) {
		case 0 : {
			AiPair *pArgs = asPair(getBxCellAt(0)) ;
			AiPair *pBody = asPair(getBxCellAt(1)) ;
			AxlLetType *pLetMeta = new AxlLetType(NULL, pArgs, pBody) ;
			//TODO:need to handle initializers & eval of such...
			for(int i = 0 ; i < pLetMeta->m_bFldCount ; ++i) {
				axlPushVal(NIL) ;
			}
			axlPushOp() ;
			pLetMeta->produce(pLetMeta->m_bFldCount) ;
			setXdx(this,1) ;
			return k_fiber().setNextOp(OP_BXEXEC) ;
				 }
		case 1 : {
			bxEnd() ;
				 }
	}
	bxError() ;
}
//
DEFINE_BXTYPE(DefLet) ;

MBINFO_BEGIN(DefLet)
	MB_FORMALARG("*FNARGS*", MBF_SUPPRESSED, TT_PAIR), //testme !!!
	MB_RESTARG("*FNBODY*", MBF_SUPPRESSED) //testme !!!
MBINFO_END

//
//AxlLetKit
//
//
DEFINE_KITTYPE(AxlLetKit) ;

TYPEINFO_BEGIN(AxlLetKit)
	TYPEINFO("LET", DefLet, TT_BX, MBF_EXTENDED)
TYPEINFO_END

NO_KITINFO(AxlLetKit) ;

KITINFO("let", AXL_KT_LET, AxlLetKit) ;