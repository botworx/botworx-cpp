/*Botworx AI - An Artificial Intelligence Framework
Copyright (C) 2004  Kurtis Fields. See BotworxAI_License.txt for details.
*/
#ifndef _AiMath_H
#define _AiMath_H

class AiMath {
public:
	AiMath(BwCell* pThis, BwCell* pThat = NULL) : p_this(pThis), p_that(pThat) {}
	float getFloat() ;
	//
	enum result_E {
		RESULT_NONE = 0
	} ;
	typedef result_E result ;
	result getResult() { return m_result ; }
	//
private:
	//Data
	BwCell* p_this ;
	BwCell* p_that ;
	result m_result ;
} ;

#endif //_AiMath_H
