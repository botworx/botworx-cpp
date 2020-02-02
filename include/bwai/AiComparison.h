/*Botworx AI - An Artificial Intelligence Framework
Copyright (C) 2004  Kurtis Fields. See BotworxAI_License.txt for details.
*/
#ifndef _AiComparison_H
#define _AiComparison_H

class AiComparison {
public:
	AiComparison(BwCell* pThis, BwCell* pThat) : p_this(pThis), p_that(pThat) {}
	enum result_E {
		RESULT_NONE = 0,
		RESULT_EQ,
		RESULT_NE,
		RESULT_LT,
		RESULT_LE,
		RESULT_GT,
		RESULT_GE
	} ;
	typedef result_E result ;
	result getResult() { return m_result ; }
	//
	bool eq() ;
	bool ne() ;
	bool lt() ;
	bool le() ;
	bool gt() ;
	bool ge() ;
private:
	void compare() ;
	//Data
	BwCell* p_this ;
	BwCell* p_that ;
	result m_result ;
} ;

#endif //_AiComparison_H
