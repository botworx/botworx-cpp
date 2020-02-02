/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _SocPlayer_H
#define _SocPlayer_H

#include "SocPersonality.h"

namespace SoccerScenario {

class SocPlayer : public SocPersonality
{
public:
    SocPlayer(
		BbPilotBrain* pBrain,
		Players others, 
		Players allplayers,
		BbMarker* ball,
		VrModel* pTeamHome,
		VrModel* pEnemyHome,
		bool isTeamA, 
		int id) : 
	SocPersonality(
		pBrain,
		others, 
		allplayers, 
		ball,
		pTeamHome,
		pEnemyHome,
		isTeamA, 
		id)
	{
	}
    // reset state
    void reset (void)
    {
        SocPersonality::reset ();
    }
	//
	virtual BwTask* produceTask(const bwString& name) ;
};

} //namespace SocScenario

#endif _SocPlayer_H
