/*BuggyBots - A Botworx VR reference app and AI playground
Copyright (C) 2005  Kurtis Fields. See BuggyBots_License.txt for details.
*/
#ifndef _Applet_H
#define _Applet_H

#include "BbApplet.h"

class wxFrame ;
class BwxVrCtrl ;

class Applet : public BbApplet {
public:
	Applet(wxFrame *pFrame, BwxVrCtrl* pCtrl) ;
	virtual ~Applet();
	wxFrame* getFrame() { return p_frame ; }
	virtual VrUser* produceUser(VrScene* pScene) ;
	//
	wxFrame* p_frame ;
	BwxVrCtrl* p_ctrl ;
protected:
	//virtual void createScene() ;
};

#endif

