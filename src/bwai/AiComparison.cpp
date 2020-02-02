/*Botworx AI - An Artificial Intelligence Framework
Copyright (C) 2004  Kurtis Fields. See BotworxAI_License.txt for details.
*/
#include "stdafx.h"

#include <bwai/AiNumber.h>

#include <bwai/AiComparison.h>
//
//AiComparison
//
void AiComparison::compare() {
	int r = 0 ;
	if(isNumber(p_this) && isNumber(p_that))
		r = AiNumber_compare(static_cast<AiNumber*>(p_this), static_cast<AiNumber*>(p_that)) ;
	else
	if(p_this != p_that)
		r = -1 ;
	switch(r) {
		case -1 :
			m_result = RESULT_LT ;
			break ;
		case 0 :
			m_result = RESULT_EQ ;
			break ;
		case 1 :
			m_result = RESULT_GT ;
			break ;
	}
}
bool AiComparison::eq() {
	compare() ;
	if(m_result == RESULT_EQ)
		return true ;
	else
		return false ;
}
bool AiComparison::ne() {
	return !eq() ;
}
bool AiComparison::lt() {
	compare() ;
	if(m_result == RESULT_LT)
		return true ;
	else
		return false ;
}
bool AiComparison::le() {
	compare() ;
	if( (m_result == RESULT_LT) || (m_result == RESULT_EQ) )
		return true ;
	else
		return false ;
}
bool AiComparison::gt() {
	compare() ;
	if(m_result == RESULT_GT)
		return true ;
	else
		return false ;
}
bool AiComparison::ge() {
	compare() ;
	if( (m_result == RESULT_GT) || (m_result == RESULT_EQ) )
		return true ;
	else
		return false ;
}
