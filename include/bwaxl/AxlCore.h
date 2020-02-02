/*Botworx AI - An Artificial Intelligence Framework
Copyright (C) 2004  Kurtis Fields. See BotworxAI_License.txt for details.
*/
#ifndef _AxlCore_H
#define _AxlCore_H

#include <bwai/AiCore.h>

//kit forward defs
class AxlFiber ;
class AxlBxKit ;
class AxlXopKit ;
class AxlRawKit ;
class AxlXnKit ;
class AxlCatcherKit ;
class AxlEvalKit ;
class AxlReplKit ;
class AxlReplKit ;
class AxlLetKit ;
class AxlFnKit ;
class AxlControlKit ;
class AiBlobKit ;

class AxlCore : public AiCore {
public:
	AxlCore(AiKit*  pSuperKit, AiKitInfo *pKitInfo) ;
	~AxlCore() ;
	static AxlCore* createInstance() ;
	//
	virtual void doConfig() ;
	virtual void createPrinter() ;
	virtual void createLogger() ;
	virtual void createStack() ;
	//
	void run() ;
	//
	void setFiber(AxlFiber* pFiber) { p_fiber = pFiber ; }
	AxlFiber* getFiber() { return p_fiber ; }
	void* getStack() { return p_stack ; }
	unsigned int getStackSize() { return m_stackSize ; }
	//Data Members
	void* p_stack ; //TODO:?shared stack?
	unsigned int m_stackSize ;
	AxlFiber* p_fiber ; //currently executing fiber
} ;
DECLARE_KITINFO(AxlCore) ;
#define asAxlCore(X) (static_cast<AxlCore*>(X))

#endif //_AxlCore_H
