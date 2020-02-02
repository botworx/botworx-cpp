/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _MoonBuggyChassis_H
#define _MoonBuggyChassis_H

#include <bwvr/VrFixedAssembly.h>

namespace MoonBuggy {
class Buggy ;
class BuggyFactory ;
class BuggyBrain ;
class BuggyEngine ;
class BuggyBody ;
class BuggyWheel ;

class BuggyChassis : public VrFixedAssembly {
public:
	BuggyChassis(Buggy *pBuggy) ;
	virtual void doCreate(const BwPartInfo& info) ;
	virtual void createVu() ;
	virtual bwString getClassName() { return "MoonBuggyChassis" ; }
	BuggyBody* getBuggyBody() { return p_buggyBody ; }
	/*Data Members*/
	Buggy *p_buggy ;
	BuggyBody *p_buggyBody ;
};
}//end namespace MoonBuggy

#endif //_MoonBuggyChassis_H
