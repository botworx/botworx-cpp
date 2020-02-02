#ifndef _MiaFactory_H
#define _MiaFactory_H

#include "MiaIdentifier.h"
//
//MiaFactory
//
class MiaFactory : public BwCell {
public:
	MiaFactory(AiSymbol* pName, ThingTT cellType = MIA_TT_FACTORY) ;
	AiSymbol* getSymbol() { return p_symbol.get() ; }
	//Data Members
	AiSymbolPtr p_symbol ;
} ;
#define isMiaFactory(C) (C->getTypeId() == MIA_TT_FACTORY)
#define asMiaFactory(C) (static_cast<MiaFactory*>(C))

#endif//_MiaFactory_H