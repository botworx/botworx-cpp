/*AXL - A Lispish interpreter for Botworx AI - An Artificial Intelligence Framework
Copyright (C) 2004  Kurtis Fields. See BotworxAI_License.txt for details.
*/
#include "stdafx.h"
#include <new>

#include <bwaxl/AxlFiber_impl.h>
#include <bwaxl/AxlBx.h>
#include <bwaxl/AxlCatcher.h>
#include <bwaxl/AxlEval.h>
#include <bwaxl/AxlXop.h>
#include <bwaxl/AxlScope.h>
#include <bwaxl/AxlXn.h>
#include <bwaxl/AxlRepl.h>
#include <bwaxl/AxlNumber.h>
#include <bwaxl/AxlPrinter.h>

#include <bwaxl/config/options.h>

#define eq(X,Y) (X == Y)
#define zerop(X) (isNumber(X) && AiNumber_zerop(asNumber(X)))

AxlFiber::AxlFiber(void *pStackRoof, unsigned int stackSize) {

	p_stackRoof = pStackRoof ;
	p_stackFloor = ((char*)pStackRoof) +  stackSize  ;
	p_stackTop = p_stackFloor ;
	//
	p_topBx = NULL ;
	p_scope = NULL ;
	p_catcher = NULL ;
	p_result = NULL ;
	p_errorDesc = NULL ;
	p_ball = NULL ;
}
//
//Bx Management
//
AxlBx* AxlFiber_pushBx(AxlFiber *pThis, ThingSize size) {
	void* pStackTop = pThis->getStackTop() ;
	AxlBx* pNewTopBx = asBx(growStack(pStackTop, size)) ;
	AxlBx* pOldTopBx = pThis->p_topBx ;
	//f6:note:this is dangerous... setting variables before the object is constructed!!!
	pNewTopBx->p_prevStackTop = pStackTop ;
	pNewTopBx->p_prevBx = pOldTopBx ;
	pThis->p_topBx = pNewTopBx ;
	pThis->setStackTop(pNewTopBx) ;
	return pNewTopBx ;
}
AxlBx* AxlFiber_axlPopBx(AxlFiber *pThis) {
	AxlBx* pOldTopBx = pThis->p_topBx ;
	//
	ThingSize thingSize = getThingASize(pOldTopBx->getMeta()) ;
	BwCell** ppCell = (BwCell**)( ((char*)pOldTopBx) + thingSize)  ;
	BwCell* pCell = NULL ;
	for(size_t i = 0 ; i < pOldTopBx->m_length ; ++i) {
		pCell = ppCell[i] ;
		removeRef(pCell) ;
	}
	//
	AxlBx* pNewTopBx = pOldTopBx->p_prevBx ;
	void *pStackTop = shrinkStack(pOldTopBx, getBlobSize(pOldTopBx)) ;
	pOldTopBx->~AxlBx() ;
	pThis->setStackTop(pStackTop) ;
	pThis->p_topBx = pNewTopBx ;
	return pNewTopBx ;
}
//
AxlCatcher * AxlFiber_pushCatcher(AxlFiber *pThis, AxlBxType *pCatcherType) {
	AxlCatcher *pCatcher = asCatcher(AxlFiber_pushBx(pThis, getThingASize(pCatcherType))) ;
	AxlCatcher *pOldCatcher = pThis->p_catcher ;
	pCatcher->p_prevCatcher = pOldCatcher ;
	pCatcher->p_prevScope = pThis->p_scope ;
	pCatcher->m_nextOp = pThis->getNextOp() ;
	pThis->p_catcher = pCatcher ;

	return pCatcher ;
}
AxlBx* AxlFiber_popCatcher(AxlFiber *pThis, AxlCatcher *pCatcher) {
	AxlBx* pNewTopBx = pCatcher->p_prevBx ;
	pThis->p_catcher = pCatcher->p_prevCatcher ;
	pThis->p_scope = pCatcher->p_prevScope ;
	void *pStackTop = shrinkStack(pCatcher, getBlobSize(pCatcher)) ;
	pThis->setStackTop(pStackTop) ;
	pThis->p_topBx = pNewTopBx ;
	pThis->setNextOp(pNewTopBx->m_nextOp) ;
	return pNewTopBx ;
}
AxlOpcode AxlFiber_throwBall(AxlFiber *pThis, BwCell *pBall) {
	pThis->p_ball = pBall ;
	return OP_THROW ;
}
//
//Xop Management
//
AxlXop* AxlFiber_pushXop(AxlFiber *pThis, AxlOpcode opCode, ThingLength length)
{
	void* pStackTop = pThis->getStackTop() ;
	AxlXop* pNewTopOp = asXop(growStack(pStackTop, (sizeof(AxlXop)))) ; //TODO: ... extensible ops?
	new(pNewTopOp) AxlXop(asXopType(TYPEDIR(opCode)), length) ;
	pNewTopOp->p_prevStackTop = pStackTop ;
	pThis->setStackTop(pNewTopOp) ;
	AxlBx* pOldTopBx = pThis->p_topBx ;
	pNewTopOp->p_prevBx = pOldTopBx ;
	pNewTopOp->m_opCode = opCode ;
	pThis->p_topBx = asBx(pNewTopOp) ;
	return pNewTopOp ;
}
AxlBx* AxlFiber_popXop(AxlFiber *pThis) {
	AxlXop* pXop = asXop(pThis->p_topBx) ;
	AxlBx *pBx = NULL ;
	bwAssert(ofTT(getTT(pXop), TT_XOP)) ; //TODO: - dead code?
	pBx = AxlFiber_axlPopBx(pThis) ;
	return pBx ;
}
//
//AxlEval Management
//
AxlEval* AxlFiber_pushEval(AxlFiber *pThis, ThingLength length)
{
	void* pStackTop = pThis->getStackTop() ;
	AxlEval* pEval = asEval(growStack(pStackTop, (sizeof(AxlEval)))) ; //TODO: ... extensible ops?
	new(pEval) AxlEval(asXopType(TYPEDIR(XOP_EVAL)), length) ;
	pEval->p_prevStackTop = pStackTop ;
	pThis->setStackTop(pEval) ;
	AxlBx* pOldTopBx = pThis->p_topBx ;
	pEval->p_prevBx = pOldTopBx ;
	pThis->p_topBx = asBx(pEval) ;
	asXop(pEval)->m_opCode = XOP_EVAL ; //TODO: - obsolete?
	pEval->m_argLength = 0 ;
	//
	return pEval ;
}
AxlBx* AxlFiber_popEval(AxlFiber *pThis) {
	AxlEval* pEval = (AxlEval*)pThis->p_topBx ;
	AxlBx *pBx = AxlFiber_axlPopBx(pThis) ;
	return pBx ;
}
//
void AxlFiber_pushVal(AxlFiber *pThis, BwCell* pVal) {
	bwAssert(pVal != UNBOUND) ;
	addRef(pVal) ;
	void* pStackTop = pThis->getStackTop() ;
	BwCell **pTopVal = (BwCell**)growStack(pStackTop, sizeof(BwCell*)) ;
	pThis->setStackTop(pTopVal) ;
	*pTopVal = pVal ; //set arg.
}
//TODO:remove?  values are accessed via index.
BwCell* AxlFiber_popVal(AxlFiber *pThis) {
	void* pStackTop = pThis->getStackTop() ;
	BwCell **pTopVal = (BwCell**)pStackTop ;
	pStackTop = shrinkStack(pStackTop, sizeof(BwCell*)) ;
	pThis->setStackTop(pStackTop) ;
	return *pTopVal ;
}
ThingLength axlPushArgs(AiPair *pPair) {
	ThingLength length = 0 ;
	for(; pPair != NULL ; pPair = pairCdr(pPair)) {
		axlPushVal(car(pPair)) ;
		length++ ;
	}
	return length ;
}
AxlOpcode axlJumpBx() {
	return k_fiber().setNextOp(OP_BXEXEC) ;
}
AxlOpcode axlCallBx() {
	axlPushOp() ;
	return k_fiber().setNextOp(OP_BXEXEC) ;
}
AxlOpcode axlCallBx1(BwCell *p1) {
	axlPushOp() ;
	axlPushVal(p1) ;
	//pushBx ...
	return k_fiber().setNextOp(OP_BXEXEC) ;
}
AxlOpcode axlCallBx2(BwCell *p1, BwCell *p2) {
	axlPushOp() ;
	axlPushVal(p1) ;
	axlPushVal(p2) ;
	//pushBx
	return k_fiber().setNextOp(OP_BXEXEC) ;
}

AxlOpcode axlBxEnd() {
	axlPopBx() ;
	AxlOpcode op = axlPopOp() ;
	return op ;
}
AxlOpcode axlBxReturn(BwCell *pVal) {
	axlPopBx() ;
	AxlOpcode op = axlPopOp() ;
	axlSetResult(pVal) ;
	return op ;
}
AxlOpcode axlJumpXop() {
	AxlOpcode jumpOP = asXop(k_fiber().p_topBx)->m_opCode ;
	k_fiber().setNextOp(jumpOP) ;
	return jumpOP ;
}
AxlOpcode axlCallXop(AxlOpcode callOp) {
	axlPushOp() ;
	pushXop(callOp) ;
	return k_fiber().setNextOp(callOp) ;
}
AxlOpcode axlCallXop1(AxlOpcode callOp, BwCell *p1) {
	axlPushOp() ;
	axlPushVal(p1) ;
	pushXop1(callOp) ;
	return k_fiber().setNextOp(callOp) ;
}
AxlOpcode axlCallXop2(AxlOpcode callOp, BwCell *p1, BwCell *p2) {
	axlPushOp() ;
	axlPushVal(p1) ;
	axlPushVal(p2) ;
	pushXopN(callOp, 2) ;
	return k_fiber().setNextOp(callOp) ;
}
AxlOpcode axlCallXopN(AxlOpcode callOp, ThingLength length) {
	axlPushOp() ;
	pushXopN(callOp, length) ;
	return k_fiber().setNextOp(callOp) ;
}
AxlOpcode axlCallXopArgs(AxlOpcode callOp, AiPair *pArgs) {
	axlPushOp() ;
	ThingLength length = pushArgs(pArgs) ;
	pushXopN(callOp, length) ;
	return k_fiber().setNextOp(callOp) ; //TODO: - is anyone using this return val?
}
AxlOpcode axlCallEval1(BwCell* pVal) {
	axlPushOp() ;
	axlPushVal(pVal) ;
	AxlEval *pEval = pushEval1() ; //TODO:? - write pushEval() ... cheater code?
	jumpXop() ;
}
AxlOpcode axlJumpEval1(BwCell* pVal) {
	axlPushVal(pVal) ;
	AxlEval *pEval = pushEval1() ; //TODO:? - write pushEval() ... cheater code?
	jumpXop() ;
}
AxlOpcode AxlFiber::evalEnd() {
#if AXL_DEBUG_EVAL
	k_printer().print("Result:  ") ;
	k_printer().printCellLn(getResult()) ;
#endif
	popEval() ;
	AxlOpcode op = popOp() ;
	return op ;
}
//
AxlOpcode axlXopEnd() {
	popXop() ;
	AxlOpcode op = axlPopOp() ;
	return op ;
}
AxlScope* AxlFiber_beginScope(AxlFiber *pThis, AxlBx *pBx) {
	void* pStackTop = pThis->getStackTop() ;
	AxlScope* pScope = asAxlScope(growStack(pStackTop, (sizeof(AxlScope)))) ;
	pThis->setStackTop(pScope) ;
	pScope->p_superScope = pThis->p_scope ;
	pThis->p_scope = pScope ;
	pScope->p_bx = pBx ;
	return pScope ;
}
void AxlFiber_endScope(AxlFiber *pThis) {
	AxlScope *pScope = pThis->p_scope->p_superScope ;
	pThis->p_scope = pScope ;
}
void AxlFiber::setScopeVal(AiSymbol* pSym, BwCell* pVal) {
	bwAssert(pVal != UNBOUND) ;
	AxlBx *pScopeBx = NULL ;
	BwCell* pLastVal = NULL ;
	for(AxlScope *pScope = p_scope ; pScope != NULL ; pScope = pScope->p_superScope) {
		pScopeBx = pScope->p_bx ;
		pLastVal = pScopeBx->getSlotVal(pSym) ; //TODO: - hack!!!
		if(pLastVal != UNBOUND) {
			pScopeBx->setSlotVal(pSym, pVal) ;
			return ;
		}
	}
	SetGlobalVal(pSym, pVal) ;
}
BwCell* AxlFiber::getScopeVal(AiSymbol *pSym) {
	AxlBx *pScopeBx = NULL ;
	BwCell* pVal = NULL ;
	for(AxlScope *pScope = p_scope ; pScope != NULL ; pScope = pScope->p_superScope) {
		pScopeBx = pScope->p_bx ;
		pVal = pScopeBx->getSlotVal(pSym) ; //TODO: - hack!!!
		if(pVal != UNBOUND)
			return pVal ;
	}
	pVal = GetGlobalVal(pSym) ;
	return pVal ;
}
AxlOpcode evalUrForm(AiPair *pPair) {
	bwAssert(0) ; //f6:implement:how hard could this be?
	return OP_UNDEFINED ;
}
AxlOpcode AxlFiber::evalForm(AiPair *pPair) {
	AiPair *pTail ;
	BwCell* pUrHead = car(pPair) ; //get head of list
	if(isPair(pUrHead))
		return evalUrForm(asPair(pUrHead)) ; //returns UrFormEvalAx
	//else it's a symbol ,TODO: .. what if it's not? Throw an exception
	BwCell* pHead = GetGlobalVal(asSymbol(pUrHead)) ;

	if(asSymbol(pHead) == UNBOUND) {
		setResult(pUrHead) ;
		throwXn(XN_UNBOUND) ;
	}

	ThingTT headTT = getTT(pHead) ;

	switch(headTT) {
		case TT_XOPTYPE :
		case TT_BXTYPE :
		case TT_FNTYPE :{
			AxlBxType* pFactory = asBxType(pHead) ;
			AiPair* pArgSlots = pFactory->getSlots() ;
			pTail = asPair(cdr(pPair)) ;
			evaluator().p_args = pTail ;
			evaluator().p_argSlots = pArgSlots ;
			evaluator().p_factory = pFactory ;
			return OP_BXCALL ;
		}
		default :
			bwAssert(0) ;
	}
	return axlError("evalForm") ;
}

AxlOpcode AxlFiber::eval() {
	BwCell* pVal = getEvalCellAt(0) ;
#if AXL_DEBUG_EVAL
	k_printer().print("Eval:  ") ;
	k_printer().printCellLn(pVal) ;
#endif
	AxlOpcode opCode = OP_ERROR ;
	ThingTT cellTT = OP_NIL ;
	if(notNil(pVal))
		cellTT = getTT(pVal) ;
	switch(cellTT) {
		case OP_NIL :
		case TT_INT :
		case TT_FLOAT :
		case TT_STRING :
			setResult(pVal) ;
			opCode = OP_NOP ;
			break ;
		case TT_SYMBOL : {
			AiSymbol* pSymbol = asSymbol(pVal) ;
			BwCell* pVarVal = NULL ;
			switch(pSymbol->getSymType()) {
				case SYMTYP_NORMAL :
					pVarVal = getScopeVal(asSymbol(pVal)) ;
					break ;
				case SYMTYP_LOGIC :
					pVarVal = getLogicVal(pSymbol) ;
					break ;
				case SYMTYP_PROPERTY :
					pVarVal = getPropertyVal(pSymbol) ;
					break ;
			}
			if(pVarVal == UNBOUND)
				throwXn(XN_UNBOUND) ;

			setResult(pVarVal) ;
			opCode = OP_NOP ;
			break ;
						 }
		case TT_PAIR :
			opCode = evalForm(asPair(pVal)) ;
			break ;
		default :
			bwAssert(0) ;
			#if AXL_DEBUG_EVAL
			k_printer().printLn("No eval handler defined for this cell type!") ;
			#endif
			break ;
	}

	return opCode ;
}
//Execute one operation
AxlOpcode AxlFiber::doStep() {
	AxlBx *pBx ;
	AxlOpcode opCode = m_nextOp ;
	//bwAssert(opCode > 0 && opCode <= AITYPE_MAX) ;
	//
	switch(opCode) {
		case OP_EXIT :
			#if AXL_DEBUG_EVAL
			printf("Bye.") ;
			#endif
			break ;
		case OP_NOP :
		case OP_ERROR :
		case OP_UNDEFINED :
			bwAssert(0) ;
		case XOP_EVAL :
			opCode = eval() ;
			if(opCode == OP_NOP)
				return evalEnd() ;
			else {
				return jumpOp(opCode) ;
			}
		case OP_PUSHARGS : {
			AxlOpcode processOp = OP_ERROR ;
			AxlBxType* pFactory = P_EVAL->p_factory ;
			AiPair* pArgSlots = pFactory->getSlots() ;
			processOp = processFArgs(pArgSlots) ;
			if(processOp != OP_THROW) {
				setNextOp(OP_EVALEND) ;
				pushOp() ;
				pFactory->produce(getArgLength()) ;
				return jumpOp(OP_BXEXEC) ;
			}
			else
				return jumpOp(OP_THROW) ;
						   }
			break ;
		case OP_EVALARGS : {
			//NEW
			AiPair* pArgSlots = P_EVAL->getArgSlots() ;
			AiSlot* pArgSlot = NULL ;
			if(notNil(pArgSlots)) {
				pArgSlot = asSlot(car(pArgSlots)) ;
			}
			//NEW
			AiPair* pArgs = P_EVAL->getArgs() ;
			BwCell* pArg = NIL ;
			if(notNil(pArgs))
				pArg = car(pArgs) ;
			//NEW
			if(!isSuppressedMb((*pArgSlot))) {
				setNextOp(OP_EVALARGS1) ;
				callEval1(pArg) ;
			}
			else
				setResult(pArg) ;
		}
		case OP_EVALARGS1 : {
			AiPair* pArgSlots = P_EVAL->getArgSlots() ;
			AiSlot* pArgSlot = NULL ;
			AiPair* pArgs = P_EVAL->getArgs() ;
			BwCell* pArg = getResult() ; //result from eval that just returned ...

			if(notNil(pArgSlots)) {
				pArgSlot = asSlot(car(pArgSlots)) ;
				pArgSlots = asPair(cdr(pArgSlots)) ;
			}

			AxlOpcode op = processArg(pArgSlot, pArg) ;

			if(pArgSlot != NIL) {
				if(getTT(pArgSlot) != TT_RESTARG)
					evaluator().p_argSlots = pArgSlots ;
				else {
					pArgs = NULL ; //TODO:a hack
					pArgSlots = NULL ;
				}
			}
			if(notNil(pArgs)) {
				pArgs = asPair(cdr(pArgs)) ;
				evaluator().p_args = pArgs ;
			}
			if(op == OP_THROW)
				return jumpOp(OP_THROW) ;
			if(isNil(pArgs) && isNil(pArgSlots)) {
				AxlBxType* pFactory = evaluator().p_factory ;
				setNextOp(OP_EVALEND) ;
				pushOp() ;
				pFactory->produce(getArgLength()) ;
				return jumpOp(OP_BXEXEC) ;
			}
			//else ...
			return jumpOp(OP_EVALARGS) ;
							}

		case OP_BXCALL : {
			return jumpOp(OP_EVALARGS) ;
			break ;
		 }
		case OP_BXEXEC : {
			pBx = p_topBx ;
			bwAssert(pBx) ;
			if(ofXop(getTT(pBx)))
				return jumpOp(asXop(pBx)->m_opCode) ;
			else
				setNextOp(pBx->exec()) ; //Main Function Call
		 }
			break ;
		case OP_BXEND :
			axlBxEnd() ;
			break ;
		case OP_EVALEND :
			return evalEnd() ;
			break ;
		case OP_POPCATCHER :
			AxlFiber_popCatcher(this, asCatcher(p_topBx)) ;
			break ;
		case OP_THROW : {
			AxlCatcher *pCatcher = p_catcher ;
			AxlOpcode catchOp = OP_ERROR ;

			BwCell *pBall = p_ball ;
			if(pCatcher->canCatch(pBall)) {
				catchOp = pCatcher->catchBall(pBall) ;
			}
			else {
				catchOp = pCatcher->missBall(pBall) ;
			}
			AxlFiber_popCatcher(this, pCatcher) ;
			if(catchOp == OP_THROW) {
				opAgain() ;
			}
						}
			break ;
		case XOP_QUOTE : {
			BwCell *pVal = getXopCellAt(0) ;
			setResult(pVal) ;
			xopEnd() ; //TODO: ... check arity
						 }
		case XOP_CONS : {
			BwCell* pCar = getXopCellAt(0) ; //Bx's are reverse indexed!!!
			BwCell* pCdr = getXopCellAt(1) ;
			AiPair* pPair = cons(pCar,pCdr) ;
			setResult(pPair) ;
			xopEnd() ;
					  }
		case XOP_CAR : {
			AiPair* pPair = asPair(getXopCellAt(0)) ;
			BwCell* pVal = car(pPair) ;
			setResult(pVal) ;
			xopEnd() ;
					  }
		case XOP_CDR : {
			AiPair* pPair = asPair(getXopCellAt(0)) ;
			BwCell* pVal = cdr(pPair) ;
			setResult(pVal) ;
			xopEnd() ;
					   }
			break ;
		case XOP_NULL : {
			BwCell *pCell = getXopCellAt(0) ;
			if(isNil(pCell))
				setResult(SYM_TRUE) ;
			else
				setResult(NIL) ;
			xopEnd() ;
						}
			break ;
		case XOP_SET : {
			AiSymbol *pSym = asSymbol(getXopCellAt(0)) ;
			BwCell *pVal = getXopCellAt(1) ;
			setScopeVal(pSym, pVal) ;
			setResult(pVal) ;
			xopEnd() ;
					   }
			break ;
		case XOP_SETQ : {
			AiSymbol *pSym = asSymbol(getXopCellAt(0)) ;
			BwCell *pVal = getXopCellAt(1) ;
			setScopeVal(pSym, pVal) ;
			setResult(pVal) ;
			xopEnd() ;
					   }
			break ;
		case XOP_EQ : {
			BwCell* pResult = NULL ;
			BwCell *pVal1 = getXopCellAt(0) ;
			BwCell *pVal2 = getXopCellAt(1) ;
			if(eq(pVal1,pVal2))
				pResult = SYM_TRUE ;
			else
				pResult = NIL ;
			setResult(pResult) ;
			xopEnd() ;
					   }
			break ;
		//Numbers
		case XOP_NUMBER_EQUAL : {
			BwCell *pResult = NULL ;
			BwCell *pVal = getXopCellAt(0) ;
			BwCell *pVal1 = getXopCellAt(1) ;
			pResult = AiNumber_equal(asNumber(pVal), asNumber(pVal1)) ;
			setResult(pResult) ;
			xopEnd() ;
					   }
			break ;
		case XOP_NUMBER_NOT_EQUAL : {
			BwCell *pResult = NULL ;
			BwCell *pVal = getXopCellAt(0) ;
			BwCell *pVal1 = getXopCellAt(1) ;
			pResult = AiNumber_notEqual(asNumber(pVal), asNumber(pVal1)) ;
			setResult(pResult) ;
			xopEnd() ;
					   }
			break ;
		case XOP_ZEROP : {
			BwCell* pResult = NULL ;
			BwCell *pVal = getXopCellAt(0) ;
			if(zerop(pVal))
				pResult = SYM_TRUE ;
			else
				pResult = NIL ;
			setResult(pResult) ;
			xopEnd() ;
					   }
			break ;
		case XOP_SUB1 : {
			BwCell *pResult = NULL ;
			BwCell *pVal = getXopCellAt(0) ;
			pResult = AiNumber_sub1(asNumber(pVal)) ;
			setResult(pResult) ;
			xopEnd() ;
					   }
			break ;
		case XOP_SUB : {
			BwCell *pResult = NULL ;
			BwCell *pVal = getXopCellAt(0) ;
			BwCell *pVal1 = getXopCellAt(1) ;
			pResult = AiNumber_sub(asNumber(pVal), asNumber(pVal1)) ;
			setResult(pResult) ;
			xopEnd() ;
					   }
			break ;
		case XOP_PLUS : {
			BwCell *pResult = NULL ;
			BwCell *pVal = getXopCellAt(0) ;
			BwCell *pVal1 = getXopCellAt(1) ;
			pResult = AiNumber_add(asNumber(pVal), asNumber(pVal1)) ;
			setResult(pResult) ;
			xopEnd() ;
					   }
			break ;
		default :
			bwAssert(0) ;
	}
	return opCode ;
}
AxlOpcode AxlFiber::stepFor(int ticks) {
	AxlOpcode op = OP_NOP ;
	while(ticks--) {
		op = doStep() ;
		if(op == OP_EXIT)
			break ;
	}
	return op ;
}
void AxlFiber::run() {
	AxlOpcode op = OP_NOP ;
	while(op != OP_EXIT) {
		op = doStep() ;
	}
}
