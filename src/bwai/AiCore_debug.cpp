/*Botworx AI - An Artificial Intelligence Framework
Copyright (C) 2004  Kurtis Fields. See BotworxAI_License.txt for details.
*/
#include "stdafx.h"
#include <bwai/AiPrinter.h>
//
//AiCore Debugging
//
/*
BW_DBG_DUMPER(Pair) {
	AiPair* pPair = static_cast<AiPair*>(pBlock) ;
	//_RPT0(_CRT_WARN, pSymbol->getCstring()) ;
	std::stringstream dst ;
	AiPrinter printer(dst) ;
	printer.printCell(pPair) ;
	_RPT1(_CRT_WARN, "Data: %s\n",	dst.str().c_str() ) ;
}
BW_DBG_DUMPER(String) {
	AiString* pString = static_cast<AiString*>(pBlock) ;
	//_RPT0(_CRT_WARN, pSymbol->getCstring()) ;
	_RPT1(_CRT_WARN, "Data: %s\n",	pString->getCstring() ) ;

}
BW_DBG_DUMPER(Symbol) {
	AiSymbol* pSymbol = static_cast<AiSymbol*>(pBlock) ;
	//_RPT0(_CRT_WARN, pSymbol->getCstring()) ;
	_RPT1(_CRT_WARN, "Data: %s\n",	pSymbol->getCstring() ) ;

}
//
BW_DBG_DUMPER(Var) {
}
//Blob
BW_DBG_DUMPER(Slot) {
}
BW_DBG_DUMPER(BlobType) {
}
BW_DBG_DUMPER(Blob) {
}
//
BW_DBG_DUMPER(Factory) {
}
////////////////////////////////
void AiCore::dumpBlock(void *ptr, size_t blockSize) {
    int block = _CrtReportBlockType(ptr);
	int blockType = _BLOCK_TYPE(block) ;
	int blockSubType = _BLOCK_SUBTYPE(block) ;
    //_RPT3(_CRT_WARN, "BwDbg_dumper found block at %p: type %d, subtype %d\n", ptr, _BLOCK_TYPE(block), _BLOCK_SUBTYPE(block));
	switch(blockSubType) {

		case TT_PAIR :
			BW_DBG_DUMP(Pair) ;
			break ;
		case TT_STRING :
			BW_DBG_DUMP(String) ;
			break ;
		case TT_SYMBOL :
			BW_DBG_DUMP(Symbol) ;
			break ;
		case TT_VAR :
			BW_DBG_DUMP(Var) ;
			break ;
		//Blob
		case TT_SLOT :
			BW_DBG_DUMP(Slot) ;
			break ;
		case TT_BLOBTYPE :
			BW_DBG_DUMP(BlobType) ;
			break ;
		case TT_BLOB :
			BW_DBG_DUMP(Blob) ;
			break ;
		//
		case TT_FACTORY :
			BW_DBG_DUMP(Factory) ;
			break ;

		default:
			_RPT3(_CRT_WARN, "###Block### : type %d, subtype %d, size %d\n",
				blockType, blockSubType, blockSize);
	}
}
*/