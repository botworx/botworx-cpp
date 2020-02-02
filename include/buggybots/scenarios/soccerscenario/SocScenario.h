/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _BbSoccerScenario_H
#define _BbSoccerScenario_H

#include <buggybots/BbScenario.h>

#include <buggybots/scenarios/soccerscenario/SocScenario_common.h>

namespace SoccerScenario {
class BbSoccerScenario : public BbScenario {
public:
	BbSoccerScenario(VrApplet* pApplet) ;
	virtual void createWorld() ;
	void buildGoals(VrGroup *pGroup) ;
	//
    unsigned int	m_PlayerCountA;
    unsigned int	m_PlayerCountB;
    Players TeamA;
    Players TeamB;
    Players m_AllPlayers;

    BbMarker* m_Ball ;
	VrModel* m_TeamAGoal ;
	VrModel* m_TeamBGoal ;
    int		m_redScore;
    int		m_blueScore;
	//
	OpenSteer::BruteForceProximityDatabase<OpenSteer::AbstractVehicle*> m_pd ;
} ;

} // namespace SoccerScenario {

#endif //_BbSoccerScenario_H
