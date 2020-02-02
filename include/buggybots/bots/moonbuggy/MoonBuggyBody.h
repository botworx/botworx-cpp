/*BuggyBots - A Botworx VR reference app and AI playground
Copyright (C) 2005  Kurtis Fields. See BuggyBots_License.txt for details.
*/
#ifndef _MoonBuggyBody_H
#define _MoonBuggyBody_H

#include <bwvr/VrCapsule.h>
class VrGroup ;

namespace MoonBuggy {

class Buggy ;
class BuggyFactory ;

class BuggyBody : public VrCapsule {
public:
	BuggyBody(VrGroup *pGroup, Buggy *pRoot) ;
	virtual void doCreate(const BwPartInfo& info) ;
	//virtual void createVu() ;
	virtual bwString getClassName() { return "MoonBuggyBody" ; }
	virtual void createGeom() ;
	/*Data Members*/
	Buggy *p_buggy ;
} ;
}//end namespace MoonBuggy
#endif //_MoonBuggyBody_H
