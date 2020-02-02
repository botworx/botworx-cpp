/*Botworx AI - An Artificial Intelligence Framework
Copyright (C) 2004  Kurtis Fields. See BotworxAI_License.txt for details.
*/
#include "stdafx.h"

#include <bwmia/MiaReader.h>
#include <bwmia/MiaParser.h>
#include <bwmia/MiaState.h>
//
//MiaReader
//
MiaReader::MiaReader(std::istream& in) : AiReader(in) {
}
void MiaReader::read() {
	for(BwCellPtr pExpr = readExpr() ; pExpr.get() != SYM_EOF ; pExpr = readExpr()) {
		MiaFileParser parser(this) ;
		parser.parse(asPair(pExpr.get())) ;
	}
}