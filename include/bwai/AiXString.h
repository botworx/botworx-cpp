/*Botworx AI - An Artificial Intelligence Framework
Copyright (C) 2004  Kurtis Fields. See BotworxAI_License.txt for details.
*/
#ifndef _AiXString_H
#define _AiXString_H

#include "AiString.h"

//
//AiXString
//
class AiXString : public AiString {
public:
	AiXString(const bwString& string) : AiString(TT_XSTRING, string) {
	}
	void *operator new(size_t count) throw() ;
	virtual void purge() ;
	//
	void addFragment(BwCell* pCell) { m_fragments.push_back(pCell) ; }
	//Data
	typedef std::list<BwCellPtr> FragmentList ;
	typedef FragmentList::iterator FragmentIter ;
	FragmentList m_fragments ;
} ;

typedef std::pair<char*, AiXString*> AiXStringPair ;
#define isXString(C) (C->getTypeId() == TT_XSTRING)
#define asXString(C) (static_cast<AiXString*>(C))
//
//AiXStringKit
//
#include "AiKit.h"

class AiXStringTable ;

class AiXStringKit : public AiPoolKitT<AiKit, AiXString> {
public:
	AiXStringKit(AiKit*  pSuperKit, AiKitInfo *pKitInfo) 
		: AiPoolKitT<AiKit, AiXString>(KT_XSTRING, pSuperKit, pKitInfo) {}
} ;
#define asXStringKit(C) ((AiXStringKit*)C)
DECLARE_KITINFO(AiXStringKit) ;
//
//AiXString
//
inline void* AiXString::operator new(size_t size) throw() {
#if AI_OPTION_POOLING
	return k_xstring().rent() ;
#else
	return BW_USERMALLOC(size, TT_XSTRING) ;
#endif
}

#include <bwai/AiXString_inline.h>

#endif //_AiXString_H
