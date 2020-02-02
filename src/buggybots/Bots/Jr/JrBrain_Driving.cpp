/*JrBots - A Botworx VR reference app and AI playground
Copyright (C) 2005  Kurtis Fields. See JrBots_License.txt for details.
*/
#include "stdafx.h"

#include <buggybots/bots/jr/JrBrain.h>
#include <buggybots/bots/jr/Jr.h>
#include <buggybots/bots/jr/JrEngine.h>
#include <buggybots/bots/jr/JrBody.h>
#include <buggybots/bots/jr/JrWheel.h>
#include <buggybots/bots/jr/JrFactory.h>

#include <bwvr/VrSteering.h>

namespace Jr {
void JrBrain::moveForward() {
	if(!m_drivingTimer.checkAlarm()) {
		return ;
	}
	m_drivingTimer.resetAlarm() ;
	//m_power += .25 ;
	m_power += m_powerIncrement ;
	//p_engine->setPower(m_power) ;
	for(int i = 0 ; i < Jr::WHEEL_TTL ; ++i) {
		p_wheelMech[i]->moveForward() ;
	}
}
void JrBrain::moveReverse() {
	if(!m_drivingTimer.checkAlarm()) {
		return ;
	}
	m_drivingTimer.resetAlarm() ;
	m_power -= m_powerIncrement ;
	//p_engine->setPower(m_power) ;
	for(int i = 0 ; i < Jr::WHEEL_TTL ; ++i) {
		p_wheelMech[i]->moveReverse() ;
	}
}
void JrBrain::moveNone() {
	if(!m_drivingTimer.checkAlarm()) {
		return ;
	}
	m_drivingTimer.resetAlarm() ;

	m_power = 0 ;
	//p_engine->setPower(m_power) ;
	for(int i = 0 ; i < Jr::WHEEL_TTL ; ++i) {
		p_wheelMech[i]->moveNone() ;
	}
}
}//end namespace BwVr::Bots::Jr 