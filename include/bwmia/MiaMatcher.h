/*Botworx AI - An Artificial Intelligence Framework
Copyright (C) 2004  Kurtis Fields. See BotworxAI_License.txt for details.
*/
#ifndef _MiaMatcher_H
#define _MiaMatcher_H

#include "MiaSubjectMatcher.h"


class MiaMatcher : public MiaSubjectMatcher {
public:
	MiaMatcher(MiaBinder& binder, MiaFactoid& result, MiaPattern& pattern)
		: MiaSubjectMatcher(binder, result, pattern) {
	}
	//Data Members
} ;

#endif //_MiaMatcher_H
