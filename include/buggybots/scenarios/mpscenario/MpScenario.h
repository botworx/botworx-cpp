/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _MpScenario_H
#define _MpScenario_H

#include <buggybots/BbScenario.h>
#include <buggybots/BbPilot.h>

using namespace BbSteer;
//
#include <bwvr/VrBall.h>
#include <bwvr/VrBody.h>

namespace MpScenario {

typedef std::vector<BbPilot*> Pilots ;
class MpWanderer ;

class MpScenario : public BbScenario {
public:
	MpScenario(VrApplet* pApplet) ;
	virtual void createWorld() ;
	virtual void doPostEnable(bool sleeping = false) ;
	void buildProps(VrGroup *pGroup) ;
	//
    unsigned int	m_PlayerCountA;
    unsigned int	m_PlayerCountB;
    Pilots TeamA;
    Pilots TeamB;
    Pilots m_AllPlayers;

    VrBall	*m_Ball;
	VrModel* m_TeamAGoal ;
	VrModel* m_TeamBGoal ;
    int		m_redScore;
    int		m_blueScore;
	//
	OpenSteer::BruteForceProximityDatabase<AbstractVehicle*> m_pd ;
	//
	BbPilot* p_wanderer ;
} ;

enum {
	CAT_DESTROYED = 0,
	CAT_PLAYER,
	CAT_ITEM
} ;

} //namespace MpScenario

#endif //_MpScenario_H
