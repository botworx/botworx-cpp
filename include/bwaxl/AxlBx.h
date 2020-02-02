#ifndef _AxlBx_h
#define _AxlBx_h

#include <bwai/AiBlob.h>
#include <bwai/AiKit.h>

class AxlBx ;
class AxlScope ;
//
//AxlBxType
//
class AxlBxType : public AiBlobType {
public:
	AxlBxType(AiTypeInfo& pInfo, ThingTT typeId = TT_BXTYPE)
		: AiBlobType(pInfo, typeId) { //Uses base Bx Meta as starting point
		f_reverseIndexed = true ;
	}
	void* operator new(size_t count) throw() {
		return BW_USERMALLOC(count, TT_BXTYPE) ;
	}
	virtual void purge() ;
} ;
#define asBxType(C) ((AxlBxType*)C)
#define BX_TYPEOF(C) (static_cast<AxlBxType*>(TypeAccessor<C##Type>::getPtr()))
//
//AxlBxTypeT
//
template <typename C>
class AxlBxTypeT : public AxlBxType {
public:
	AxlBxTypeT(AiTypeInfo& pInfo) : AxlBxType(pInfo) {
	}
	static AiType* instantiate(AiTypeInfo& pInfo) {
		AxlBxTypeT<C>* pType = new AxlBxTypeT<C>(pInfo) ;
		pType->registerSelf(pInfo, s_typeId) ;
		return pType ;
	}
	virtual void* produce(ThingLength length) {
		return new C(this, length) ;
	} ;
	//
	static ThingTT s_typeId ;
} ;
#define DEFINE_BXTYPE(C) _DEFINE_TYPE(C, AxlBxTypeT)

//
//AxlBx
//
typedef char AxlXdx ;
class AxlBx : public AiBlob {
public:
	AxlBx(AxlBxType *pType, ThingLength length) : AiBlob(pType, length) {
		m_xdx = 0 ;
		m_nextOp = OP_NIL ;
	}
	void* operator new(size_t size) throw() ;
	void* operator new(size_t size, void *object) throw() { return object; }
	void operator delete(void* _Ptr) throw() { bwAssert(0) ; } //class is on stack!!!
	virtual ~AxlBx() {}
	virtual AxlOpcode exec() { return OP_ERROR ; }
	//Data Members
	AxlXdx m_xdx ; //continue point
	AxlOpcode m_nextOp ;
	//
	void *p_prevStackTop ;
	AxlBx *p_prevBx ; //previous in Bx call chain
} ;
#define isBx(C) (C->m_typeID == TT_BX) //TODO: ... this is an abstract base!
#define ofBx(X) (ofTT(X, TT_BX))
#define asBx(C) ((AxlBx*)C)
#define setXdx(B,I) (asBx(B)->m_xdx = I)
#define getXdx(B) (asBx(B)->m_xdx)
//
//AxlBxKit
//
class AxlBxKit : public AiKit {
public:
	AxlBxKit(AiKit* pSuperKit, AiKitInfo *pKitInfo)
		: AiKit(AXL_KT_BX, pSuperKit, pKitInfo) {
	}
} ;
DECLARE_KITINFO(AxlBxKit) ;


#endif//_AxlBx_h
