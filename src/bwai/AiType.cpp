/*Botworx AI - An Artificial Intelligence Framework
Copyright (C) 2004  Kurtis Fields. See BotworxAI_License.txt for details.
*/
#include "stdafx.h"

#include <bwai/AiType.h>

void AiType::purge() {
	AiType::~AiType() ;
	BW_USERFREE(this, TT_TYPE) ;
}
void AiType::registerSelf(AiTypeInfo& pInfo, ThingTT& typeID) {
	if(typeID == TT_NIL)
		typeID = (ThingTT)k_core().registerType(this, pInfo) ;
}