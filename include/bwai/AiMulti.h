/*Botworx AI - An Artificial Intelligence Framework
Copyright (C) 2004  Kurtis Fields. See BotworxAI_License.txt for details.
*/
#ifndef _AiMulti_H
#define _AiMulti_H

#include "AiList.h"

class AiMulti : public BwCell {
public:
	AiMulti(AiPair* pVals) : BwCell(TT_MULTI) {
		//p_list = pVals ;
		m_list.set(pVals) ;
	}
	~AiMulti() {
	}
	void *operator new(size_t count) throw() ;
	virtual void purge() ;
	//
	//AiPair* getList() const { return p_list.get() ; }
	AiPair* getList() const { return m_list.get() ; }
	//Data
	//AiPairPtr p_list ;
	AiList m_list ;
} ;
typedef boost::intrusive_ptr<AiMulti> AiMultiPtr ;
//
inline bool isMulti(const BwCell* cell) { return cell->getTypeId() == TT_MULTI ; }
#define notMulti(C) (C->getTypeId() != TT_MULTI)
#define asMulti(C) (static_cast<AiMulti*>(C))
#define asConstMulti(C) (static_cast<const AiMulti*>(C))
//
#include "AiKit.h"

class AiMultiKit : public AiPoolKitT<AiKit, AiMulti> {
public:
	AiMultiKit(AiKit*  pSuperKit, AiKitInfo *pKitInfo) 
		: AiPoolKitT<AiKit, AiMulti>(KT_MULTI, pSuperKit, pKitInfo) {}
} ;
DECLARE_KITINFO(AiMultiKit) ;
//
inline void* AiMulti::operator new(size_t size) throw() {
#if AI_OPTION_POOLING
	return k_multi().rent() ;
#else
	return BW_USERMALLOC(size, TT_MULTI) ;
#endif
}

#endif //_AiMulti_H
