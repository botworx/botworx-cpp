/*Botworx AI - An Artificial Intelligence Framework
Copyright (C) 2004  Kurtis Fields. See BotworxAI_License.txt for details.
*/
#include "stdafx.h"

#include <bwmia/MiaIdentifier.h>
#include <bwmia/MiaTopic.h>
#include <bwmia/MiaFactory.h>
#include <bwmia/MiaPrinter.h>
//
// MiaFact
//
void MiaFact::purge() {
	if(getSubject() == NULL) {
		AiSymbol* pName = asSymbol(getValue()) ;
		pName->setVal(NULL) ;
	}
	MiaFact::~MiaFact() ;
#if AI_OPTION_POOLING
	k_fact().release(this) ;
#else
	BW_USERFREE(this, MIA_TT_FACT) ;
#endif
}
MiaFact* MiaFact::clone() {
	MiaFact* pClone = new MiaFact(getSubject(), getLink(), getValue(), getTruth()) ;
	return pClone ;
}
void MiaFact::setPropertyVal(AiSymbol* pSymbol, BwCell* pVal) {
	bwAssert(0) ; //implement ... if pSymbol != subject, link or value pass request to topic.
}
BwCell* MiaFact::getPropertyVal(AiSymbol* pSymbol) {
	if(pSymbol == PSYM_SUBJECT)
		return getSubject() ;
	else if (pSymbol == PSYM_LINK)
		return getLink() ;
	else if (pSymbol == PSYM_VALUE)
		return getValue() ;
	else
		return NULL ;
}
inline void MiaFact_printSubject(MiaPrinter &printer, const MiaFact& data) {
	if(!data.isIdentifier())
		if(!data.subject().isIdentifier()) //an identity fact
			printer << data.subject() ;
		else
			printer << data.subject().value() ;
	else
		printer << data.value() ;
}
inline void MiaFact_printVal(MiaPrinter &printer, const MiaFact& data) {
	if(data.getValue() != &data) {
		if(ofTT(data.getValue()->getTypeId(), MIA_TT_FACT))
			printer.printCell(asFact(data.getValue())->getValue()) ;
		else
			printer.printCell(data.getValue()) ;
		//os << " " ;
	}
	else
		printer << "value:this" ;
}
MiaPrinter& operator<<(MiaPrinter &printer, const MiaFact& data) {
	printer << "( " ;
	//Subject
	MiaFact_printSubject(printer, data) ;
	printer << " " ;
	//Link
	if(data.getLink() != &data) {
		printer.printCell(data.p_link->getValue()) ;
	}
	else
		printer << "link:this" ;
	printer << " " ;
	//Value
	MiaFact_printVal(printer, data) ;
	printer << " )" ;

	return printer ;
}
//
// MiaFactKit Meta
//
DEFINE_KITTYPE(MiaFactKit) ;

TYPEINFO_NONE(MiaFactKit) ;
NO_KITINFO(MiaFactKit) ;

KITINFO("MiaFactKit", MIA_KT_FACT, MiaFactKit) ;
