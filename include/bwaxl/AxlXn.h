#ifndef _AxlXn_h
#define _AxlXn_h

#include <bwai/AiKit.h>

//
//AxlXnType
//
class AxlXnTypeBase : public AiValueType {
public:
	AxlXnTypeBase(AiTypeInfo& pInfo)
		: AiValueType(pInfo) { //Uses base Bx Meta as starting point
	}
} ;
#define asXnType(C) ((AxlXnTypeBase*)C)
#define XN_TYPEOF(C) (static_cast<AxlXnTypeBase*>(TypeAccessor<C##Type>::getPtr()))
//
//AxlXnTypeT
//
template <typename C>
class AxlXnTypeT : public AxlXnTypeBase {
public:
	AxlXnTypeT(AiTypeInfo& pInfo) : AxlXnTypeBase(pInfo) {
	}
	static AiType* instantiate(AiTypeInfo& pInfo) {
		AxlXnTypeT<C>* pType = new AxlXnTypeT<C>(pInfo) ;
		pType->registerSelf(pInfo, s_typeId) ;
		return pType ;
	}
	virtual void* produce(ThingLength length) { 
		return new C(this) ;
	} ;
	//Data Members
	static ThingTT s_typeId ;
} ; 
#define DEFINE_XNTYPE(C) _DEFINE_TYPE(C, AxlXnTypeT)

//TODO:we're leaking these!!!
class AxlXn : public BwCell {
public:
	AxlXn(AiType* pXnMeta) : BwCell(TT_XN) {
		p_xnMeta = pXnMeta ;
	}
	void* operator new(size_t count) {
		return BW_USERMALLOC(count, TT_XN) ;
	}
	void operator delete(void* object) {
		BW_USERFREE(object, TT_XN) ;
	}
	virtual void purge() ;
	AiType* p_xnMeta ;
} ;
#define DEFINE_XN(C) class C : public AxlXn { public: \
	C(AiType* pXnMeta) : AxlXn(pXnMeta) {} } \

#define isXn(C) (C->m_typeID == TT_XN)
#define ofXn(X) (ofTT(X, TT_XN))
#define asXn(C) ((AxlXn*)C)
#define getXnMeta(X) (X->p_xnMeta)

class AxlXnKit : public AiKit {
public:
	AxlXnKit(AiKit* pSuperKit, AiKitInfo *pKitInfo) 
		: AiKit(AXL_KT_XN, pSuperKit, pKitInfo) {
	}
} ;
DECLARE_KITINFO(AxlXnKit) ;

#endif//_AxlXn_h
