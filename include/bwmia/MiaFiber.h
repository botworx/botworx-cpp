#ifndef _MiaFiber_H
#define _MiaFiber_H

#include <bwaxl/AxlFiber_impl.h>

class MiaFiber : public AxlFiber {
public:
	MiaFiber(MiaBinder& binder, void *pStackRoof, unsigned int stackSize) ;
	BwCell* eval(BwCell* pExpr) ;
	virtual void setLogicVal(AiSymbol* pSymbol, BwCell* pVal) ;
	virtual BwCell* getLogicVal(AiSymbol* pSymbol) ;
	virtual void setPropertyVal(AiSymbol* pSymbol, BwCell* pVal) ;
	virtual BwCell* getPropertyVal(AiSymbol* pSymbol) ;
	MiaBinder* getBinder() { return p_binder ; }
	MiaBinder& binder() { return *p_binder ; }
	//Data Members
	MiaBinder* p_binder ;
} ;


#endif //_MiaFiber_H
