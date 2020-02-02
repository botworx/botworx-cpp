/*AXL - A Lispish interpreter for Botworx AI - An Artificial Intelligence Framework
Copyright (C) 2004  Kurtis Fields. See BotworxAI_License.txt for details.
*/
#include "stdafx.h"

#include <bwaxl/AxlFiber_impl.h>

#include <bwaxl/AxlControl.h>
//
//AndBx
//
AxlOpcode AndBx::exec() {
	AiPair* pConds = NULL ;
	BwCell* pCond = NULL ;
	switch(m_xdx) {
		case 0 : {
			AiPair *pConds = asPair(getBxCellAt(0)) ;
			p_conds = pConds ;
			setXdx(this, 1) ; //removeme - unnecessary
				 }
		case 1 : {
			pConds = getConds() ;
			if(isNil(pConds)) {
				axlSetResult(SYM_TRUE) ;
				bxEnd() ;
			}
			pCond = car(pConds) ;
			setXdx(this, 2) ;
			callEval1(pCond) ;
				 }
		case 2 : {
			BwCell* pResult = axlGetResult() ;
			if(isNil(pResult)) {
				bxEnd() ;
			}
			else {
				pConds = getConds() ;
				p_conds = asPair(cdr(pConds)) ;
				setXdx(this, 1) ;
				bxAgain() ;
			}
				 }
	}
	bxError() ;
}