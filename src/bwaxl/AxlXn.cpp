/*AXL - A Lispish interpreter for Botworx AI - An Artificial Intelligence Framework
Copyright (C) 2004  Kurtis Fields. See BotworxAI_License.txt for details.
*/
#include "stdafx.h"

#include <bwaxl/AxlFiber_impl.h>
#include <bwaxl/AxlXn.h>

void AxlXn::purge() {
	AxlXn::~AxlXn() ;
	BW_USERFREE(this, TT_XN) ;
}
//
DEFINE_XNTYPE(AxlXn) ;
MBINFO_NONE(AxlXn) ;

DEFINE_XN(AxlUnboundXn) ;
DEFINE_XNTYPE(AxlUnboundXn) ;
MBINFO_BEGIN(AxlUnboundXn)
	MB_DESCINFO("Unbound Symbol!")
MBINFO_END

DEFINE_XN(AxlTooManyArgsXn) ;
DEFINE_XNTYPE(AxlTooManyArgsXn) ;
MBINFO_BEGIN(AxlTooManyArgsXn)
	MB_DESCINFO("Too many arguments!")
MBINFO_END

DEFINE_XN(AxlNotEnoughArgsXn) ;
DEFINE_XNTYPE(AxlNotEnoughArgsXn) ;
MBINFO_BEGIN(AxlNotEnoughArgsXn)
	MB_DESCINFO("Not enough arguments!")
MBINFO_END

DEFINE_XN(AxlBadArgXn) ;
DEFINE_XNTYPE(AxlBadArgXn) ;
MBINFO_BEGIN(AxlBadArgXn)
	MB_DESCINFO("Bad Argument!")
MBINFO_END
//
//AxlXnKit
//
DEFINE_KITTYPE(AxlXnKit) ;

TYPEINFO_BEGIN(AxlXnKit)
	TYPEINFO("XN-TYPE", AxlXn, TT_XN, MBF_DEFAULT),
	TYPEINFO("UNBOUND-XN-TYPE", AxlUnboundXn, XN_UNBOUND, MBF_DEFAULT),
	TYPEINFO("TMARGS-XN-TYPE", AxlTooManyArgsXn, XN_TOO_MANY_ARGS, MBF_DEFAULT),
	TYPEINFO("NEARGS-XN-TYPE", AxlNotEnoughArgsXn, XN_NOT_ENOUGH_ARGS, MBF_DEFAULT),
	TYPEINFO("BADARG-XN-TYPE", AxlBadArgXn, XN_BAD_ARG, MBF_DEFAULT)
TYPEINFO_END

NO_KITINFO(AxlXnKit) ;

KITINFO("xn", AXL_KT_XN, AxlXnKit) ;
