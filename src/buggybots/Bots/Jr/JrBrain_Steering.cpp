/*JrBots - A Botworx VR reference app and AI playground
Copyright (C) 2005  Kurtis Fields. See JrBots_License.txt for details.
*/
#include "stdafx.h"

#include <buggybots/bots/jr/JrBrain.h>
#include <buggybots/bots/jr/Jr.h>
#include <buggybots/bots/jr/JrFactory.h>
#include <buggybots/bots/jr/JrEngine.h>
#include <buggybots/bots/jr/JrWheel.h>

#include <bwvr/VrSteering.h>

namespace Jr {
void JrBrain::turnLeft() {
	if(!m_steeringTimer.checkAlarm())
		return ;
	m_steeringTimer.resetAlarm() ;
	for(int i = 0 ; i < Jr::WHEEL_TTL ; ++i) {
		p_wheelMech[i]->turnLeft() ;
	}
} 
void JrBrain::turnRight() {
	if(!m_steeringTimer.checkAlarm())
		return ;
	m_steeringTimer.resetAlarm() ;
	for(int i = 0 ; i < Jr::WHEEL_TTL ; ++i) {
		p_wheelMech[i]->turnRight() ;
	}
}
void JrBrain::turnNone() {
	if(!m_steeringTimer.checkAlarm()) {
		return ;
	}
	m_steeringTimer.resetAlarm() ;
	for(int i = 0 ; i < Jr::WHEEL_TTL ; ++i) {
		p_wheelMech[i]->turnNone() ;
	}
}

}//end namespace BwVr::Bots::Jr 