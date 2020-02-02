/*Botworx AI - An Artificial Intelligence Framework
Copyright (C) 2004  Kurtis Fields. See BotworxAI_License.txt for details.
*/
#ifndef _MiaAsserterBase_H
#define _MiaAsserterBase_H

#include "MiaEval.h"

class MiaBinder ;
class MiaFactoid ;
//
//MiaAsserterBase
//
class MiaAsserterBase : public MiaEval {
public:
	MiaAsserterBase(MiaBinder& binder, MiaFactoid& result) 
		: MiaEval(binder), p_result(&result) {
	}
	MiaFactoid* getResult() { return p_result ; }
	MiaFactoid& result() { return *p_result ; }
	//Data Members
private:
	MiaFactoid* p_result ;
} ;

#endif //_MiaAsserterBase_H
