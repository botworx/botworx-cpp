/*AXL - A Lispish interpreter for Botworx AI - An Artificial Intelligence Framework
Copyright (C) 2004  Kurtis Fields. See BotworxAI_License.txt for details.
*/
#include "stdafx.h"

#include <bwaxl/AxlControl.h> //TODO: - do need this! fix constructor to use bx!!!

//
//CondBx
//
DEFINE_BXTYPE(CondBx) ;

MBINFO_BEGIN(CondBx)
	MB_RESTARG("*FORMS*", MBF_SUPPRESSED)
MBINFO_END
//
//WhileBx
//
DEFINE_BXTYPE(WhileBx) ;

MBINFO_BEGIN(WhileBx)
	MB_FORMALARG("CONDITION", MBF_SUPPRESSED, TT_CELL),
	MB_RESTARG("*FORMS*", MBF_SUPPRESSED)
MBINFO_END
//
//AndBx
//
DEFINE_BXTYPE(AndBx) ;

MBINFO_BEGIN(AndBx)
	MB_RESTARG("*FORMS*", MBF_SUPPRESSED)
MBINFO_END
//
//OrBx
//
DEFINE_BXTYPE(OrBx) ;

MBINFO_BEGIN(OrBx)
	MB_RESTARG("*FORMS*", MBF_SUPPRESSED)
MBINFO_END
//
//TagBodyBx
//
DEFINE_BXTYPE(TagBodyBx) ;

MBINFO_BEGIN(TagBodyBx)
	MB_RESTARG("*FORMS*", MBF_SUPPRESSED)
MBINFO_END
//
//AxlControlKit
//
DEFINE_KITTYPE(AxlControlKit) ;

TYPEINFO_BEGIN(AxlControlKit)
	TYPEINFO("COND", CondBx, BX_COND, MBF_DEFAULT),
	TYPEINFO("AND", AndBx, BX_AND, MBF_DEFAULT),
	TYPEINFO("OR", OrBx, BX_OR, MBF_DEFAULT),
	TYPEINFO("TAGBODY", TagBodyBx, BX_TAGBODY, MBF_DEFAULT),
	TYPEINFO("WHILE", WhileBx, TT_BX, MBF_EXTENDED)
TYPEINFO_END

NO_KITINFO(AxlControlKit) ;

KITINFO("control", AXL_KT_CONTROL, AxlControlKit) ;