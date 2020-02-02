/*BuggyBots - A Botworx VR reference app and AI playground
Copyright (C) 2005  Kurtis Fields. See BuggyBots_License.txt for details.
*/
#ifndef _BbScene_H
#define _BbScene_H

#include <bwvr/VrScene.h>
#include "BbApplet.h"
//
//BbScene
//
class BbScene : public VrScene
{
public:
	BbScene(VrScenario *pScenario);
	virtual ~BbScene();
	virtual void doCreate(const BwPartInfo& info) ;
	//virtual bool doStep(BwStepper& stepper) ;
	virtual void doStep(BwStepper& stepper) ;
	virtual void createUser() ;
	/*Data Members*/
	BwLoTimer m_displayUpdateTimer ;
};

#endif //_BbScene_H