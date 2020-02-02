/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _MpHuman_H
#define _MpHuman_H

#include "MpPersonality.h"

namespace MpScenario {

class MpHuman : public MpPersonality
{
public:
    MpHuman(BbPilotBrain* pBrain,
		Pilots others, 
		Pilots allplayers, 
		VrModel* pTeamHome,
		VrModel* pEnemyHome,
		bool isTeamA, 
		int id) : 
	MpPersonality(pBrain,
		others, 
		allplayers, 
		pTeamHome,
		pEnemyHome,
		isTeamA, 
		id)
	{}

    // reset state
    void reset (void)
    {
        MpPersonality::reset ();
    }
	virtual BwTask* produceTask(const bwString& name) ;
};

} //namespace MpScenario

#endif _MpHuman_H
