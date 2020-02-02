/*Botworx AI - An Artificial Intelligence Framework
Copyright (C) 2004  Kurtis Fields. See BotworxAI_License.txt for details.
*/
#include "stdafx.h"

#include <bwmia/MiaPrinter.h>
#include <bwmia/MiaIdentifier.h>

void MiaPrinter::printCell(const BwCell* pCell) {
	if(isNil(pCell)) {
		print("NIL") ;
		return ;
	}
	ThingTT cellTT = getTT(pCell) ;
	switch( cellTT ) {
		case MIA_TT_TOPIC :
			bwAssert(0) ;
		case MIA_TT_IDENTIFIER :
			*this << *asConstIdentifier(pCell) ;
			break ;
		case MIA_TT_FACT :
			*this << *asConstFact(pCell) ;
			break ;
		default :
			AxlPrinter::printCell(pCell) ;
	}
}
