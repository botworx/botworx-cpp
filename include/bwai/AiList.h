#ifndef _AiList_H
#define _AiList_H

#include "AiPair.h"
#include <bwstd/BwDumbPtr.h>
/*
Pair helper class.  Inline usage only.
*/
template <typename T>
class AiListT {
public:
	AiListT() {}
	~AiListT() {}
	AiListT(AiPair* pHead) {
		set(pHead) ;
	}
	void set(AiPair* pHead) {
		p_head = pHead ;
		if(pHead != NULL)
			p_tail = tail(pHead) ;
		else
			p_tail = NULL ;
	}
	void clear() { p_head = p_tail = NULL ; }
	bool empty() { return p_head == NULL ; }
	bool hasTail() { return p_tail != NULL ; }
	AiPair* append(AiPair* pPair) {
		if(p_head == NULL) {
			p_head = p_tail = pPair ;
			return pPair ;
		}
		//else
		AiPair* pOldTail = getTail() ;
		pOldTail->setRight(pPair) ;
		p_tail = pPair ;
		return get() ;
	}
	AiPair* push_front(BwCell* pVal) {
		bwAssert(0) ;
		AiPairPtr pHead = p_head ;
		p_head = consa(pVal) ;
		p_head->p_right = pHead ;
		return p_head ;
	}
	void pop_front() {
		erase(get()) ;
	}
	AiPair* push_back(BwCell* pVal) {
		return append(consa(pVal)) ;
	}
	void pop_back() {
		erase(getTail()) ;
	}
	void erase(AiPair* pPair) {
		set(removePair(pPair, get())) ;
	}
	//
	AiPair* get() const { return p_head.get() ; }
	BwCell* front() const { return car(get()) ; }
	AiPair* getTail() const { return p_tail.get() ; }
	BwCell* back() const { return car(getTail()) ; }
	//Data Members
	T p_head ;
	T p_tail ;
};
typedef AiListT< boost::dumb_ptr<AiPair> > AiFastList ;
typedef AiListT<AiPairPtr> AiList ;

#endif //_AiList_H
