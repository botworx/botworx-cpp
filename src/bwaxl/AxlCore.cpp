/*AXL - A Lispish interpreter for Botworx AI - An Artificial Intelligence Framework
Copyright (C) 2004  Kurtis Fields. See BotworxAI_License.txt for details.
*/
#include "stdafx.h"

#include <bwaxl/AxlFiber_impl.h>
#include <bwaxl/AxlBx.h>
#include <bwaxl/AxlXn.h>
#include <bwaxl/AxlEval.h>
#include <bwaxl/AxlRepl.h>
#include <bwaxl/AxlPrinter.h>
#include <bwaxl/AxlXop.h>
//
// AxlCore
//
AxlCore::AxlCore(AiKit* pKit, AiKitInfo *pKitInfo) : AiCore(pKit, pKitInfo)  {
}
AxlCore::~AxlCore() {
	BW_FREE(p_stack) ;
}
AxlCore* AxlCore::createInstance() {
	AxlCore* pThis = new AxlCore(NULL,KITINFOREF(AxlCore)) ;
	pThis->createEnabled() ;
	return pThis ;
}
void AxlCore::doConfig() {
	AiCore::doConfig() ;
	createStack() ;
}
//TODO:need to chain sinks ...?
void AxlCore::createPrinter() {
	p_printer = new AxlPrinter(std::cout) ;
}
void AxlCore::createLogger() {
	AiCore::createLogger() ;
	/*std::string fileName = "../log/log.txt" ;
	std::ofstream* pOut = new std::ofstream(fileName.c_str(), std::ios_base::out | std::ios_base::trunc );
	p_logger = new AxlPrinter(*pOut) ;*/
}
void AxlCore::createStack() {
	m_stackSize = AXLSTACK_SIZE ;
	p_stack = BW_MALLOC(m_stackSize) ; 
}
void AxlCore::run() {
	AxlFiber fiber(getStack(), getStackSize()) ;
	setFiber(&fiber) ;
	new AxlBootBx() ;
	fiber.run() ;
}