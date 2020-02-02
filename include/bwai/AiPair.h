/*Botworx AI - An Artificial Intelligence Framework
Copyright (C) 2004  Kurtis Fields. See BotworxAI_License.txt for details.
*/
#ifndef _AiPair_H
#define _AiPair_H

class AiPair : public BwCell {
public:
	AiPair(BwCell* pLeft, BwCell* pRight) : BwCell(TT_PAIR) {
		p_left = pLeft ;
		p_right = pRight ;
	}
	~AiPair() {
	}
	void *operator new(size_t count) throw() ;
	virtual void purge() ;
	//
	void setLeft(BwCell* pCell) { p_left = pCell ; }
	BwCell* getLeft() const { return p_left.get() ; }
	void setRight(BwCell* pCell) { p_right = pCell ; }
	BwCell* getRight() const { return p_right.get() ; }
	//Data
	BwCellPtr p_left ; //car
	BwCellPtr p_right ; //cdr
} ;
//typedef boost::intrusive_ptr<AiPair> AiPairPtr ;
//
inline bool isPair(const BwCell* cell) { return cell->getTypeId() == TT_PAIR ; }
#define notPair(C) (C->getTypeId() != TT_PAIR)
//#define asPair(C) (static_cast<AiPair*>(C))
inline AiPair* asPair(BwCell* pCell) {
	bwAssert( pCell == NULL ? true : pCell->getTypeId() == TT_PAIR ) ;
	return static_cast<AiPair*>(pCell) ;
}
#define asConstPair(C) (static_cast<const AiPair*>(C))
//
#include "AiKit.h"

class AiPairKit : public AiPoolKitT<AiKit, AiPair> {
public:
	AiPairKit(AiKit*  pSuperKit, AiKitInfo *pKitInfo)
		: AiPoolKitT<AiKit, AiPair>(KT_PAIR, pSuperKit, pKitInfo) {}
} ;
DECLARE_KITINFO(AiPairKit) ;
//
//AiPair
//
inline void* AiPair::operator new(size_t size)  throw() {
#if AI_OPTION_POOLING
	return k_pair().rent() ;
#else
	return BW_USERMALLOC(size, TT_PAIR) ;
#endif
}
//
#include <bwai/AiPair_inline.h>

#endif //_AiPair_H
