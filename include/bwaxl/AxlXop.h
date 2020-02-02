#ifndef _AxlXop_h
#define _AxlXop_h

#include "AxlBx.h"
#include "AxlFiber_impl.h"
//
//AxlXopType
//
class AxlXopType : public AxlBxType {
public:
	AxlXopType(AiTypeInfo& pInfo, ThingTT typeId = TT_XOPTYPE)
		: AxlBxType(pInfo, typeId) { //Uses base Bx Meta as starting point
		m_opCode = pInfo.m_thingTT ;
	}
	void* operator new(size_t count) throw() {
		return BW_USERMALLOC(count, TT_XOPTYPE) ;
	}
	virtual void purge() ;
	AxlOpcode m_opCode ;
} ;
#define isXopType(C) (isTT(C, TT_XOPTYPE))
#define asXopType(C) ((AxlXopType*)C)
//
//AxlXopTypeT
//
template <typename C>
class AxlXopTypeT : public AxlXopType {
public:
	AxlXopTypeT(AiTypeInfo& pInfo) : AxlXopType(pInfo) {
	}
	static AiType* instantiate(AiTypeInfo& pInfo) {
		AxlXopTypeT<C>* pType = new AxlXopTypeT<C>(pInfo) ;
		ThingTT s_typeId = TT_NIL ;
		pType->registerSelf(pInfo, s_typeId) ;
		return pType ;
	}
	virtual void* produce(ThingLength length) { 
		//return new C(this, length) ;
		AxlOpcode opCode = m_opCode ;
		return pushXopN(opCode, length) ;
	} ;
	//Data Members
} ; 
#define DEFINE_XOPTYPE(C) class C##Type : public AxlXopTypeT<C> {} ;

//
//AxlXop
//
class AxlXop : public AxlBx {
public:
	AxlXop(AxlXopType *pMeta, ThingLength length) 
		: AxlBx(pMeta, length) {
	}
	//
	AxlOpcode m_opCode ;
} ;
#define isXop(X) (isTT(X, TT_XOP))
#define ofXop(X) (ofTT(X, TT_XOP))
#define asXop(X) ((AxlXop*)X)

class AxlXopKit : public AiKit {
public:
	AxlXopKit(AiKit* pSuperKit, AiKitInfo *pKitInfo) 
		: AiKit(AXL_KT_XOP, pSuperKit, pKitInfo) {
	}
	//
	virtual void buildMetas(AiKitInfo& pKitInfo) ;
	void buildOpMetas() ;
} ;
DECLARE_KITINFO(AxlXopKit) ;

#endif//_AxlXop_h