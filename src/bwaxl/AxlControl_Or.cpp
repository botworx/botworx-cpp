/*AXL - A Lispish interpreter for Botworx AI - An Artificial Intelligence Framework
Copyright (C) 2004  Kurtis Fields. See BotworxAI_License.txt for details.
*/
#include "stdafx.h"

#include <bwaxl/AxlFiber_impl.h>

#include <bwaxl/AxlControl.h> //TODO: - do need this! fix constructor to use bx!!!
//
//OrBx
//
AxlOpcode OrBx::exec() {
	AiPair* pConds = NULL ;
	BwCell* pCond = NULL ;
	switch(m_xdx) {
		case 0 : {
			pConds = static_cast<AiPair*>(getBxCellAt(0)) ;
			p_conds = pConds ;
			setXdx(this, 1) ; //removeme - unnecessary
				 }
		case 1 : {
			pConds = getConds() ;
			if(isNil(pConds)) {
				axlSetResult(NIL) ;
				bxEnd() ;
			}
			pCond = car(pConds) ;
			setXdx(this, 2) ;
			callEval1(pCond) ;
				 }
		case 2 : {
			BwCell* pResult = axlGetResult() ;
			if(notNil(pResult)) {
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