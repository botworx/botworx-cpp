/*AXL - A Lispish interpreter for Botworx AI - An Artificial Intelligence Framework
Copyright (C) 2004  Kurtis Fields. See BotworxAI_License.txt for details.
*/
#include "stdafx.h"
//
//AiCore Meta
//
DEFINE_ABSTRACT_KITTYPE(AiCore) ;

DEFINE_AIVALUETYPE(BwCell) ;
MBINFO_NONE(BwCell) ;

TYPEINFO_BEGIN(AiCore)
	TYPEINFO("CELL-TYPE", BwCell, TT_CELL, MBF_DEFAULT)
TYPEINFO_END

DECLARE_KITINFO(AiPairKit) ;
DECLARE_KITINFO(AiMultiKit) ;
DECLARE_KITINFO(AiSymbolKit) ;
DECLARE_KITINFO(AiStringKit) ;
DECLARE_KITINFO(AiXStringKit) ;
DECLARE_KITINFO(AiIntKit) ;
DECLARE_KITINFO(AiFloatKit) ;
DECLARE_KITINFO(AiBlobKit) ;
//DECLARE_KITINFO(AiObjectKit) ;
//DECLARE_KITINFO(AiClassKit) ;

KITINFO_BEGIN(AiCore)
	KITINFOREF(AiSymbolKit),
	KITINFOREF(AiStringKit),
	KITINFOREF(AiXStringKit),
	KITINFOREF(AiIntKit),
	KITINFOREF(AiFloatKit),
	//KITINFOREF(AiClassKit),
	KITINFOREF(AiPairKit),
	KITINFOREF(AiMultiKit),
	//KITINFOREF(AiObjectKit),
	KITINFOREF(AiBlobKit)
KITINFO_END

KITINFO("core", KT_CORE, AiCore) ;
