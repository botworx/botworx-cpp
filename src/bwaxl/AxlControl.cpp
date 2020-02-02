/*AXL - A Lispish interpreter for Botworx AI - An Artificial Intelligence Framework
Copyright (C) 2004  Kurtis Fields. See BotworxAI_License.txt for details.
*/
#include "stdafx.h"

#include <bwaxl/AxlFiber_impl.h>

#include <bwaxl/AxlControl.h> //TODO: - do need this! fix constructor to use bx!!!
//
//CondBx
//
AxlOpcode CondBx::exec() {
	AiPair* pConds = NULL ;
	AiPair* pCond = NULL ;
	BwCell* pTest = NULL ;
	AiPair* pActions = NULL ;

	switch(m_xdx) {
		case 0 : {
			AiPair* pConds = asPair(getBxCellAt(0)) ;
			p_conds = pConds ;
			setXdx(this, 1) ; //removeme - unnecessary
				 }
		case 1 : {
			pConds = getConds() ;
			pCond = asPair(car(pConds)) ;
			pTest = car(pCond) ;
			pActions = asPair(cdr(pCond)) ;
			p_actions = pActions ;
			setXdx(this, 2) ;
			callEval1(pTest) ;
				 }
		case 2 : {
			BwCell* pResult = axlGetResult() ;
			if(notNil(pResult)) {
				pActions = getActions() ;
				setXdx(this, 3) ;
				callEval1(car(pActions)) ; //TODO:we're only handling one action here! See WhileBx for example.
			}
			else {
				pConds = getConds() ;
				if(isNil(pConds))
					bxEnd() ;
				p_conds = asPair(cdr(pConds)) ;
				setXdx(this, 1) ;
				bxAgain() ;
			}
				 }
		case 3 : {
			bxEnd() ;
				 }
	}
	bxError() ;
}