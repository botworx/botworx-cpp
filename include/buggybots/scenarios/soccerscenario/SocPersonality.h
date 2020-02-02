/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _SocPersonality_H
#define _SocPersonality_H

#include <buggybots/BbScenario.h>
#include <buggybots/BbPilotPersonality.h>

#include <bwcontrol/BwTaskGroup.h>

namespace SoccerScenario {

class SocPersonality : public BbPilotPersonality {
public:
    SocPersonality(BbPilotBrain* pBrain,
		Players others, 
		Players allplayers, 
		BbMarker* ball,
		VrModel* pTeamHome,
		VrModel* pEnemyHome,
		bool isTeamA, 
		int id) : 
	BbPilotPersonality(pBrain),
		m_others(others),
		m_AllPlayers(allplayers), 
		m_Ball(ball), 
		p_teamHome(pTeamHome),
		p_enemyTeamHome(pEnemyHome),
		b_ImTeamA(isTeamA), 
		m_MyID(id) 

	{
		m_minorTasks.setIsMutex(false) ;
		addTaskGroup(&m_majorTasks) ;
		addTaskGroup(&m_minorTasks) ;
		//
		reset ();
	}
    // reset state
    void reset (void) ;
	//
	virtual BwTask* produceTask(const bwString& name) ;
	//
    // per-instance reference to its group
    Players	m_others ;
    Players	m_AllPlayers ;
    BbMarker*	m_Ball ;
	VrModel* p_teamHome ;
	VrModel* p_enemyTeamHome ;
	//
	void setAvatar(VrModel* pAvatar) { p_avatar = pAvatar ; }
	VrModel* p_avatar ;
	//
    bool	b_ImTeamA;
    int		m_MyID;
    bwVector3		m_home;
	//
	static bwVector3 playerPosition[9] ;
	//
    // allocate one and share amoung instances just to save memory usage
    // (change to per-instance allocation to be more MP-safe)
	AVGroup neighbors;
	float m_minTimeToCollision ;
	//
	PolylinePathway m_path ;
	//
	//BwTaskGroup m_taskGroup ;
	BwTaskGroup m_minorTasks ;
	BwTaskGroup m_majorTasks ;
} ;

} //namespace SocScenario

#endif _SocPersonality_H
