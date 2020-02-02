/*Botworx AI - An Artificial Intelligence Framework
Copyright (C) 2004  Kurtis Fields. See BotworxAI_License.txt for details.
*/
#ifndef _AiKit_H
#define _AiKit_H

#include <bwcore/BwKit.h>
#include "AiTypeInfo.h"
//
class AiCore ;

class AiKit : public BwKit {
public:
	AiKit(KitTT typeID, AiKit* pSuperKit, AiKitInfo *pKitInfo) ;
	virtual ~AiKit() ;
	virtual void doPostDisable(bool sleeping = true) ;
	virtual void doCreate(const BwPartInfo& info) ;
	virtual void doConfig() ;
	//
	AiKitInfo& getKitInfo() { return (*p_info) ; }
	AiKitInfo* findExtendingKitInfo(AiKitInfo& pInfo) ;
	void buildKits(AiKitInfo& pInfo) ;

	virtual void buildMetas(AiKitInfo& pKitInfo) ;
	virtual void initMetas(AiTypeInfos pInfo) ;

	void setKitInfo(AiKitInfo *pInfo) { p_info = pInfo ; }
	KitTT getKitTypeID() { return m_kitTypeID ; }
	//Data
	KitTT m_kitTypeID ;
	AiKitInfo *p_info ;
	AiKit*  p_superKit ;
	//
	unsigned int m_size ;
} ;
#define asKit(P) (static_cast<AiKit*>(P))

///////////////
template<typename T_Base, typename T_Part>
class AiHeapKitT : public T_Base {
public:
	AiHeapKitT(KitTT typeID, AiKit* pSuperKit, AiKitInfo *pKitInfo) 
		: T_Base(typeID, pSuperKit, pKitInfo) {
	}
	T_Part* rent() { return BW_MALLOC(sizeof(T_Part)) ; }
	virtual void release(void *pCell) { BW_FREE(pCell) ; }
	//Data Members
};
///////////////
template<typename T_Base, typename T_Part>
class AiPoolKitT : public T_Base {
public:
	typedef boost::pool<> T_Pool ;
public:
	AiPoolKitT(KitTT typeID, AiKit* pSuperKit, AiKitInfo *pKitInfo) 
		: T_Base(typeID, pSuperKit, pKitInfo), m_pool(sizeof(T_Part)) {
		this->m_size = sizeof(T_Part) ;
	}
	T_Part* rent() { 
		return static_cast<T_Part*>(m_pool.malloc()) ; 
	}
	virtual void release(void *pCell) { m_pool.free(pCell) ; }
	//Data Members
	T_Pool m_pool ;
};

#endif //_AiKit_H
