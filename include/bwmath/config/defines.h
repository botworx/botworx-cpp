/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxPZ_License.txt for details.
*/
#ifndef _BwMath_defines_H
#define _BwMath_defines_H

namespace bwmath {
	enum PlaneSide {
		ON_PLANE,
		POS_SIDE,
		NEG_SIDE
	};
	enum rotationMode_E {
		ROTMODE_FREE = 0,
		ROTMODE_FIXED
	} ;
	typedef rotationMode_E rotationMode ;
	enum positionMode_E {
		POSMODE_FREE = 0,
		POSMODE_FIXED
	} ;
	typedef positionMode_E positionMode ;
}

#endif //_BwMath_defines_H
