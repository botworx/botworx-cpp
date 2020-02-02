#ifndef _AxlRepl_h
#define _AxlRepl_h

#include <bwai/AiKit.h>
#include "AxlBx.h"
#include <bwai/AiReader.h>

//
//AxlRepl
//
class AxlRepl : public AxlBx {
public:
	AxlRepl(AxlBxType *pMeta, ThingLength length)
		: AxlBx(pMeta, length), p_expr(NULL) {
	}
	void operator delete(void* _Ptr) throw() { bwAssert(0) ; } //class is on stack!!!
	//Data Members
	BwCellPtr p_expr ;
} ;
//
//AxlBootBx
//
class AxlBootBx : public AxlBx {
public:
	AxlBootBx() ;
	AxlBootBx(AxlBxType *pMeta, ThingLength length) : AxlBx(pMeta, length){	}
	//
	void* operator new(size_t count) throw() ;
	void operator delete(void* _Ptr) throw() { bwAssert(0) ; } //class is on stack!!!
	virtual AxlOpcode exec() ;
} ;
//
//AxlExprRepl
//
class AxlExprRepl : public AxlRepl {
public:
	AxlExprRepl(BwCell* pExpr) ;
	AxlExprRepl(AxlBxType *pMeta, ThingLength length) : AxlRepl(pMeta, length){	}
	~AxlExprRepl() ;
	void* operator new(size_t count) throw() ;
	virtual AxlOpcode exec() ;
	//Data Members
} ;
//
//AxlTermRepl
//
class AxlTermRepl : public AxlRepl {
public:
	AxlTermRepl() ;
	AxlTermRepl(AxlBxType *pMeta, ThingLength length) : AxlRepl(pMeta, length){	}
	~AxlTermRepl() ;
	void* operator new(size_t count) throw() ;
	virtual AxlOpcode exec() ;
	//Data Members
	AiReader *p_reader ;
} ;
//
//AxlFileRepl
//
class AxlFileRepl : public AxlRepl {
public:
	AxlFileRepl(char *pFileName) ;
	AxlFileRepl(AxlBxType *pMeta, ThingLength length) : AxlRepl(pMeta, length){	}
	~AxlFileRepl() ;
	void* operator new(size_t count) throw() ;
	virtual AxlOpcode exec() ;
	//Data Members
	std::ifstream m_file ;
	AiReader *p_reader ;
} ;
//
//AxlReplKit
//
class AxlReplKit : public AiKit {
public:
	AxlReplKit(AiKit* pSuperKit, AiKitInfo *pKitInfo)
		: AiKit(AXL_KT_TASK, pSuperKit, pKitInfo) {
	}
} ;
DECLARE_KITINFO(AxlReplKit) ;

#endif //_AxlRepl_h
