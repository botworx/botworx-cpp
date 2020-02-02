/*Botworx AI - An Artificial Intelligence Framework
Copyright (C) 2004  Kurtis Fields. See BotworxAI_License.txt for details.
*/
#include "stdafx.h"

#include <bwmia/MiaIdentifier.h>
#include <bwmia/MiaSpace.h>

//
// MiaIdentifier
//
void MiaIdentifier::purge() {
	if(getSubject() == NULL) {
		AiSymbol* pName = asSymbol(getValue()) ;
		pName->setVal(NULL) ;
	}
	MiaIdentifier::~MiaIdentifier() ;
#if AI_OPTION_POOLING
	k_identifier().release(this) ;
#else
	BW_USERFREE(this, MIA_TT_IDENTIFIER) ;
#endif
}

MiaIdentifier::MiaIdentifier(AiSymbol* pSymbol) : MiaFact(MIA_TT_IDENTIFIER) {
	setLink(SUBJECT_NAME) ;
	setValue(pSymbol) ;
	SetGlobalVal(pSymbol, this) ;
	if(pSymbol->isInterned()) {
		pSymbol->m_refCount = --pSymbol->m_refCount ;
	}
	else
	{
		m_refCount = --m_refCount ;
	}
	//
	p_space = NULL ;
	//LinkId
	m_hasFillers = false ;
}
//
MiaPrinter& operator<<(MiaPrinter &printer, const MiaIdentifier& data) {
	printer.printCell(data.getValue()) ; //value is a symbol
	return printer ;
}
//
// MiaIdentifierKit Meta
//
DEFINE_KITTYPE(MiaIdentifierKit) ;

TYPEINFO_NONE(MiaIdentifierKit) ;
NO_KITINFO(MiaIdentifierKit) ;

KITINFO("MiaIdentifierKit", MIA_KT_IDENTIFIER, MiaIdentifierKit) ;
