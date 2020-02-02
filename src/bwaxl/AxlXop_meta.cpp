/*AXL - A Lispish interpreter for Botworx AI - An Artificial Intelligence Framework
Copyright (C) 2004  Kurtis Fields. See BotworxAI_License.txt for details.
*/
#include "stdafx.h"

#include <bwaxl/AxlFiber_impl.h>

#include <bwaxl/AxlXop.h>

void AxlBxType::purge() {
	AxlBxType::~AxlBxType() ;
	BW_USERFREE(this, TT_BXTYPE) ;
}
void AxlXopType::purge() {
	AxlXopType::~AxlXopType() ;
	BW_USERFREE(this, TT_XOPTYPE) ;
}
//
//AxlXopKit
void AxlXopKit::buildMetas(AiKitInfo& pKitInfo) {
	AiKit::buildMetas(pKitInfo) ;
	buildOpMetas() ;
}
void AxlXopKit::buildOpMetas() {
	AxlXopType *pMeta ;
	//TODO: - kludge?
	for(int i = TT_OP+1 ; i < TT_OP_UNKNOWN ; ++i) {
	    const size_t bufferSize = 32;
		char buffer[bufferSize] ;
		strcpy(buffer, "XOP_") ;
		char buffer2[bufferSize] ;
		//_itoa(i, buffer2, 10) ;
		//snprintf(buffer2, bufferSize, "%d", i);
		bwItoa(i, buffer2, bufferSize, 10);
		strcat(buffer, buffer2) ;

		AiTypeInfo info(buffer, TT_XOPTYPE, static_cast<ThingTT>(i), sizeof(AxlXop)) ;
		/*
		asMbInfo(&info)->m_mbTT = TT_XOPTYPE ;
		asMbInfo(&info)->p_name = buffer ;
		asMbInfo(&info)->p_metabitInfoZ = NULL ;
		asTypeInfo(&info)->m_thingTT = static_cast<ThingTT>(i) ;
		asTypeInfo(&info)->m_thingASize = sizeof(AxlXop) ;
		*/
		pMeta = new AxlXopType(asTypeInfo(info)) ;
		TYPEDIR(i) = pMeta ;
	}
}

DEFINE_AIVALUETYPE(AxlXopType) ;
MBINFO_NONE(AxlXopType) ;
//
//AxlXopKit
//
DEFINE_KITTYPE(AxlXopKit) ;

TYPEINFO_BEGIN(AxlXopKit)
	TYPEINFO("XOP-TYPE", AxlXopType, TT_XOPTYPE, MBF_DEFAULT)
TYPEINFO_END

NO_KITINFO(AxlXopKit) ;

KITINFO("xop", AXL_KT_XOP, AxlXopKit) ;
