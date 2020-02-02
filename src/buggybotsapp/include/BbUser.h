/*BuggyBots - A Botworx VR reference app and AI playground
Copyright (C) 2005  Kurtis Fields. See BuggyBots_License.txt for details.
*/
#ifndef _BbUser_H
#define _BbUser_H

#include <bwvrcegui/VrCeguiUser.h>

class BbApplet ;
class BbScenario ;
class Buggy ;
class BuggyBrain ;

class VrCameraController ;
class VrHandController ;

//class BbUser : public VrUser
class BbUser : public VrCeguiUser
{
public:
	BbUser(VrScene *pScene) ;
	virtual void doCreate(const BwPartInfo& info) ;
	virtual void createGui() ;
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
	/*Data Members*/
};

#endif //_BbUser_H

