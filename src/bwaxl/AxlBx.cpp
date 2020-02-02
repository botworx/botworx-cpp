/*AXL - A Lispish interpreter for Botworx AI - An Artificial Intelligence Framework
Copyright (C) 2004  Kurtis Fields. See BotworxAI_License.txt for details.
*/
#include "stdafx.h"

#include <bwaxl/AxlFiber_impl.h>
#include <bwaxl/AxlBx.h>

//
//AxlBx
//
MBINFO_NONE(AxlBx) ;

void* AxlBx::operator new(size_t size) throw() {
	return axlPushBx(size) ;
}
//
//AxlBxType
//
DEFINE_AIVALUETYPE(AxlBxType) ;
MBINFO_NONE(AxlBxType) ;
//
//AxlBxKit
//
DEFINE_KITTYPE(AxlBxKit) ;

TYPEINFO_BEGIN(AxlBxKit)
	TYPEINFO("BX-TYPE", AxlBxType, TT_BXTYPE, MBF_DEFAULT)
TYPEINFO_END

NO_KITINFO(AxlBxKit) ;

KITINFO("bx", AXL_KT_BX, AxlBxKit) ;

