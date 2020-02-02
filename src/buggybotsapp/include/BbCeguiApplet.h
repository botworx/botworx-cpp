/*BuggyBots - A Botworx VR reference app and AI playground
Copyright (C) 2005  Kurtis Fields. See BuggyBots_License.txt for details.
*/
#ifndef _BbCeguiApplet_H
#define _BbCeguiApplet_H

#include <buggybots/BbApplet.h>

class VrUser ;
class Buggy ;

class BbCeguiApplet : public BbApplet {
public:
	BbCeguiApplet();
	virtual ~BbCeguiApplet();
	//
	virtual VrUser* produceUser(VrScene* pScene) ;
};

#endif //_BbApplet_H