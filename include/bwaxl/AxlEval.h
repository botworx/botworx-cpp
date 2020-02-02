#ifndef _AxlEval_h
#define _AxlEval_h

#include <bwai/AiKit.h>
#include "AxlXop.h"

class AxlEval : public AxlXop {
public:
	AxlEval(AxlXopType *pMeta, ThingLength length)
		: AxlXop(pMeta, length) {
		m_argLength = 0 ;
	}
	AiPair* getArgs() { return p_args.get() ; }
	AiPair* getArgSlots() { return p_argSlots.get() ; }
	//Data Members
	AxlBxType* p_factory ;
	AiPairPtr p_args ;
	AiPairPtr p_argSlots ;
	ThingLength m_argLength ;
} ;
#define isEval(X) (isTT(X, XOP_EVAL))
#define asEval(X) ((AxlEval*)X)

//AxlEvalKit
class AxlEvalKit : public AiKit {
public:
	AxlEvalKit(AiKit* pSuperKit, AiKitInfo *pKitInfo)
		: AiKit(AXL_KT_EVAL, pSuperKit, pKitInfo) {
	}
} ;
DECLARE_KITINFO(AxlEvalKit) ;

//
extern AxlOpcode AxlEval_processArg(AxlEval *pThis, AiSlot* pArgSlot, BwCell* pArg) ;
extern AxlOpcode AxlEval_processFArg(AxlEval *pThis, AiSlot* pArgSlot) ;
extern AxlOpcode AxlEval_processFArgs(AxlEval *pThis, AiPair* pArgSlots) ;
extern ThingLength AxlEval_getArgLength(AxlEval *pThis) ;



#endif //_AxlEval_h
