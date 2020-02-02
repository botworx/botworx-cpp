/*AXL - A Lispish interpreter for Botworx AI - An Artificial Intelligence Framework
Copyright (C) 2004  Kurtis Fields. See BotworxAI_License.txt for details.
*/
#include "stdafx.h"

#include <bwaxl/AxlFiber_impl.h>
#include <bwaxl/AxlEval.h>
#include <bwaxl/AxlXn.h>
#include <bwaxl/AxlXop.h>

#define axlCompareTTs(M1, M2) (isValueType(getTT(M1)) || M1 == M2)
//
bool axlNormalizeVal(AiType* pMeta, BwCell* pCell) {
	axlSetResult(pCell) ;
	return true ; //TODO:Type checking is messed up now ...
	/*AiType* pSrcMeta = NULL ;
	if(isNil(pCell))
		pSrcMeta = TYPEDIR(TT_CELL) ;
	else
		pSrcMeta = getCellType(pCell) ;
	if(ofPType(getThingTT(pMeta))) {
		AiType* pDstMeta = asPType(pMeta)->getTargetMeta() ;
        return axlCompareTTs(pDstMeta, pSrcMeta) ;
	}
	else
		throw BwGeneralException("axlNormalizeVal ... wasn't a pointer!") ;
	return false ;*/
}
//
AxlOpcode AxlEval_processArg(AxlEval *pThis, AiSlot* pArgSlot, BwCell* pArg) {
	AiPair* pArgs = pThis->getArgs() ;
	BwCell *pResultArg = NIL ;
	if(isNil(pArgSlot) & notNil(pArgs)) {
		throwXn(XN_TOO_MANY_ARGS) ;
	}
	ThingTT slotTT = getTT(pArgSlot) ; //watchme ... unless these are final metas.
	switch(slotTT) {
		case TT_FORMALARG : {
			if(isNil(pArgs)) {
				throwXn(XN_NOT_ENOUGH_ARGS) ;
			}
							}
			break ;
		case TT_OPTARG : {
						 }
			break ;
		case TT_RESTARG : {
			if(isNil(pArgs)) { //TODO: ... is rest optional? what if its the first and only arg?
				throwXn(XN_NOT_ENOUGH_ARGS) ;
			}
			pArg = pArgs ;
						  }
		  break ;
	}
	AiType* pElMeta = pArgSlot->p_elMeta ;
	if(!axlNormalizeVal(pElMeta, pArg)) {
		axlSetResult(pArg) ; //watchme - this should go inside exceptions?
		throwXn(XN_BAD_ARG) ;
	}
	axlPushResult() ;
	pThis->m_argLength ++ ;
	return OP_NOP ;
}
//
AxlOpcode AxlEval_processFArg(AxlEval *pThis, AiSlot* pArgSlot) {
	AiPair* pArgs = pThis->getArgs() ;
	BwCell* pArg = NIL ;
	BwCell* pResultArg = NIL ;
	if(notNil(pArgs)) {
		pArg = car(pArgs) ;
	}
	if(isNil(pArgSlot) & notNil(pArgs)) {
		throwXn(XN_TOO_MANY_ARGS) ;
	}
	ThingTT slotTT = getTT(pArgSlot) ; //watchme ... unless these are final metas.
	switch(slotTT) {
		case TT_FORMALARG : {
			if(isNil(pArgs)) {
				throwXn(XN_NOT_ENOUGH_ARGS) ;
			}
							}
			break ;
		case TT_OPTARG : {
						 }
			break ;
		case TT_RESTARG : {
			if(isNil(pArgs)) { //TODO: ... is rest optional? what if its the first and only arg?
				throwXn(XN_NOT_ENOUGH_ARGS) ;
			}
			pArg = pArgs ;
			pThis->p_args = NULL ; //causes processFArgs to end gracefully
						  }
		  break ;
	}
	AiType* pElMeta = pArgSlot->p_elMeta ;
	if(!axlNormalizeVal(pElMeta, pArg)) {
		axlSetResult(pArg) ; //watchme - this should go inside exceptions?
		throwXn(XN_BAD_ARG) ;
	}
	pThis->m_argLength ++ ;
	return OP_NOP ;
}
AxlOpcode AxlEval_processFArgs(AxlEval *pThis, AiPair* pArgSlots) {
	AiSlot* pArgSlot = NULL ;
	AiPair* pArgs = pThis->getArgs() ;
	AxlOpcode op = OP_ERROR ;
	while(op != OP_END) {
		if(notNil(pArgSlots)) {
			pArgSlot = asSlot(car(pArgSlots)) ;
			pArgSlots = asPair(cdr(pArgSlots)) ;
		}
		else
			pArgSlot = NULL ;
		op = AxlEval_processFArg(pThis, pArgSlot) ;
		if(op == OP_THROW)
			relayBall() ;
		axlPushResult() ; //push result from processFArg
		pArgs = pThis->getArgs() ; //reload ... may have been modified by processFArg
		if(notNil(pArgs))
			pThis->p_args = pArgs = asPair(cdr(pArgs)) ;
		if(isNil(pArgs) & isNil(pArgSlots))
			op = OP_END ;
	}
	return op ;
}
//
ThingLength AxlEval_getArgLength(AxlEval *pThis) {
	return pThis->m_argLength ;
}
//
//AxlEvalKit
//
DEFINE_KITTYPE(AxlEvalKit) ;

DEFINE_XOPTYPE(AxlEval) ;
MBINFO_NONE(AxlEval) ;
//
TYPEINFO_BEGIN(AxlEvalKit)
	TYPEINFO("EVAL", AxlEval, XOP_EVAL, MBF_DEFAULT)
TYPEINFO_END

NO_KITINFO(AxlEvalKit) ;

KITINFO("eval", AXL_KT_EVAL, AxlEvalKit) ;
