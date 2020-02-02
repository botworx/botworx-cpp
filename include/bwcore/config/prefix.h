/*Botworx AI - An Artificial Intelligence Framework
Copyright (C) 2004  Kurtis Fields. See BotworxAI_License.txt for details.
*/
#ifndef _Kernel_prefix_H
#define _Kernel_prefix_H

enum RawTT_E {

	#include <bwcore/config/types.h>
	TT_CELL_UNKNOWN,
	TT_UNKNOWN
} ;
//typedef unsigned char ThingTT ;
typedef RawTT_E ThingTT ;

#endif //_Kernel_prefix_H