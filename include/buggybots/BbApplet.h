/*BuggyBots - A Botworx VR reference app and AI playground
Copyright (C) 2005  Kurtis Fields. See BuggyBots_License.txt for details.
*/
#ifndef _BbApplet_H
#define _BbApplet_H

#include <bwvr/VrApplet.h>

class VrUser ;
class Buggy ;

class BbApplet : public VrApplet {
public:
	BbApplet();
	virtual ~BbApplet();
	//
	//virtual VrUser* produceUser(VrScene* pScene) ;
protected:
	virtual void createScenario() ;
};

#endif //_BbApplet_H