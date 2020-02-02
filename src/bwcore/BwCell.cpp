/*Botworx AI - An Artificial Intelligence Framework
Copyright (C) 2004  Kurtis Fields. See BotworxAI_License.txt for details.
*/
#include "stdafx.h"

//
//BwCell
//
void BwCell::purge() {
	//bwAssert(0) ;
	BW_FREE(this) ;
}
