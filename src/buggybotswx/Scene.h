/*BuggyBots - A Botworx VR reference app and AI playground
Copyright (C) 2005  Kurtis Fields. See BuggyBots_License.txt for details.
*/
#ifndef _Scene_H
#define _Scene_H

#include "BbScene.h"

class Applet ;

class Scene : public BbScene
{
public:
	Scene(VrScenario *pScenario);
	virtual ~Scene();
	virtual void doCreate(const BwPartInfo& info) ;
	//virtual void createUser() ;
	/*Data Members*/
	wxFrame* getFrame() { return p_frame ; }
	//
	wxFrame* p_frame ;
};

#endif

