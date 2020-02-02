/*Botworx AI - An Artificial Intelligence Framework
Copyright (C) 2004  Kurtis Fields. See BotworxAI_License.txt for details.
*/
#ifndef _Ai_prefix_H
#define _Ai_prefix_H

enum RawTT_E {

	#include <bwai/config/types.h>
	TT_CELL_UNKNOWN,
	TT_UNKNOWN
} ;
//typedef unsigned char ThingTT ;
typedef RawTT_E ThingTT ;

//
//
//
enum KitTT_E {

	#include <bwai/config/kits.h>
	KT_UNKNOWN
} ;
typedef KitTT_E KitTT ;

#endif //_Ai_prefix_H