/*Botworx AI - An Artificial Intelligence Framework
Copyright (C) 2004  Kurtis Fields. See BotworxAI_License.txt for details.
*/
#ifndef _MiaBinderOps_H
#define _MiaBinderOps_H

#include "MiaMethod.h"

inline MiaMethod& getMethod(MiaBinder& binder) { return *binder.p_method ; }
inline MiaMind& getMind(MiaBinder& binder) { return *binder.p_method->p_mind ; }
inline MiaRule& getRule(MiaBinder& binder) { return binder.p_method->m_rule ; }
inline void setSelectSpace(MiaBinder& binder, MiaSpace* pSpace) { binder.p_method->p_selectSpace = pSpace ; }
inline MiaSpace& getSelectSpace(MiaBinder& binder) { return *binder.p_method->p_selectSpace ; }
//
inline void setVal(MiaBinder& binder, AiSymbol* pSymbol, BwCell* pVal) {
	switch(pSymbol->getSymType()) {
		case SYMTYP_LOGIC :
			binder.setVal(pSymbol, pVal) ;
			break ;
		case SYMTYP_NORMAL :
			SetGlobalVal(pSymbol, pVal) ;
			break ;
		case SYMTYP_PROPERTY :
			bwAssert(0) ; //TODO:implement?
			break ;
	}
}
inline BwCell* getVal(MiaBinder& binder, AiSymbol* pSymbol) {
	BwCell* pVal = NULL ;
	switch(pSymbol->getSymType()) {
		case SYMTYP_LOGIC :
			pVal = binder.getVal(pSymbol) ;
			break ;
		case SYMTYP_NORMAL :
			pVal = GetGlobalVal(pSymbol) ;
			if(pVal == UNBOUND)
				pVal = new MiaIdentifier(pSymbol) ; //not excited about this yet ...
			break ;
		case SYMTYP_PROPERTY :
			pVal = getMethod(binder).getPropertyVal(pSymbol) ;
			break ;
	}
	return pVal ;
}

#endif //_MiaBinderOps_H
