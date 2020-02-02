/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _MpPersonality_H
#define _MpPersonality_H

#include <buggybots/BbScenario.h>
#include <buggybots/BbPilotPersonality.h>
#include <bwcontrol/BwTaskGroup.h>
//
#include <bwvr/VrBall.h>
#include <bwvr/VrBody.h>

namespace MpScenario {

class MpPersonality : public BbPilotPersonality {
public:
    MpPersonality(BbPilotBrain* pBrain,
		Pilots others, 
		Pilots allplayers, 
		VrModel* pTeamHome,
		VrModel* pEnemyHome,
		bool isTeamA, 
		int id) : 
	BbPilotPersonality(pBrain),
		m_others(others),
		m_AllPilots(allplayers), 
		p_teamHome(pTeamHome),
		p_enemyTeamHome(pEnemyHome),
		b_ImTeamA(isTeamA), 
		m_MyID(id) 
	{
		//
		m_minorTasks.setIsMutex(false) ;
		addTaskGroup(&m_majorTasks) ;
		addTaskGroup(&m_minorTasks) ;
		//
		reset ();
	}
    void reset (void) ;
	//
	virtual BwTask* produceTask(const bwString& name) ;
	//
    // per-instance reference to its group
    Pilots	m_others ;
    Pilots	m_AllPilots ;
    VrBall*	m_Ball ;
	VrModel* p_teamHome ;
	VrModel* p_enemyTeamHome ;
	//
	BbPilot* wanderer ;
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

	//proximity test scratch pad.
	AVGroup& proximity() { return m_proximity ; }
	AVGroup m_proximity ;
	//
	AVGroup& neighbors() { return m_neighbors ; }
	AVGroup m_neighbors ;
	float m_minTimeToCollision ;
	//
	PolylinePathway m_path ;
	//
	BwTaskGroup m_minorTasks ;
	BwTaskGroup m_majorTasks ;
	//
	BbMarker* p_item ;
	AVGroup& items() { return m_items ; }
	AVGroup m_items ;
	//
	BbMarker* p_enemy ;
	//
	AVGroup& pursuers() { return m_pursuers ; }
	AVGroup m_pursuers ;
} ;

} //namespace MpScenario

#endif _MpPersonality_H
