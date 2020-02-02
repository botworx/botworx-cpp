#ifndef _AxlFiber_inline_h
#define _AxlFiber_inline_h

#include "AxlFiber.h"
#include <bwai/AiType.h>

class AxlBxType ;
class AxlXop ;

#define P_EVAL (k_fiber().getEvaluator())

#define growStack(X, Y) (((char*)X) - Y)
#define shrinkStack(X, Y) (((char*)X) + Y)

template<typename T>
void setCellAt(T* pThis, int ndx, BwCell* pCell) {
}
template<typename T>
BwCell* getCellAt(T* pThis, int ndx) {
	return	(*((BwCell**) ( ((char*)pThis) + (sizeof(T)) + ( pThis->m_length-(ndx+1)) * (sizeof(BwCell*)) ) ) )  ;
}
//
template<typename T>
BwCell* getBlobCellAt(T* pThis, int ndx) {
	return (*((BwCell**) ( ((char*)pThis) + (getThingASize(pThis->getMeta())) + ( pThis->m_length-(ndx+1)) * (sizeof(BwCell*)) ) ) )  ;
}
#define getXopCellAt(I) getCellAt((AxlXop*)k_fiber().p_topBx, I)
//
#define processFArgs(S) (AxlEval_processFArgs(P_EVAL, S))
#define processFArg(S) (AxlEval_processFArg(P_EVAL, S))
#define processArg(S,A) (AxlEval_processArg(P_EVAL, S,A))
#define pushArgs(A) (axlPushArgs(A))
#define getArgLength() (AxlEval_getArgLength(P_EVAL))

#define pushEval() (AxlFiber_pushEval(k_getFiber(), 0))
#define pushEval1() (AxlFiber_pushEval(k_getFiber(), 1))
#define popEval() (AxlFiber_popEval(k_getFiber()))
#define callEval1(A) return axlCallEval1(A)
#define jumpEval1(A) return axlJumpEval1(A)
#define getEvalCellAt(I) getCellAt(P_EVAL, I)
//
#define axlPushVal(V) (AxlFiber_pushVal(k_getFiber(), V))
#define axlPopVal() (AxlFiber_popVal(k_getFiber()))
//
#define axlSetNextOp(O) (k_fiber().setNextOp(O))
#define axlGetNextOp(O) (k_fiber().getNextOp())
//
#define axlPushBx(S) (AxlFiber_pushBx(k_getFiber(), S))
#define axlPopBx() (AxlFiber_axlPopBx(k_getFiber()))
#define getBxCellAt(I) getBlobCellAt(k_fiber().p_topBx, I)

#define axlPushOp() (k_fiber().pushOp())
#define axlPopOp() (k_fiber().popOp())
//
#define jumpBx() return axlJumpBx()
#define callBx() return axlCallBx() //TODO: - new meta index version
#define callBx1(V1) return axlCallBx(V1)
#define callBx2(V1, V2) return axlCallBx2(V1,V2)
//
#define pushXop(O) (AxlFiber_pushXop(k_getFiber(), O, 0))
#define pushXop1(O) (AxlFiber_pushXop(k_getFiber(), O, 1))
#define pushXopN(O, I) (AxlFiber_pushXop(k_getFiber(), O, I))
#define popXop() (AxlFiber_popXop(k_getFiber()))
#define jumpXop() return axlJumpXop()
#define callXop(O) return axlCallXop(O) //k_fiber().p_topBx->m_nextOp = 
#define callXop1(O,V1) return axlCallXop1(O,V1)
#define callXop2(O,V1,V2) return axlCallXop2(O,V1,V2)
#define callXopArgs(O, A) return axlCallXopArgs(O, A)
#define xopEnd() return axlXopEnd()
//
#define opAgain() return(k_fiber().m_nextOp)
#define bxAgain() return(OP_BXEXEC) 
#define bxEnd() return(OP_BXEND)
#define bxReturn(X) return axlBxReturn(X) //TODO:?
#define bxError() return(OP_ERROR)
#define axlSetResult(V) (k_fiber().p_result = V)
//void axlSetResult(AxlFiber& fiber, BwCell* pVal) { fiber.setResult(pVal) ; }
#define axlGetResult() (k_fiber().getResult())
#define axlPushResult() (axlPushVal(k_fiber().getResult()))
#define axlPopResult() (k_fiber().p_result = popVal()) //TODO::unused
//
#define beginScope(B) (AxlFiber_beginScope(k_getFiber(), B))
#define endScope() (AxlFiber_endScope(k_getFiber()))
//
#define axlPushCatcher(M) (AxlFiber_pushCatcher(k_getFiber(), M))
//#define axlPopCatcher() (AxlFiber_popCatcher(k_getFiber())) //TODO:whats up with this?
#define setBall(B) (k_fiber().p_ball = B)
#define getBall() (k_fiber().p_ball)
#define throwBall(B) return AxlFiber_throwBall(k_getFiber(), B)
#define relayBall() return OP_THROW ; //TODO:? ...
#define throwXn(X) throwBall(new AxlXn(TYPEDIR(X)))

inline AxlOpcode axlError(char *pErrorDesc) {
	k_fiber().setErrorDesc(pErrorDesc) ;
	throw BwGeneralException(pErrorDesc) ;
	return OP_ERROR ;
}

extern AxlOpcode AxlFiber_throwBall(AxlFiber *pThis, BwCell *pBall) ;
extern void AxlFiber_pushVal(AxlFiber *pThis, BwCell* pVal) ;
extern BwCell* AxlFiber_popVal(AxlFiber *pThis) ;
//
extern AxlScope* AxlFiber_beginScope(AxlFiber *pThis, AxlBx *pBx) ;
extern void AxlFiber_endScope(AxlFiber *pThis) ;
//
extern AxlBx* AxlFiber_pushBx(AxlFiber *pThis, ThingSize size) ;
extern AxlBx* AxlFiber_axlPopBx(AxlFiber *pThis) ;
extern AxlOpcode axlJumpBx() ;
extern AxlOpcode axlCallBx() ;
extern AxlOpcode axlCallBx1(BwCell *p1) ;
extern AxlOpcode axlCallBx2(BwCell *p1, BwCell *p2) ;
extern AxlOpcode axlBxEnd() ;
extern AxlOpcode axlBxReturn() ;
//
extern AxlXop* AxlFiber_pushXop(AxlFiber *pThis, AxlOpcode opCode, ThingLength length) ;
extern AxlBx* AxlFiber_popXop(AxlFiber *pThis) ;
extern AxlOpcode axlJumpXop() ;
extern AxlOpcode axlCallXop(AxlOpcode callOp) ;
extern AxlOpcode axlCallXop1(AxlOpcode callOp, BwCell *p1) ;
extern AxlOpcode axlCallXop2(AxlOpcode callOp, BwCell *p1, BwCell *p2) ;
extern AxlOpcode axlCallXopArgs(AxlOpcode callOp, AiPair *pArgs) ;
extern AxlOpcode axlCallEval1(BwCell* pVal) ;
extern AxlOpcode axlJumpEval1(BwCell* pVal) ;
extern AxlOpcode axlXopEnd() ;
//
extern AxlCatcher * AxlFiber_pushCatcher(AxlFiber *pThis, AxlBxType *pCatcherType) ;
extern AxlBx* AxlFiber_popCatcher(AxlFiber *pThis, AxlCatcher *pCatcher) ;

#endif //_AxlFiber_inline_h
