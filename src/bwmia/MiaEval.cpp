/*Botworx AI - An Artificial Intelligence Framework
Copyright (C) 2004  Kurtis Fields. See BotworxAI_License.txt for details.
*/
#include "stdafx.h"

#include <bwmia/MiaTopic.h>
#include <bwmia/MiaIdentifier.h>
#include <bwmia/MiaState.h>
#include <bwmia/MiaEval.h>
#include <bwmia/MiaBinderOps.h>

#include <bwmia/MiaFiber.h>
//
// MiaEval
//
BwCell* MiaEval::eval(BwCell* pExpr) {
	BwCell* pVal = NULL ;
	switch(getTT(pExpr)) {
		case TT_SYMBOL :
			pVal = getSymbolVal(asSymbol(pExpr)) ;
			break ;
		case TT_PAIR :
			pVal = evalPair(asPair(pExpr)) ;
			break ;
		default :
			pVal = pExpr ;
	}
	return pVal ;
}
void MiaEval::setSymbolVal(AiSymbol* pSymbol, BwCell* pVal) {
	switch(pSymbol->getSymType()) {
		case SYMTYP_LOGIC :
			setLogicVal(pSymbol, pVal) ;
			break ;
		case SYMTYP_NORMAL :
			setGlobalVal(pSymbol, pVal) ;
			break ;
		case SYMTYP_PROPERTY :
			setPropertyVal(pSymbol, pVal) ;
			break ;
	}
}
BwCell* MiaEval::getSymbolVal(AiSymbol* pSymbol) {
	BwCell* pVal = NULL ;
	switch(pSymbol->getSymType()) {
		case SYMTYP_LOGIC :
			pVal = getLogicVal(pSymbol) ;
			break ;
		case SYMTYP_NORMAL :
			pVal = getGlobalVal(pSymbol) ;
			break ;
		case SYMTYP_PROPERTY :
			pVal = getPropertyVal(pSymbol) ;
			break ;
	}
	return pVal ;
}
BwCell* MiaEval::evalPair(AiPair* pExpr) {
	BwCell* pVal = NULL ;
	MiaFiber fiber(binder(), k_core().getStack(), k_core().getStackSize()) ;
	pVal = fiber.eval(pExpr) ;
	return pVal ;
}
void MiaEval::setGlobalVal(AiSymbol* pSymbol, BwCell* pVal) {
	bwAssert(0) ;
	SetGlobalVal(pSymbol, pVal) ;
}
BwCell* MiaEval::getGlobalVal(AiSymbol* pSymbol) {
	return internId(pSymbol) ; //TODO:what if global is not id?
}
void MiaEval::setLogicVal(AiSymbol* pSymbol, BwCell* pVal) {
	bwAssert(0) ;
	p_binder->setVal(pSymbol, pVal) ;
}
BwCell* MiaEval::getLogicVal(AiSymbol* pSymbol) {
	return p_binder->getVal(pSymbol) ;
}
void MiaEval::setPropertyVal(AiSymbol* pSymbol, BwCell* pVal) {
	bwAssert(0) ; //TODO:implement?
}
BwCell* MiaEval::getPropertyVal(AiSymbol* pSymbol) {
	return getMethod(binder()).getPropertyVal(pSymbol) ;
}
