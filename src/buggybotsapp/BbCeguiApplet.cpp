/*BuggyBots - A Botworx VR reference app and AI playground
Copyright (C) 2005  Kurtis Fields. See BuggyBots_License.txt for details.
*/
#include "stdafx.h"

#include "BbCeguiApplet.h"
#include "BbUser.h"

BbCeguiApplet::BbCeguiApplet(void) {
}

BbCeguiApplet::~BbCeguiApplet() {
}
VrUser* BbCeguiApplet::produceUser(VrScene* pScene) {
	BbUser* pUser = new BbUser(pScene) ;
	pUser->create() ;
	return pUser ;
}