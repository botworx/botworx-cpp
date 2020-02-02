/*Botworx AI - An Artificial Intelligence Framework
Copyright (C) 2004  Kurtis Fields. See BotworxAI_License.txt for details.
*/
#ifndef _Axl_prefix_H
#define _Axl_prefix_H

enum RawTT_E {
	#include <bwaxl/config/types.h>
	TT_CELL_UNKNOWN,
	TT_UNKNOWN
} ;
//typedef unsigned char ThingTT ;
typedef RawTT_E ThingTT ;

//
//
//
enum KitTT_E {
	#include <bwaxl/config/kits.h>
	KT_UNKNOWN
} ;
typedef KitTT_E KitTT ;

#endif //_Axl_prefix_H