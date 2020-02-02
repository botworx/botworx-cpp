/*Botworx AI - An Artificial Intelligence Framework
Copyright (C) 2004  Kurtis Fields. See BotworxAI_License.txt for details.
*/
#ifndef _AiType_H
#define _AiType_H

#include "AiMeta.h"

//
//AiType
//
class AiType : public AiMeta {
public:
	AiType(AiTypeInfo& pInfo, ThingTT typeId) : AiMeta(pInfo, typeId) {
		m_thingTT = pInfo.m_thingTT ;
		m_thingSize = m_thingASize = pInfo.m_thingASize ;
		m_isBlobType = false ;
	}
	void *operator new(size_t count) throw() {
		return BW_USERMALLOC(count, TT_TYPE) ;
	}
	virtual void purge() ;
	//
	virtual void* produce(ThingLength length) { bwAssert(0) ; return NULL ; }
	//
	void registerSelf(AiTypeInfo& pInfo, ThingTT& typeID) ;
	//Data Members
	ThingTT m_thingTT ; //Type ID of this type.
	ThingSize m_thingSize ;
	ThingSize m_thingASize ;
	bool m_isBlobType ;
} ;
typedef boost::intrusive_ptr<AiType> AiTypePtr ;

#define getThingTT(X)(X->m_thingTT)
#define isType(X) (isTT(X, TT_TYPE))
#define asType(C) ((AiType*)C)
//
//AiTypeT
//
template <typename C>
class AiTypeT : public AiType {
public:
	AiTypeT(AiTypeInfo& pInfo, ThingTT typeId = TT_VALUETYPE) : AiType(pInfo, typeId) {
	}
	static AiType* instantiate(AiTypeInfo& pInfo) {
		AiTypeT<C>* pType = new AiTypeT<C>(pInfo) ;
		pType->registerSelf(pInfo, s_typeId) ;
		return pType ;
	}
	virtual void* produce(ThingLength length) {
		//return new C(this, length) ;
		return new C(this) ;
	} ;
	//Data Members
	static ThingTT s_typeId ;
} ;
//
#define _DEFINE_TYPE(C, B) class C##Type : public B<C> { public: } ; \
	template<> ThingTT B<C>::s_typeId = TT_NIL ; \
	template<> class TypeAccessor<C##Type> { public: static AiType* getPtr() ; } ; \
	AiType* TypeAccessor<C##Type>::getPtr() { return TYPEDIR(C##Type::s_typeId) ; }
//
#define DEFINE_AITYPE(C) _DEFINE_TYPE(C, AiTypeT)
//
//AiValueType
//
class AiValueType : public AiType {
public:
	AiValueType(AiTypeInfo& pInfo, ThingTT typeId = TT_VALUETYPE) : AiType(pInfo, typeId) {
		//TODO: metaBuild ... pass MetaMeta ...?
	}
	void *operator new(size_t count) throw() {
		return BW_USERMALLOC(count, TT_VALUETYPE) ;
	}
	virtual void purge() {
		BW_USERFREE(this, TT_VALUETYPE) ;
	}
	//Data Members
};
#define isValueType(X) (isTT(X, TT_VALUETYPE)) //TODO: ??? or ... this is the only way?
#define asValueType(C) (static_cast<AiValueType*>(C))
//
//AiValueTypeT
//
template <typename C>
class AiValueTypeT : public AiType {
public:
	AiValueTypeT(AiTypeInfo& pInfo, ThingTT typeId = TT_VALUETYPE) : AiType(pInfo, typeId) {
	}
	static AiType* instantiate(AiTypeInfo& pInfo) {
		AiValueTypeT<C>* pType = new AiValueTypeT<C>(pInfo) ;
		pType->registerSelf(pInfo, s_typeId) ;
		return pType ;
	}
	//Data Members
	static ThingTT s_typeId ;
} ;
#define DEFINE_AIVALUETYPE(C) _DEFINE_TYPE(C, AiValueTypeT)
//
//AiKitType
//
class AiKitType : public AiType {
public:
	AiKitType(AiTypeInfo& pInfo, ThingTT typeId = TT_KITTYPE) : AiType(pInfo, typeId){
	}
	virtual AiKit* produce(AiKit*  pSuperKit, AiKitInfo *pKitInfo) { bwAssert(0) ; return NULL ; }
} ;
#define asAiKitType(C) ((AiKitType*)C)
//
//AiKitTypeT
//
template <typename C>
class AiKitTypeT : public AiKitType {
public:
	AiKitTypeT(AiKitInfo& pInfo) : AiKitType(asTypeInfo(pInfo)) {
	}
	static AiType* instantiate(AiTypeInfo& pInfo) {
		return new AiKitTypeT<C>(asKitInfo(pInfo)) ; //TODO:HACK?
	}
	virtual AiKit* produce(AiKit*  pSuperKit, AiKitInfo *pKitInfo) {
		AiKit *pKit = new C(pSuperKit, pKitInfo) ;
		pKit->create() ;
		return pKit ;
	} ;
	//Data Members
	static ThingTT s_typeId ;
} ;
//
#define DEFINE_KITTYPE(C) class C##Type : public AiKitTypeT<C> {} ;
//
//AiAbstractKitTypeT
//
template <typename C>
class AiAbstractKitTypeT : public AiKitType {
public:
	AiAbstractKitTypeT(AiKitInfo& pInfo) : AiKitType(asTypeInfo(pInfo)) {
	}
	static AiType* instantiate(AiTypeInfo& pInfo) {
		return new AiAbstractKitTypeT<C>(asKitInfo(pInfo)) ; //TODO:HACK?
	}
	//Data Members
	static ThingTT s_typeId ;
} ;
//
#define DEFINE_ABSTRACT_KITTYPE(C) class C##Type : public AiAbstractKitTypeT<C> {} ;

#endif //_AiType_H
