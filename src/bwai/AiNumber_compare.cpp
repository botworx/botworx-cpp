/*Botworx AI - An Artificial Intelligence Framework
Copyright (C) 2004  Kurtis Fields. See BotworxAI_License.txt for details.
*/
#include "stdafx.h"

#include <bwai/AiInt.h>
#include <bwai/AiFloat.h>

int AiInt_compare(AiInt *pThis, AiNumber *pThat) {
	ThingTT thatNumTT = getNumberTT(getTT(pThat)) ;
	switch(thatNumTT) {
		case TT_INT : {
			if(pThis->m_value == asInt(pThat)->m_value)
				return 0 ;
			else if(pThis->m_value > asInt(pThat)->m_value)
				return 1 ;
		} break ;
		case TT_FLOAT : {
			if(pThis->m_value == asFloat(pThat)->m_value)
				return 0 ;
			else if(pThis->m_value > asFloat(pThat)->m_value)
				return 1 ;
		} break ;
		default :
			bwAssert(0) ;
	}
	return -1 ;
}
int AiFloat_compare(AiFloat *pThis, AiNumber *pThat) {
	ThingTT thatNumTT = getNumberTT(getTT(pThat)) ;
	AiNumber *pNumber = NULL ;
	switch(thatNumTT) {
		case TT_INT : {
			if(pThis->m_value == asInt(pThat)->m_value)
				return 0 ;
			else if(pThis->m_value > asInt(pThat)->m_value)
				return 1 ;
		} break ;
		case TT_FLOAT : {
			if(pThis->m_value == asFloat(pThat)->m_value)
				return 0 ;
			else if(pThis->m_value > asFloat(pThat)->m_value)
				return 1 ;
		} break ;
		default :
			bwAssert(0) ;
	}
	return -1 ;
}
int AiNumber_compare(AiNumber *pThis, AiNumber *pThat) {
	ThingTT thisNumTT = getNumberTT(getTT(pThis)) ;
	switch(thisNumTT) {
		case TT_INT :
			return AiInt_compare(asInt(pThis), pThat) ;
			break ;
		case TT_FLOAT :
			return AiFloat_compare(asFloat(pThis), pThat) ;
			break ;
		default :
			bwAssert(0) ;
	}
	return -1 ; //keep the compiler happy.
}
BwCell* AiNumber_equal(AiNumber *pThis, AiNumber *pThat) {
	if(AiNumber_compare(pThis, pThat) == 0)
		return SYM_TRUE ;
	else
		return NIL ;
}
BwCell* AiNumber_notEqual(AiNumber *pThis, AiNumber *pThat) {
	if(AiNumber_compare(pThis, pThat) == 0)
		return NIL ;
	else
		return SYM_TRUE ;
}
