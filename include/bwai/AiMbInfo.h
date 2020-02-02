/*Botworx AI - An Artificial Intelligence Framework
Copyright (C) 2004  Kurtis Fields. See BotworxAI_License.txt for details.
*/
#ifndef _AiMbInfo_H
#define _AiMbInfo_H

#include "AiMeta_meta.h"
#include <variant>

enum AiMbFlag_E {
	MBF_DEFAULT = 0,
	MBF_DYNAMIC = 1, //MbInfo is either on the stack or in the heap.
	MBF_EXTENDED = 2, //represents an extended type that is not in the meta directory.
	MBF_INDEXED = 4, //represents an extended type that is in the meta directory.
	MBF_LEXICAL = 8, //put in current namespace, not global
	MBF_SUPPRESSED = 16 //Suppressed evaluation
};
enum AiMbFlagNdx_E {
	MBF_DYNAMIC_FLAG = 0,
	MBF_EXTENDED_FLAG,
	MBF_INDEXED_FLAG,
	MBF_LEXICAL_FLAG,
	MBF_SUPPRESSED_FLAG
} ;
// union AiMbInfoZ ;
struct AiSlotInfo;
struct AiElInfo;
struct AiDescInfo;
typedef std::variant<AiSlotInfo, AiElInfo, AiDescInfo> AiMbInfoZ;
typedef std::vector<AiMbInfoZ> AiMbInfoZs;
#define NO_MBINFOZS (AiMbInfoZs())

//
//AiMbInfo
//
struct AiMbInfo {
	AiMbInfo(const char *pName, ThingTT tt, unsigned int flags,  AiMbInfoZs pZ) :
		p_name(pName), m_mbTT(tt), m_flags(flags), p_metabitInfoZ(pZ) {
	}
	const char *p_name ;
	ThingTT m_mbTT ;
	unsigned int m_flags ;
	AiMbInfoZs p_metabitInfoZ ; //sub info
} ;
#define asMbInfo(C) ((AiMbInfo&)C)
//
#define setMbitz(M, V) (((AiMbInfo&)M).p_metabitInfoZ = V)
#define getMbitz(M) (((AiMbInfo&)M).p_metabitInfoZ)
#define getMbString(M) ((char*)(((AiMbInfo&)M).p_name) )
#define setMbSymbol(M, V) (M.p_name = V)
#define getMbSymbol(M) ((AiSymbol*)(M.p_name) )
#define setMbFlag(M,F) (M.m_flags |= ( 1 << F))
#define getMbFlag(M,F) (M.m_flags & ( 1 << F))
//
#define isDynamicMb(M)	(getMbFlag(M,MBF_DYNAMIC_FLAG))
#define isStaticMb(M)	(!getMbFlag(M,MBF_DYNAMIC_FLAG))
#define isExtendedMb(M) (getMbFlag(M,MBF_EXTENDED_FLAG))
#define isIntegralMb(M) (!getMbFlag(M,MBF_EXTENDED_FLAG))
#define isIndexedMb(M) (getMbFlag(M,MBF_INDEXED_FLAG))
#define isGlobalMb(M) (!getMbFlag(M,MBF_LEXICAL_FLAG))
#define isLexicalMb(M) (getMbFlag(M,MBF_LEXICAL_FLAG))
#define isSuppressedMb(M) (getMbFlag(M,MBF_SUPPRESSED_FLAG))
//
//AiElInfo
//
struct AiElInfo : AiMbInfo {
	AiElInfo(const char *pName, ThingTT mbTT, unsigned int flags,  AiMbInfoZs pZ,
		ThingTT bElTT) : AiMbInfo(pName, mbTT, flags, pZ),
		m_bElTT(bElTT)
	{
	}

	ThingTT m_bElTT ; //meta for element
} ;
#define asElInfo(C) ((AiElInfo*)C)
//
//AiDescInfo
//
struct AiDescInfo : AiMbInfo {
	AiDescInfo(const char *pName, ThingTT mbTT, unsigned int flags,  AiMbInfoZs pZ) : AiMbInfo(pName, mbTT, flags, pZ)
	{
	}

	//name is description!
} ;
#define asDescInfo(C) ((AiDescInfo*)C)

//
//AiSlotInfo
//
struct AiSlotInfo : AiMbInfo {
	AiSlotInfo(const char *pName, ThingTT mbTT, unsigned int flags,  AiMbInfoZs pZ,
		ThingTT elTT, ThingSize elPos) : AiMbInfo(pName, mbTT, flags, pZ),
		m_elTT(elTT), m_elPos(elPos)
	{
	}

	ThingTT m_elTT ; //meta for element
	ThingSize m_elPos ; //offset into parent structure
} ;
#define asSlotInfo(C) ((AiSlotInfo&)C)

//
//AiMbInfoZ
//
/*
union AiMbInfoZ {
	//AiMbInfoZ(AiSlotInfo)
	struct AiSlotInfo m_slotInfo ;
	struct AiElInfo m_elInfo ;
	struct AiDescInfo m_descInfo ;
} ;
*/
typedef std::variant<AiSlotInfo, AiElInfo, AiDescInfo> AiMbInfoZ;

#define asMbInfoZ(C) ((AiMbInfoZ&)C)
//
#define MBINFO_BEGIN(C) AiMbInfoZs s_##C##_metabitInfoZ {
#define MBINFO_END } ;
#define MBINFO_NONE(C) MBINFO_BEGIN(C) }

#define DECLARE_MBINFO(C) extern AiMbInfoZs s_##C##_metabitInfoZ

#define MB_FORMALARG(N,F,E) AiSlotInfo(N, TT_FORMALARG, F, NO_MBINFOZS, E, 0)
#define MB_RESTARG(N,F) AiSlotInfo(N, TT_RESTARG, F, NO_MBINFOZS, TT_PAIR, 0)
#define MB_DESCINFO(S) AiDescInfo(S, TT_DESC, MBF_DEFAULT, NO_MBINFOZS)

#endif //_AiMbInfo_H