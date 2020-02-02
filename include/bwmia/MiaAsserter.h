/*Botworx AI - An Artificial Intelligence Framework
Copyright (C) 2004  Kurtis Fields. See BotworxAI_License.txt for details.
*/
#ifndef _MiaAsserter_H
#define _MiaAsserter_H

#include "MiaSubjectAsserter.h"

class MiaAsserter : public MiaSubjectAsserter {
public:
	MiaAsserter(MiaBinder& binder, MiaFactoid& result)
		: MiaSubjectAsserter(binder, result) {
	}
	//Data
} ;

#endif //_MiaAsserter_H
