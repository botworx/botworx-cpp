/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <bwvr/VrSurfaceInfo.h>

VrSurfaceInfo::VrSurfaceInfo() {
	m_mode = dContactBounce | dContactApprox1 ;
	//m_mu = 20 ;
	m_mu = .49f ; //switching to mu scaling.
	m_bounce = 0.3f ;
	m_bounceVel = 0.1f ;
}
VrSurfaceInfo::~VrSurfaceInfo() {
}