#ifndef _AxlFiber_H
#define _AxlFiber_H

#include "AxlBx.h"

#define AXLSTACK_SIZE 1048576 //1 Megabyte for now...

class AxlEval ;
class AxlCatcher ;
class AxlScope ;
class AxlBx ;

class AxlFiber {
public:
	AxlFiber(void *pStackRoof, unsigned int stackSize) ;
	void run() ;
	AxlOpcode stepFor(int ticks) ;
	//private
	AxlOpcode doStep() ;
	AxlOpcode eval() ;
	AxlOpcode evalForm(AiPair *pPair) ;
	AxlOpcode evalEnd() ;
	void setResult(BwCell* pVal) { p_result = pVal ; }
	BwCell* getResult() { return p_result ; }
	//BwCell* getResult() { return p_result.get() ; }
	void setScopeVal(AiSymbol* pSym, BwCell* pVal) ;
	BwCell* getScopeVal(AiSymbol *pSym) ;
	//f6:newstuff:
	virtual void setLogicVal(AiSymbol* pSymbol, BwCell* pVal) {}
	virtual BwCell* getLogicVal(AiSymbol* pSymbol) { return UNBOUND ; }
	virtual void setPropertyVal(AiSymbol* pSymbol, BwCell* pVal) {}
	virtual BwCell* getPropertyVal(AiSymbol* pSymbol) { return UNBOUND ; }
	//f6:newstuff:end
	AxlEval* getEvaluator() { return ((AxlEval*)p_topBx) ; }
	AxlEval& evaluator() { return *((AxlEval*)p_topBx) ; }
	//
	void setErrorDesc(char* pDesc) { p_errorDesc = pDesc ; }
	char* getErrorDesc() { return p_errorDesc ; }
	//
	AxlOpcode setNextOp(AxlOpcode opCode) {
		//bwAssert(opCode > 0 && opCode <= AITYPE_MAX) ;
		m_nextOp = opCode ;
		return opCode ;
	}
	AxlOpcode getNextOp() { return m_nextOp ; }
	void pushOp() { p_topBx->m_nextOp = m_nextOp ; }
	AxlOpcode popOp() { return setNextOp(p_topBx->m_nextOp) ; }
	AxlOpcode jumpOp(AxlOpcode opCode) { return setNextOp(opCode) ; }
	//Data Members
	char *p_errorDesc ; //debug aid ... remove later?
	BwCell *p_ball ; //item currently being thrown
	AxlCatcher *p_catcher ; //top catcher
	AxlScope *p_scope ; //top scope
	AxlBx *p_topBx ;
	BwCell* p_result ;
	//
	void setStackTop(void* pTop) {
		bwAssert(pTop >= p_stackRoof) ;
		bwAssert(pTop <= p_stackFloor) ;
		p_stackTop = pTop ;
	}
	void* getStackTop() { return p_stackTop ; }
private:
	void *p_stackRoof ;
	void *p_stackFloor ;
	void *p_stackTop ;
	//
	AxlOpcode m_nextOp ;
} ;

#endif //_AxlFiber_H
