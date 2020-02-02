/*Botworx AI - An Artificial Intelligence Framework
Copyright (C) 2004  Kurtis Fields. See BotworxAI_License.txt for details.
*/
#include "stdafx.h"

//
//AiMetabit
//
AiMetabit::AiMetabit(AiMetabit* pParent, AiMbInfo &pInfo, ThingTT typeId) : BwCell(typeId) {
	p_parent = pParent ;
	p_info = &pInfo ;
	//AiSymbolPtr pName ;
	AiSymbol* pName = NULL ;
	m_flags = pInfo.m_flags ;
	if(m_typeId != TT_KITTYPE) {
		// if(isStaticMb(asMbInfo(pInfo)))
			pName = intern(getMbString(pInfo)) ;
		/*else
			pName = static_cast<AiSymbol*>(asMbInfo(pInfo)->p_name) ;*/
	}
	p_name = pName ;
}
void AiMetabit::init() {
}

