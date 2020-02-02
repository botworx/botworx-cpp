/*AXL - A Lispish interpreter for Botworx AI - An Artificial Intelligence Framework
Copyright (C) 2004  Kurtis Fields. See BotworxAI_License.txt for details.
*/
#include "stdafx.h"

#include <bwaxl/AxlFiber_impl.h>

#include <bwaxl/AxlControl.h> //TODO: - do need this! fix constructor to use bx!!!

//
//TagBodyBx
//
AxlOpcode TagBodyBx::exec() {
	AiPair* pForms = NULL ;
	BwCell* pForm = NULL ;
	switch(m_xdx) {
		case 0 : {
			AiPair *pForms = asPair(getBxCellAt(0)) ;
			p_forms = pForms ;
			setXdx(this,1) ; //redundant?
				 }
		case 1 : {
			pForms = getForms() ;
			if(isNil(pForms)) {
				bxEnd() ;
			}
			pForm = car(pForms) ;
			setXdx(this, 2) ;
			callEval1(pForm) ;
				 }
		case 2 : {
			BwCell* pResult = axlGetResult() ;
			pForms = getForms() ;
			p_forms = asPair(cdr(pForms)) ;
			setXdx(this, 1) ;
			bxAgain() ;
				 }
	}
	bxError() ;
}