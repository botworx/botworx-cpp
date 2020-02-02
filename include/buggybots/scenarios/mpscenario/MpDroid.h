/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _MpDroid_H
#define _MpDroid_H

#include "MpPersonality.h"

namespace MpScenario {

class MpDroid : public MpPersonality
{
public:
    MpDroid(BbPilotBrain* pBrain,
		BbPilot* w,
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
	{
		wanderer = w ;
	}
    // reset state
    void reset (void)
    {
        MpPersonality::reset ();
    }
	//
	virtual BwTask* produceTask(const bwString& name) ;
};

} //namespace MpScenario

#endif _MpDroid_H
