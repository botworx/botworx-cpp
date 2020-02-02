/*AXL - A Lispish interpreter for Botworx AI - An Artificial Intelligence Framework
Copyright (C) 2004  Kurtis Fields. See BotworxAI_License.txt for details.
*/
#include "stdafx.h"

#include <bwai/AiInt.h>
#include <bwai/AiFloat.h>

#include <bwaxl/AxlControl.h>
#include <bwaxl/AxlXop.h>
#include <bwaxl/AxlBx.h>
//
#include <bwaxl/AxlPrinter.h>
#include <bwaxl/AxlFiber_impl.h>
#include <bwaxl/AxlNumber.h>
#include <bwaxl/AxlXn.h>

void AxlPrinter::printXn(AxlXn *pXn) {
	print("Exception: ") ;
	AiType* pXnMeta = getXnMeta(pXn) ;
	AiString* pMetaDesc = pXnMeta->getDescription() ;
	printCell(pMetaDesc) ;
}
void AxlPrinter::printCell(const BwCell* pCell) {
	if(isNil(pCell)) {
		print("NIL") ;
		return ;
	}
	ThingTT cellTT = getTT(pCell) ;
	switch( cellTT ) {
		case TT_XN :
			printXn(asXn(pCell)) ;
			break ;
		default :
			AiPrinter::printCell(pCell) ;
	}
}