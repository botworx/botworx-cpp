/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _BwFactory_H
#define _BwFactory_H

#include "BwKit.h"


class BwFactory ;
template<>
struct BwSigT<BwFactory> : BwSigT<BwPart> {
	typedef BwKit	T_Owner ;
	//
	static bwString name() { return "Factory" ; }
} ;

class BwFactory : public BwPart {
public:
	BwFactory(BwPart* pOwner, BwKit *pKit = nullptr) ;
	int getSerialCounter() { return m_serialCounter ; }
	int incSerialCounter() { return m_serialCounter += 1 ; }
	virtual void* rent(size_t size) ;
	virtual void release(void *pCell) ;
	//
	BwKit* getKit() { return p_kit ; }
	//Data Members
protected:
	BwKit *p_kit ;
	int m_serialCounter ;
public:
} ;
///////////
template<typename T_Class, typename T_Base = BwFactory>
class BwFactoryT : public T_Base {
public:
	typedef BwSigT<T_Class>			T_Sig ;
	typedef typename T_Sig::T_Kit	T_Kit ;
	typedef typename T_Sig::T_Owner	T_Owner ;
public:
	BwFactoryT(BwPart* pOwner, BwKit *pKit = nullptr) : T_Base(pOwner, pKit) {
	}
	//Data Members
public:
};

///////
template<typename T>
	inline T* create_part(T* part, bwPartStyle style = PS_DEFAULT) {
		part->create(style) ;
		return part ;
	}
template<typename T>
	inline void destroyPart(T *pPart) {
		if(pPart == nullptr)
			return ;
		if(pPart->isOperational())
			pPart->disable(false) ;
		BwFactory *pFactory = pPart->getFactory() ;
		if(pFactory != nullptr) {
			pPart->~T() ;
			pFactory->release(pPart) ;
		}
		else {
			//bwAssert( _CrtIsValidHeapPointer( pPart ) ); //incompatible with _aligned_malloc???
			delete pPart ;
		}
	}

#endif //_BwFactory_H
