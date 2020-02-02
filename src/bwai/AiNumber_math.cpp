/*Botworx AI - An Artificial Intelligence Framework
Copyright (C) 2004  Kurtis Fields. See BotworxAI_License.txt for details.
*/
#include "stdafx.h"

#include <bwai/AiInt.h>
#include <bwai/AiFloat.h>


bool AiNumber_zerop(AiNumber *pThis) {
	ThingTT numTT = getNumberTT(getTT(pThis)) ;
	bool truth = false ;
	switch(numTT) {
		case TT_INT :
			truth = asInt(pThis)->m_value == 0 ;
			break ;
		case TT_FLOAT :
			truth = asFloat(pThis)->m_value == 0.0 ;
			break ;
	}
	return truth ;
}
AiNumber* AiNumber_sub1(AiNumber *pThis) {
	ThingTT numTT = getNumberTT(getTT(pThis)) ;
	AiNumber *pNumber = NULL ;
	switch(numTT) {
		case TT_INT :
			pNumber = new AiInt(asInt(pThis)->m_value -1) ;
			break ;
		case TT_FLOAT :
			pNumber = new AiFloat(asFloat(pThis)->m_value -1) ;
			break ;
	}
	return pNumber ;
}
AiNumber* AiInt_sub(AiInt *pThis, AiNumber *pThat) {
	ThingTT thatNumTT = getNumberTT(getTT(pThat)) ;
	AiNumber *pNumber = NULL ;
	switch(thatNumTT) {
		case TT_INT : {
			int value = pThis->m_value - asInt(pThat)->m_value ;
			pNumber = new AiInt(value) ;
		} break ;

		case TT_FLOAT : {
			float value = pThis->m_value - asFloat(pThat)->m_value ;
			pNumber = new AiFloat(value) ;
		} break ;
	}
	return pNumber ;
}
AiNumber* AiFloat_sub(AiFloat *pThis, AiNumber *pThat) {
	ThingTT thatNumTT = getNumberTT(getTT(pThat)) ;
	AiNumber *pNumber = NULL ;
	switch(thatNumTT) {
		case TT_INT : {
			float value = pThis->m_value - asInt(pThat)->m_value ;
			pNumber = new AiFloat(value) ;
		} break ;
		case TT_FLOAT : {
			float value = pThis->m_value - asFloat(pThat)->m_value ;
			pNumber = new AiFloat(value) ;
		} break ;
	}
	return pNumber ;
}
AiNumber* AiNumber_sub(AiNumber *pThis, AiNumber *pThat) {
	ThingTT thisNumTT = getNumberTT(getTT(pThis)) ;
	AiNumber *pNumber = NULL ;
	switch(thisNumTT) {
		case TT_INT :
			pNumber = asNumber(AiInt_sub(asInt(pThis), pThat)) ;
			break ;
		case TT_FLOAT :
			pNumber = asNumber(AiFloat_sub(asFloat(pThis), pThat)) ;
			break ;
	}
	return pNumber ;
}
AiNumber* AiInt_add(AiInt *pThis, AiNumber *pThat) {
	ThingTT thatNumTT = getNumberTT(getTT(pThat)) ;
	AiNumber *pNumber = NULL ;
	switch(thatNumTT) {
		case TT_INT : {
			int value = pThis->m_value + asInt(pThat)->m_value ;
			pNumber = new AiInt(value) ;
		} break ;

		case TT_FLOAT : {
			float value = pThis->m_value + asFloat(pThat)->m_value ;
			pNumber = new AiFloat(value) ;
		} break ;
	}
	return pNumber ;
}
AiNumber* AiFloat_add(AiFloat *pThis, AiNumber *pThat) {
	ThingTT thatNumTT = getNumberTT(getTT(pThat)) ;
	AiNumber *pNumber = NULL ;
	switch(thatNumTT) {
		case TT_INT : {
			float value = pThis->m_value + asInt(pThat)->m_value ;
			pNumber = new AiFloat(value) ;
		} break ;
		case TT_FLOAT : {
			float value = pThis->m_value + asFloat(pThat)->m_value ;
			pNumber = new AiFloat(value) ;
		} break ;
	}
	return pNumber ;
}
AiNumber* AiNumber_add(AiNumber *pThis, AiNumber *pThat) {
	ThingTT thisNumTT = getNumberTT(getTT(pThis)) ;
	AiNumber *pNumber = NULL ;
	switch(thisNumTT) {
		case TT_INT :
			pNumber = asNumber(AiInt_add(asInt(pThis), pThat)) ;
			break ;
		case TT_FLOAT :
			pNumber = asNumber(AiFloat_add(asFloat(pThis), pThat)) ;
			break ;
	}
	return pNumber ;
}