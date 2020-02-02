/*Botworx AI - An Artificial Intelligence Framework
Copyright (C) 2004  Kurtis Fields. See BotworxAI_License.txt for details.
*/
#ifndef _MiaMatcherBase_H
#define _MiaMatcherBase_H

#include "MiaEval.h"

class MiaBinder ;
class MiaFactoid ;

class MiaMatcherBase : public MiaEval {
public:
	MiaMatcherBase(MiaBinder& binder, MiaFactoid& result, MiaPattern& pattern) 
		: MiaEval(binder), p_result(&result), p_pattern(&pattern) {
	}
	MiaFactoid* getResult() { return p_result ; }
	MiaFactoid& result() { return *p_result ; }
	MiaPattern* getPattern() { return p_pattern ; }
	MiaPattern& pattern() { return *p_pattern ; }
	//Data Members
private:
	MiaFactoid* p_result ;
	MiaPattern* p_pattern ;
} ;

#endif //_MiaMatcherBase_H
