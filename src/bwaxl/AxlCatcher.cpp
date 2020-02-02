/*AXL - A Lispish interpreter for Botworx AI - An Artificial Intelligence Framework
Copyright (C) 2004  Kurtis Fields. See BotworxAI_License.txt for details.
*/
#include "stdafx.h"

#include <bwaxl/AxlCatcher.h>
#include <bwaxl/AxlFiber_impl.h>
//
//AxlCatcher
//

DEFINE_AIVALUETYPE(AxlCatcher) ;

AxlCatcher::AxlCatcher(AiType* pCatchType, AxlXdx catchXdx) 
	: AxlBx(BX_TYPEOF(AxlCatcher), 0) {
	m_nextOp = OP_POPCATCHER ;
	p_catchType = pCatchType ;
	m_catchXdx = catchXdx ;
}

AxlOpcode AxlCatcher::exec() {
	switch(m_xdx) {
		case 0 : {
			printf("AxlCatcher: Why did you execute me? ") ;
				 }
	}
	bxError() ;
}
void* AxlCatcher::operator new(size_t count) throw() {
	return axlPushCatcher(BX_TYPEOF(AxlCatcher)) ;
}
//
MBINFO_NONE(AxlCatcher) ;
//

//
//AxlCatcherKit
//
DEFINE_KITTYPE(AxlCatcherKit) ;

TYPEINFO_BEGIN(AxlCatcherKit)
	TYPEINFO("CATCHER-TYPE", AxlCatcher, BX_CATCHER, MBF_DEFAULT)
TYPEINFO_END

NO_KITINFO(AxlCatcherKit) ;

KITINFO("catcher", AXL_KT_CATCHER, AxlCatcherKit) ;
