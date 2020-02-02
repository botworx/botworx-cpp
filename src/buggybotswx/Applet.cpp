/*BuggyBots - A Botworx VR reference app and AI playground
Copyright (C) 2005  Kurtis Fields. See BuggyBots_License.txt for details.
*/
#include "stdafx.h"

#include "Applet.h"
#include "User.h"
#include "BwxVrCtrl.h"
#include "BwxInjector.h"
//
#include <bwvr/VrScene.h>

Applet::Applet(wxFrame *pFrame, BwxVrCtrl* pCtrl) {
	p_frame = pFrame ;
	p_ctrl = pCtrl ;
}
Applet::~Applet() {
}
VrUser* Applet::produceUser(VrScene* pScene) {
	User* pUser = new User(pScene, p_frame, p_ctrl) ;
	pUser->create() ;
	return pUser ;
}