/*Botworx AI - An Artificial Intelligence Framework
Copyright (C) 2004  Kurtis Fields. See BotworxAI_License.txt for details.
*/
#ifndef _AiXString_inline_H
#define _AiXString_inline_H

#include "AiReader.h"
#include "AiPrinter.h"
//
template <typename T>
inline AiString* AiXString_expand(AiXString* pXString, const T& functor) {
	std::string src(pXString->getString()) ;
	std::stringstream dst ;
	for(std::string::iterator iter = src.begin() ; iter != src.end() ; ++iter) {
		if(*iter != '$') {
			dst << *iter ;
			continue ;
		}
		//else
		std::stringstream tmp ;
		while(*++iter != '$') {
			tmp << *iter ;
		}
		tmp << "\n" ;
		AiReader reader(tmp) ;
		BwCellPtr pCell = reader.readExpr() ;
		BwCellPtr pCell2 = functor(pCell.get()) ;
		AiPrinter printer(dst) ;
		printer.printCell(pCell2.get()) ;
	}
	return new AiString(dst.str()) ;
}
#endif //_AiXString_inline_H