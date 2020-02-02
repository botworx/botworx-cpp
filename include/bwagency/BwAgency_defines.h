/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _BwAgency_defines_H
#define _BwAgency_defines_H

enum agentType_E {
	AGENT_DEFAULT = 0,
	AGENT_MIA_DEFAULT = AGENT_DEFAULT,
	AGENT_TTL
} ;
typedef agentType_E agentType ;

enum stateType_E {
	STATE_DEFAULT = 0,
	STATE_MIA_DEFAULT = STATE_DEFAULT,
	STATE_TTL
} ;
typedef stateType_E stateType ;

#endif //_BwAgency_defines_H