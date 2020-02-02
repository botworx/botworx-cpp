/*Botworx AI - An Artificial Intelligence Framework
Copyright (C) 2004  Kurtis Fields. See BotworxAI_License.txt for details.
*/
#ifndef _AiMetabit_h
#define _AiMetabit_h

#include "AiTypeInfo.h"
#include "AiMeta_meta.h"

//
//AiMetabit
//
class AiMetabit : public BwCell {
public:
	AiMetabit(AiMetabit* pParent, AiMbInfo &pInfo, ThingTT typeId) ;
	virtual void init() ;
	//Accessors
	AiSymbol* getName() { return p_name.get() ; }
	AiMbInfo* getInfo() { return p_info ; }
	//Data Members
	AiMetabit* p_parent ;
	AiSymbolPtr p_name ;
	AiMbInfo*    p_info ;
	unsigned int m_flags ;
};

#define getMbTT(X) (ifOfTT(X, TT_SLOT) : ifTT(X, TT_DESC) : TT_NIL )

#endif //_AiMetabit_h