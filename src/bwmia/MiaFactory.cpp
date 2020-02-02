/*Botworx AI - An Artificial Intelligence Framework
Copyright (C) 2004  Kurtis Fields. See BotworxAI_License.txt for details.
*/
#include "stdafx.h"

#include <bwmia/MiaFactory.h>
#include <bwmia/MiaIdentifier.h>
//
//MiaFactory
//
MiaFactory::MiaFactory(AiSymbol* pSymbol, ThingTT cellType) : BwCell(cellType) {
	p_symbol = pSymbol ;
}