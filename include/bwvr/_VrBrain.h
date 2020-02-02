#ifndef __VrBrain_H
#define __VrBrain_H

#include <bwcore/_BwPart.h>

namespace _VrBrain {
	using namespace _BwPart ;
	enum {
		COMMAND_LEFT = BWPART_MSG_TTL,
		COMMAND_FORWARD,
		COMMAND_RIGHT,
		COMMAND_REVERSE,
		COMMAND_JUMP,
		COMMAND_FLIP,
		COMMAND_FIRE_MISSILE,
		COMMAND_FIRE_LASER,
		COMMAND_PITCH_UP,
		COMMAND_PITCH_DOWN,
		COMMAND_ROLL_LEFT,
		COMMAND_ROLL_RIGHT,
		VRBRAIN_MSG_TTL
	};
};

#endif //__VrBrain_H
