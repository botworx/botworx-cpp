/*Botworx AI - An Artificial Intelligence Framework
Copyright (C) 2004  Kurtis Fields. See BotworxAI_License.txt for details.
*/
#include "stdafx.h"

#include <bwai/AiInt.h>
#include <bwai/AiFloat.h>

#include <bwai/AiMath.h>

float AiMath::getFloat() {
	bwAssert(isNumber(p_this)) ;
	float value = .0 ;
	switch(getTT(p_this)) {
		case TT_INT :
			value = (float)asInt(p_this)->m_value ;
		break ;
		case TT_FLOAT :
			value = asFloat(p_this)->m_value ;
		break ;
	}
	return value ;
}
