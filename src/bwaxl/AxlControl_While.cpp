/*AXL - A Lispish interpreter for Botworx AI - An Artificial Intelligence Framework
Copyright (C) 2004  Kurtis Fields. See BotworxAI_License.txt for details.
*/
#include "stdafx.h"

#include <bwaxl/AxlFiber_impl.h>

#include <bwaxl/AxlControl.h> //TODO: - do need this! fix constructor to use bx!!!
//
//WhileBx
//
AxlOpcode WhileBx::exec() {
	BwCell* pTest = NULL ;
	AiPair* pBody = NULL ;
	AiPair* pActions = NULL ;
	BwCell* pAction = NULL ;
	switch(m_xdx) {
		case 0 : {
			pTest = getBxCellAt(0) ;
			p_test = pTest ;
			pBody = asPair(getBxCellAt(1)) ;
			p_body = pBody ;
			p_actions = pBody ;
			setXdx(this, 1) ; //removeme - unnecessary
				 }
		case 1 : {
			pTest = getTest() ;
			setXdx(this, 2) ;
			callEval1(pTest) ;
				 }
		case 2 : {
			BwCell* pResult = axlGetResult() ;
			if(isNil(pResult))
				bxEnd() ;
			//else
			}
		case 3 : {
			pAction = car(getActions()) ;
			setXdx(this, 4) ;
			callEval1(pAction) ;
			}
		case 4 : {
			pActions = pairCdr(getActions()) ;
			if(pActions == NIL) {
				p_actions = p_body ;
				setXdx(this, 1) ;
			}
			else {
				p_actions = pActions ;
				setXdx(this, 3) ;
			}
			bxAgain() ;
				 }
	}
	bxError() ;
}