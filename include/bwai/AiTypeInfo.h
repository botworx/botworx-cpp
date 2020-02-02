/*Botworx AI - An Artificial Intelligence Framework
Copyright (C) 2004  Kurtis Fields. See BotworxAI_License.txt for details.
*/
#ifndef _AiTypeInfo_H
#define _AiTypeInfo_H

#include "AiMbInfo.h"

class AiType ;
class AiMeta ;

struct AiTypeInfo ;

typedef AiType*(*AiTypeProducer)(AiTypeInfo &pInfo) ;

struct AiTypeInfo : AiMbInfo {
	AiTypeInfo(const char *pName, ThingTT mbTT, unsigned int flags,  AiMbInfoZs pZ,
		AiTypeInfo* pSuperInfo, AiTypeProducer p, ThingTT thingTT, ThingSize thingASize) : AiMbInfo(pName, mbTT, flags, pZ),
		p_superInfo(pSuperInfo), produce(p), m_thingTT(thingTT), m_thingASize(thingASize)
	{
	}
	//TODO: kludge for axlxopmeta
	AiTypeInfo(const char *pName, ThingTT mbTT,
		ThingTT thingTT, ThingSize thingASize) : AiMbInfo(pName, mbTT, 0, NO_MBINFOZS),
		m_thingTT(thingTT), m_thingASize(thingASize)
	{
	}

	AiTypeInfo* p_superInfo ;
	AiTypeProducer produce ;
	ThingTT m_thingTT ;
	ThingSize m_thingASize ;
} ;
#define asTypeInfo(P) (static_cast<AiTypeInfo&>(P))
typedef std::vector<AiTypeInfo> AiTypeInfos;
//
#define TYPEINFO_BEGIN(C) AiTypeInfos s_##C##_metaInfo {

#define TYPEINFO(N,C,M,F) AiTypeInfo(N, TT_TYPE, F, s_##C##_metabitInfoZ, NULL, &C##Type::instantiate, M, sizeof(C))

// #define TYPEINFO_END ,{ NULL } } ;
#define TYPEINFO_END } ;
#define TYPEINFO_NONE(C) TYPEINFO_BEGIN(C) }

//
//AiKitInfo
//
class AiKitInfo;
typedef std::vector<AiKitInfo> AiKitInfos;
typedef std::vector<AiKitInfo*> AiKitInfoRefs;

struct AiKitInfo : AiTypeInfo {
	AiKitInfo(const char *pName, ThingTT mbTT, unsigned int flags,  AiMbInfoZs pZ,
		AiTypeInfo* pSuperInfo, AiTypeProducer p, ThingTT thingTT, ThingSize thingASize, AiKitInfoRefs pKitRefs, AiTypeInfos pMetaInfoZ) :
		AiTypeInfo(pName, mbTT, flags, pZ, pSuperInfo, p, thingTT, thingASize),
		p_kitRefs(pKitRefs), p_metaInfoZ(pMetaInfoZ)
	{
	}

	AiKitInfoRefs p_kitRefs ;
	AiTypeInfos p_metaInfoZ ;
} ;
#define asKitInfo(M) (static_cast<AiKitInfo&>(M))

#define KITINFO(N,M,C) AiKitInfo s_##C##_kitInfo = AiKitInfo(N, TT_KITTYPE, MBF_DEFAULT, NO_MBINFOZS, NULL, &C##Type::instantiate, asThingTT(M), (sizeof(C)), s_##C##_kitInfoRefs, s_##C##_metaInfo)
#define KITINFO_EX(N,M,C,S) AiKitInfo s_##C##_kitInfo = { N, TT_KITTYPE, MBF_DEFAULT, NO_MBINFOZS, &asTypeInfo(s_##S##_kitInfo), &C##Type::instantiate, asThingTT(M), (sizeof(C)), s_##C##_kitInfoRefs, s_##C##_metaInfo}

#define DECLARE_KITINFO(C) extern AiKitInfo s_##C##_kitInfo
//
#define KITINFO_BEGIN(C) AiKitInfoRefs s_##C##_kitInfoRefs = {
#define KITINFOREF(C) &s_##C##_kitInfo
#define KITINFO_END } ;
#define NO_KITINFO(C) KITINFO_BEGIN(C) }

#endif //_AiTypeInfo_H