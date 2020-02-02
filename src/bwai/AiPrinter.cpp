/*AXL - A Lispish interpreter for Botworx AI - An Artificial Intelligence Framework
Copyright (C) 2004  Kurtis Fields. See BotworxAI_License.txt for details.
*/
#include "stdafx.h"

#include <bwai/AiMulti.h>

#include <bwai/AiMeta.h>
#include <bwai/AiInt.h>
#include <bwai/AiFloat.h>
//
#include <bwai/AiPrinter.h>
#include <bwai/AiString.h>
//
//AiPrinter
//
void AiPrinter::printString(const AiString *pString) {
	print("\"") ;
	print(pString->getCstring()) ;
	print("\"") ;
}
void AiPrinter::printSymbol(const AiSymbol *pSymbol) {
	print(pSymbol->getCstring()) ;
}
void AiPrinter::printInt(const AiInt *pCell) {
    const size_t bufferSize = 64;
	char buffer[bufferSize] ;
	//_itoa(pCell->m_value, buffer, 10) ;
	//snprintf(buffer, bufferSize, "%d", pCell->m_value);
	bwItoa(pCell->m_value, buffer, bufferSize, 10);
	sink() << buffer ;
}
void AiPrinter::printFloat(const AiFloat *pCell) {
    const size_t bufferSize = 64;
	char buffer[bufferSize] ;
	int     precision = 10;
	snprintf(buffer, bufferSize, "%f", pCell->m_value);

	sink() << buffer ;
}
void AiPrinter::printDottedPair(const AiPair* pPair) {
	printCell(car(pPair)) ;
	sink() << "." ;
	printCell(cdr(pPair)) ;
}
void AiPrinter::printPair(const AiPair* pPair) {
	BwCell* pCar = car(pPair) ;
	BwCell* pCdr = cdr(pPair) ;
	if(isNil(pCdr)) {
		printCell(pCar) ;
	}
	else if(notPair(pCdr)) {
		printDottedPair(pPair) ;
	}
	else if(isNil(pCar))
		printCell(SYM_NIL) ;
	else if(isPair(pCar))
		printList(asPair(pCar)) ;
	else
		printCell(pCar) ;
}
void AiPrinter::printList(const AiPair* pPair) {
	sink() << "(" ;
	while(notNil(pPair) && isPair(pPair)) {
		printPair(pPair) ;
		BwCell* pCell = cdr(pPair) ;
		if(notNil(pCell))
			sink() << " " ;
		pPair = static_cast<AiPair*>(pCell) ;
	}
	sink() << ")" ;
}
//#define isFreed(P) (*(int*)P == 0xdddddddd)
//#define isDestructed(P) (*(int*)P == 0xfeeefeee)

#define isFreed(P) (*(int*)P == 0xdddddddd || *(int*)P == 0xfeeefeee)
void AiPrinter::printCell(const BwCell* pCell) {
	if(isNil(pCell)) {
		print("NIL") ;
		return ;
	}
	//else
	if(isFreed(pCell)) {
		print("*FREED*") ;
		return ;
	}
	//else
	ThingTT cellTT = getTT(pCell) ;
	switch( cellTT ) {
		case TT_STRING :
		case TT_XSTRING :
			printString(asConstString(pCell)) ;
			break ;
		case TT_SYMBOL :
			printSymbol(asConstSymbol(pCell)) ;
			break ;
		case TT_INT :
			printInt(asConstInt(pCell)) ;
			break ;
		case TT_FLOAT :
			printFloat(asConstFloat(pCell)) ;
			break ;
		case TT_PAIR :
			printList(asConstPair(pCell)) ;
			break ;
		case TT_MULTI :
			printList(asConstPair(asConstMulti(pCell)->getList())) ;
			break ;
		case TT_FACTORY :
		case TT_XOPTYPE :
		case TT_BXTYPE :
		case TT_FNTYPE :
			print("Function:  ") ;
			printCellLn(asMeta(pCell)->getName()) ;
			break ;
		default :
			bwAssert(0) ;
			printLn("No print handler defined for this cell type!") ;
	}
}
void AiPrinter::printCellLn(const BwCell* pCell) {
	printCell(pCell) ;
	print("\n") ;
}
