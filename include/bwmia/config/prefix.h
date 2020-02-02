/*Botworx AI - An Artificial Intelligence Framework
Copyright (C) 2004  Kurtis Fields. See BotworxAI_License.txt for details.
*/
#ifndef _Mia_prefix_H
#define _Mia_prefix_H

enum RawTT_E {

	#include <bwmia/config/types.h>
	TT_CELL_UNKNOWN,
	TT_UNKNOWN
} ;
//typedef unsigned char ThingTT ;
typedef RawTT_E ThingTT ;
//
//
//
enum KitTT_E {

	#include <bwmia/config/kits.h>
	KT_UNKNOWN
} ;
typedef KitTT_E KitTT ;

#endif //_Mia_prefix_H