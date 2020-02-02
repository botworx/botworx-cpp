#ifndef _AxlCatcher_h
#define _AxlCatcher_h

/*
	Purpose: Implement exception handling.
	Allocation: Virtual stack only.
*/

#include "AxlBx.h"

//
//AxlCatcher
//
class AxlCatcher : public AxlBx {
public:
	AxlCatcher(AiType* pCatchType, AxlXdx catchXdx) ;
	void *operator new(size_t count) throw() ;
	void operator delete(void* _Ptr) throw() { bwAssert(0) ; } //class is on stack!!!
	virtual AxlOpcode exec() ;
	bool canCatch(BwCell *pBall) { return true ; } //TODO: - implement
	AxlOpcode catchBall(BwCell *pBall) {
		p_prevBx->m_xdx = m_catchXdx ;
		//printf("AxlCatcher: caught what? ") ;
		//catcherEnd() ;
		return OP_NOP ;
	}
	AxlOpcode missBall(BwCell *pBall) {
		printf("AxlCatcher: Missed what? ") ;
		//catcherEnd() ;
		return OP_NOP ;
	}
	//Data Members
	AxlCatcher *p_prevCatcher ;
	AxlScope *p_prevScope ;
	AiType* p_catchType ;
	AxlXdx m_catchXdx ; //set p_prevBx->m_xdx to this after catching
} ;
#define asCatcher(B) ((AxlCatcher*)B)
//
//AxlCatcherKit
//
class AxlCatcherKit : public AiKit {
public:
	AxlCatcherKit(AiKit* pSuperKit, AiKitInfo *pKitInfo)
		: AiKit(AXL_KT_CATCHER, pSuperKit, pKitInfo) {
	}
} ;
DECLARE_KITINFO(AxlCatcherKit) ;
//
//AxlCatcher
//
#define axlCatch(M,X) (new AxlCatcher(M, X))

#endif //_AxlCatcher_h
