/*Botworx AI - An Artificial Intelligence Framework
Copyright (C) 2004  Kurtis Fields. See BotworxAI_License.txt for details.
*/
#ifndef _AiPair_inline_H
#define _AiPair_inline_H
 
inline BwCell* car(const AiPair* pPair) { return pPair->getLeft() ; }
inline AiPair* pairCar(AiPair* pPair) { return asPair(car(pPair)) ; }
inline AiSymbol* symbolCar(AiPair* pPair) { return asSymbol(car(pPair)) ; }

inline BwCell* cdr(const AiPair* pPair) { return pPair->getRight() ; }
inline AiPair* pairCdr(AiPair* pPair) { return asPair(cdr(pPair)) ; }

inline BwCell* cadr(AiPair* pPair) { return car(pairCdr(pPair)) ; }
inline BwCell* cddr(AiPair* pPair) { return cdr(pairCdr(pPair)) ; }
inline BwCell* caddr(AiPair* pPair) { return car(pairCdr(pairCdr(pPair))) ; }
inline BwCell* cadddr(AiPair* pPair) { return car(pairCdr(pairCdr(pairCdr(pPair)))) ; }

inline BwCell* safeCaddr(AiPair* pPair) { 
	AiPair *pVal = pPair ;
	if(pVal == NIL) return NIL ;
	pVal = pairCdr(pVal) ;
	if(pVal == NIL) return NIL ;
	pVal = pairCdr(pVal) ;
	if(pVal == NIL) return NIL ;
	return car(pVal) ;
}
inline BwCell* safeCadddr(AiPair* pPair) { 
	AiPair *pVal = pPair ;
	if(pVal == NIL) return NIL ;
	pVal = pairCdr(pVal) ;
	if(pVal == NIL) return NIL ;
	pVal = pairCdr(pVal) ;
	if(pVal == NIL) return NIL ;
	pVal = pairCdr(pVal) ;
	if(pVal == NIL) return NIL ;
	return car(pVal) ;
}

inline void rplaca(AiPair* pPair, BwCell *pCell) {
	pPair->p_left = pCell ;
}
inline void rplacd(AiPair* pPair, BwCell *pCell) {
	pPair->p_right = pCell ;
}
//Pair and List helper functions.
inline AiPair* cons(BwCell* pLeft, BwCell* pRight) {
	return new AiPair(pLeft, pRight) ;
}
inline AiPair* consa(BwCell* pLeft) {
	return new AiPair(pLeft, NIL) ;
}
inline AiPair* consd(BwCell* pRight) {
	return new AiPair(NIL, pRight) ;
}
inline AiPair* tail(AiPair* pHead) {
	AiPair* pTail = pHead ;
	while(pTail->p_right != NIL)
		pTail = asPair(pTail->getRight()) ;
	return pTail ;
}
inline AiPair* appendList(AiPair* pHead, AiPair* pTail) {
	AiPair* pNewHead = pHead ;
	while(pNewHead->p_right != NIL)
		pNewHead = asPair(pNewHead->getRight()) ;
	rplacd(pNewHead, pTail) ;
	return pHead ;
}
inline AiPair* reverseList(AiPair* pList) {
	AiPair* pVal = NULL ;
    while (isPair(pList)) {
	pVal = cons(car(pList), pVal) ;
	pList = asPair(cdr(pList)) ;
    }
    return pVal ;
}
//Create new association and return prepended list.
inline AiPair* defAssoc(AiPair* pPair, BwCell* pLeft, BwCell* pRight) {
	AiPair* pAssoc = cons(pLeft, pRight) ;
	AiPair* pLink = cons(pAssoc, pPair) ;
	return pLink ;
}
//Find pair by left value and return it
inline AiPair* findAssocLeft(AiPair* pPair, BwCell* pKey) {
	AiPair* pAssoc = NULL ;
	BwCell* pRight = NIL ;
	BwCell* pLeft = NIL ;
	for(; pPair != NULL ; pPair = pairCdr(pPair)) {
		pAssoc = asPair(car(pPair)) ;
		pLeft = car(pAssoc) ;
		if(isEq(pLeft, pKey)) {
			return pAssoc ;
		}
	}
	return NULL ;
}
inline AiPair* assoc(BwCell* pKey, AiPair* pPair) {
	return findAssocLeft(pPair, pKey) ;
}
inline BwCell* setAssocRight(AiPair* pPair, BwCell* pLeft, BwCell* pRight) {
	AiPair* pAssoc = findAssocLeft(pPair, pLeft) ;
	if(pAssoc == NULL )
		return NIL ;
	rplacd(pAssoc, pRight) ;
	return SYM_TRUE ;
}
inline BwCell* getAssocRight(AiPair* pPair, BwCell* pLeft) {
	AiPair* pAssoc = findAssocLeft(pPair, pLeft) ;
	if(isNil(pAssoc))
		return NIL ;
	//else
	return cdr(pAssoc) ;
}
//destructive removal
inline AiPair* removeCons(BwCell* pCell, AiPair* pList) {
	AiPair* pLastPair = NULL ;
	BwCell* pCar = NULL ;

	for(AiPair* pExpr = pList ; pExpr != NIL ;  pExpr = pairCdr(pExpr)) {
		pCar = car(pExpr) ;
		if(pCar == pCell) {
			if(pLastPair == NIL) { //means this is head of list!
				if(pExpr->p_right == NULL) //means head and tail
					return NULL ;
				//else
				return pairCdr(pExpr) ;
			}
			else {
				pLastPair->p_right = pExpr->p_right ;
				return pList ;
			}
		}
	}
	return pList ;	
}
inline AiPair* removePair(AiPair* pPair, AiPair* pList) {
	AiPair* pLastPair = NULL ;
	AiPair* pCdr = NULL ;

	for(AiPair* pExpr = pList ; pExpr != NIL ;  pExpr = pairCdr(pExpr)) {
		pCdr = pairCdr(pExpr) ;
		if(pCdr == pPair) {
			if(pLastPair == NIL) { //means this is head of list!
				if(pExpr->p_right == NULL) //means head and tail
					return NULL ;
				//else
				return pairCdr(pExpr) ;
			}
			else {
				pLastPair->p_right = pExpr->p_right ;
				return pList ;
			}
		}
	}
	return pList ;	
}
#endif //_AiPair_inline_H