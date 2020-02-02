/*AXL - A Lispish interpreter for Botworx AI - An Artificial Intelligence Framework
Copyright (C) 2004  Kurtis Fields. See BotworxAI_License.txt for details.
*/
#include "stdafx.h"

#include <bwai/AiBlob.h>
#include <bwai/AiReader.h>

#include <bwaxl/AxlFiber_impl.h>
#include <bwaxl/AxlBx.h>
//
#include <bwaxl/AxlRepl.h>
#include <bwaxl/AxlPrinter.h>
#include <bwaxl/AxlXop.h>
#include <bwaxl/AxlXn.h>
#include <bwaxl/AxlCatcher.h>

class AxlXnType ;

DEFINE_BXTYPE(AxlExprRepl) ;
MBINFO_NONE(AxlExprRepl) ;

AxlExprRepl::AxlExprRepl(BwCell* pExpr) : AxlRepl(BX_TYPEOF(AxlExprRepl), 0) {
	p_expr = pExpr ;
	m_nextOp = OP_BXEXEC ; //special because this is a Root Task
	axlSetNextOp(OP_BXEXEC) ;
}
AxlExprRepl::~AxlExprRepl() {
}
void* AxlExprRepl::operator new(size_t size) throw() {
	pushXop(OP_EXIT) ; //at very bottom of bstack.
	k_fiber().p_topBx->m_nextOp = OP_EXIT ; //TODO: ... later
	//return axlPushBx(BX_TYPEOF(AxlExprRepl)) ;
	return AxlBx::operator new(size) ;
}
AxlOpcode AxlExprRepl::exec() {
	switch(m_xdx) {
		case 0 : {
			BwCell* pExpr = p_expr.get() ;
			if(pExpr == SYM_EOF)
				bxEnd() ;
			//else
			setXdx(this, 1) ;
			axlCatch(THINGMETAOF(AxlXn), 2) ; //set exception handler
			jumpEval1(pExpr) ; //don't store nextop in catcher!!!
				 }
		case 1 : {
			BwCell* pResult = axlGetResult() ;
			setXdx(this, 0) ;
			bxEnd() ;
				 }
		case 2 : //exception handler
			AxlXn* pXn = asXn(getBall()) ;
			k_printer().print("EvalTask.catch :  ") ;
			k_printer().printCellLn(pXn) ;
			k_printer().printCellLn(axlGetResult()) ;
			setXdx(this, 0) ;
			//bxAgain() ;
			bxEnd() ;
	}
	bxError() ;
}
/////////////////////////
DEFINE_BXTYPE(AxlTermRepl) ;
MBINFO_NONE(AxlTermRepl) ;

AxlTermRepl::AxlTermRepl() : AxlRepl(BX_TYPEOF(AxlTermRepl), 0) {
	p_reader = new AiReader(std::cin) ;
}
AxlTermRepl::~AxlTermRepl() {
	delete p_reader ;
}
void* AxlTermRepl::operator new(size_t size) throw() {
	//return axlPushBx(BX_TYPEOF(AxlTermRepl)) ;
	return AxlBx::operator new(size) ;
}
AxlOpcode AxlTermRepl::exec() {
	switch(m_xdx) {
		case 0 : {
			k_printer().print("USER > ") ;
			BwCell* pExpr = p_reader->readExpr() ;
			p_expr = pExpr ;
			k_printer().printCellLn(pExpr) ;

			if(pExpr == SYM_EOF) {
				bxEnd() ;
			}
			//else
			setXdx(this, 1) ;
			axlCatch(THINGMETAOF(AxlXn), 2) ;
			jumpEval1(pExpr) ; //don't store nextop in catcher!!!
				 }
		case 1 : {
			BwCell* pResult = axlGetResult() ;
			k_printer().printCellLn(pResult) ;
			setXdx(this, 0) ;
			bxAgain() ;
				 }
		case 2 : //error catcher
			AxlXn* pXn = asXn(getBall()) ;
			k_printer().print("TermTask.catch :  ") ;
			k_printer().printCellLn(pXn) ;
			k_printer().printCellLn(axlGetResult()) ;
			setXdx(this, 0) ;
			bxAgain() ;
	}
	bxError() ;
}
//
DEFINE_BXTYPE(AxlFileRepl) ;
MBINFO_NONE(AxlFileRepl) ;

AxlOpcode AxlFileRepl::exec() {
	switch(m_xdx) {
		case 0 : {
			BwCell* pExpr = p_reader->readExpr() ;
			p_expr = pExpr ;
			if(pExpr == SYM_EOF)
				bxEnd() ;
			//else
			setXdx(this, 1) ;
			axlCatch(THINGMETAOF(AxlXn), 2) ;
			jumpEval1(pExpr) ; //else ... you store nextop in catcher!!!
				 }
		case 1 : {
			BwCell* pResult = axlGetResult() ;
			k_printer().printCellLn(pResult) ;
			setXdx(this, 0) ;
			bxAgain() ;
				 }
		case 2 : //error catcher
			AxlXn *pXn = asXn(getBall()) ;
			k_printer().print("FileTask.catch :  ") ;
			k_printer().printCellLn(pXn) ;
			setXdx(this, 0) ;
			bxAgain() ;
	}
	bxError() ;
}
AxlFileRepl::AxlFileRepl(char *pFileName) : AxlRepl(BX_TYPEOF(AxlFileRepl), 0){
	m_file.open(pFileName, std::ios::in) ;
	p_reader = new AiReader(m_file) ;
}
AxlFileRepl::~AxlFileRepl() {
	delete p_reader ;
}
void* AxlFileRepl::operator new(size_t size) throw() {
	//return axlPushBx(BX_TYPEOF(AxlFileRepl)) ;
	return AxlBx::operator new(size) ;
}
//
DEFINE_BXTYPE(AxlBootBx) ;
MBINFO_NONE(AxlBootBx) ;

AxlBootBx::AxlBootBx() : AxlBx(BX_TYPEOF(AxlBootBx), 0) {
	m_nextOp = OP_BXEXEC ; //special because this Is the Boot Task
	axlSetNextOp(OP_BXEXEC) ;
}

AxlOpcode AxlBootBx::exec() {
	switch(m_xdx) {
		case 0 : 
			//Load lib functions
			new AxlFileRepl("init.axl") ;
			setXdx(this, 1) ;
			callBx() ;
		case 1 :
			new AxlTermRepl() ;
			setXdx(this, 2) ;
			m_nextOp = OP_EXIT ;
			callBx() ;
		case 2 :
			bxEnd() ;
	}
	bxError() ;
}
void* AxlBootBx::operator new(size_t size) throw() {
	pushXop(OP_EXIT) ; //at very bottom of bstack.
	//return axlPushBx(BX_TYPEOF(AxlBootBx)) ;
	return AxlBx::operator new(size) ;
}
//
TYPEINFO_BEGIN(AxlReplKit)
	TYPEINFO("EVALTASK", AxlExprRepl, TT_UNKNOWN, MBF_DEFAULT),
	TYPEINFO("TERMTASK", AxlTermRepl, TT_UNKNOWN, MBF_DEFAULT),
	TYPEINFO("FILETASK", AxlFileRepl, TT_UNKNOWN, MBF_DEFAULT),
	TYPEINFO("BOOTTASK", AxlBootBx, TT_UNKNOWN, MBF_DEFAULT)
TYPEINFO_END
//
//AxlReplKit
//
DEFINE_KITTYPE(AxlReplKit) ;

NO_KITINFO(AxlReplKit) ;

KITINFO("task", AXL_KT_TASK, AxlReplKit) ;
