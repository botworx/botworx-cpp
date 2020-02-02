/*BuggyBots - A Botworx VR reference app and AI playground
Copyright (C) 2005  Kurtis Fields. See BuggyBots_License.txt for details.
*/
#ifndef _BbWorld_H
#define _BbWorld_H

#include <bwvr/VrWorld.h>
#include <bwvr/VrCollider.h>
#include <bwvr/VrQuadNodeKit.h>
#include <bwvr/VrSharedVu.h>

class BbWorld : public VrWorld
{
public:
	BbWorld(BwActor *pActor) ;
	virtual ~BbWorld();
	virtual void createVu() ;
	virtual void createNodeKit() ;
	virtual void createNode() ;
	//Data Members
};

#endif //_BbWorld_H

