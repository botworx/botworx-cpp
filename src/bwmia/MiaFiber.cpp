/*Botworx AI - An Artificial Intelligence Framework
Copyright (C) 2004  Kurtis Fields. See BotworxAI_License.txt for details.
*/
#include "stdafx.h"

#include <bwmia/MiaTopic.h>
#include <bwmia/MiaIdentifier.h>
#include <bwmia/MiaState.h>
#include <bwmia/MiaFiber.h>
#include <bwmia/MiaBinderOps.h>

#include <bwaxl/AxlRepl.h>

//
// MiaFiber
//
MiaFiber::MiaFiber(MiaBinder& binder, void *pStackRoof, unsigned int stackSize)
	: AxlFiber(pStackRoof, stackSize) {
	p_binder = &binder ;
}
BwCell* MiaFiber::eval(BwCell* pExpr) {
	BwCell* pVal = NULL ;
	k_core().setFiber(this) ;
	new AxlExprRepl(pExpr) ;
	run() ;
	pVal = getResult() ;
	return pVal ;
}
void MiaFiber::setLogicVal(AiSymbol* pSymbol, BwCell* pVal) {
	p_binder->setVal(pSymbol, pVal) ;
}
BwCell* MiaFiber::getLogicVal(AiSymbol* pSymbol) {
	return p_binder->getVal(pSymbol) ;
}
void MiaFiber::setPropertyVal(AiSymbol* pSymbol, BwCell* pVal) {
	bwAssert(0) ;
}
BwCell* MiaFiber::getPropertyVal(AiSymbol* pSymbol) {
	return getMethod(binder()).getPropertyVal(pSymbol) ;
}
