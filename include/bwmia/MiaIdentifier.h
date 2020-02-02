/*Botworx AI - An Artificial Intelligence Framework
Copyright (C) 2004  Kurtis Fields. See BotworxAI_License.txt for details.
*/
#ifndef _MiaIdentifier_H
#define _MiaIdentifier_H

#include "MiaFact.h"

class MiaSpace ;
//
//MiaIdentifier
//
class MiaIdentifier : public MiaFact {
public:
	MiaIdentifier(AiSymbol* pSymbol) ;
	void *operator new(size_t count) throw() ;
	virtual void purge() ;
	//
	void setSpace(MiaSpace* pSpace) { p_space = pSpace ; }
	MiaSpace* getSpace() { return p_space ; }
	//
	friend MiaPrinter& operator<<(MiaPrinter &printer, const MiaIdentifier& data) ;
	//Data Members
	MiaSpace* p_space ;
	//LinkId
	void setHasFillers(bool val) { m_hasFillers = val ; }
	bool hasFillers() { return m_hasFillers ; }
	bool m_hasFillers ;
} ;
#define asIdentifier(X) (static_cast<MiaIdentifier*>(X))
#define asConstIdentifier(X) (static_cast<const MiaIdentifier*>(X))
//
//MiaIdentifierKit
//
#include <bwai/AiKit.h>

class MiaIdentifierKit : public AiPoolKitT<AiKit, MiaIdentifier> {
public:
	MiaIdentifierKit(AiKit*  pSuperKit, AiKitInfo *pKitInfo) 
		: AiPoolKitT<AiKit, MiaIdentifier>(MIA_KT_IDENTIFIER, pSuperKit, pKitInfo) {}
} ;
DECLARE_KITINFO(MiaIdentifierKit) ;
//
//MiaIdentifier
//
inline void* MiaIdentifier::operator new(size_t size) throw() {
#if AI_OPTION_POOLING
	return k_identifier().rent() ;
#else
	return (MiaIdentifier*)BW_USERMALLOC(size, MIA_TT_IDENTIFIER) ;
#endif
}
inline MiaIdentifier* internId(AiSymbol* pSymbol) {
	MiaIdentifier* pId = static_cast<MiaIdentifier*>(GetGlobalVal(pSymbol)) ;
	if(pId != UNBOUND)
		return pId ;
	//else
	pId = new MiaIdentifier(pSymbol) ;
	return pId ;
}
#endif //_MiaIdentifier_H