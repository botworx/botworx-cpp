/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _User_H
#define _User_H

#include <BwxUser.h>

class UserMode ;

class User : public BwxUser {
public:
	User(VrScene *pScene, wxFrame *pFrame, BwxVrCtrl* pCtrl) ;
	virtual void doCreate(const BwPartInfo& info) ;
	virtual bool processEvent(BwControllerEvent&& evt) ;
	//
	void mouseMoved (BwControllerEvent& evt) ;
	void mouseDragged (BwControllerEvent& evt) ;
    void mousePressed (BwControllerEvent& evt) ;
    void mouseReleased (BwControllerEvent& evt) ;
	void mouseClicked(BwControllerEvent& evt) {}
	void mouseEntered(BwControllerEvent& evt) {}
	void mouseExited(BwControllerEvent& evt) {}

    void keyPressed(BwControllerEvent& evt) ;
	void keyReleased(BwControllerEvent& evt) ;
	void keyClicked(BwControllerEvent& evt) ;
};

#endif //_User_H