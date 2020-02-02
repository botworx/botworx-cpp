/*AXL - A Lispish interpreter for Botworx AI - An Artificial Intelligence Framework
Copyright (C) 2004  Kurtis Fields. See BotworxAI_License.txt for details.
*/
#include "stdafx.h"

#include <bwaxl/AxlFiber_impl.h>

#include <bwaxl/AxlNumber.h>
#include <bwaxl/AxlXop.h>

//
//
//
typedef AxlXop AxlNumberEqXop ; 
DEFINE_XOPTYPE(AxlNumberEqXop) ;
MBINFO_BEGIN(AxlNumberEqXop)
	MB_FORMALARG("X", MBF_DEFAULT, TT_CELL),
	MB_FORMALARG("Y", MBF_DEFAULT, TT_CELL)
MBINFO_END
//
typedef AxlXop AxlNumberNeqXop ; 
DEFINE_XOPTYPE(AxlNumberNeqXop) ;
MBINFO_BEGIN(AxlNumberNeqXop)
	MB_FORMALARG("X", MBF_DEFAULT, TT_CELL),
	MB_FORMALARG("Y", MBF_DEFAULT, TT_CELL)
MBINFO_END
//
typedef AxlXop AxlNumberPlusXop ; 
DEFINE_XOPTYPE(AxlNumberPlusXop) ;
MBINFO_BEGIN(AxlNumberPlusXop)
	MB_FORMALARG("X", MBF_DEFAULT, TT_CELL),
	MB_FORMALARG("Y", MBF_DEFAULT, TT_CELL)
MBINFO_END
//
typedef AxlXop AxlNumberSubXop ; 
DEFINE_XOPTYPE(AxlNumberSubXop) ;
MBINFO_BEGIN(AxlNumberSubXop)
	MB_FORMALARG("X", MBF_DEFAULT, TT_CELL),
	MB_FORMALARG("Y", MBF_DEFAULT, TT_CELL)
MBINFO_END
//
//AxlNumberKit
//
DEFINE_KITTYPE(AxlNumberKit) ;

TYPEINFO_BEGIN(AxlNumberKit)
	TYPEINFO("=", AxlNumberEqXop, XOP_NUMBER_EQUAL, MBF_DEFAULT),
	TYPEINFO("/=", AxlNumberNeqXop, XOP_NUMBER_NOT_EQUAL, MBF_DEFAULT),
	TYPEINFO("+", AxlNumberPlusXop, XOP_PLUS, MBF_DEFAULT),
	TYPEINFO("-", AxlNumberSubXop, XOP_SUB, MBF_DEFAULT)
TYPEINFO_END

NO_KITINFO(AxlNumberKit) ;

KITINFO("number", KT_NUMBER, AxlNumberKit) ;

