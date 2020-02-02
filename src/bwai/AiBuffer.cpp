/*Botworx AI - An Artificial Intelligence Framework
Copyright (C) 2004  Kurtis Fields. See BotworxAI_License.txt for details.
*/
#include "stdafx.h"

#include <bwai/AiBuffer.h>

void AiBuffer::purge() {
	AiBuffer::~AiBuffer() ;
#if AI_OPTION_POOLING
	k_buffer().release(this) ;
#else
	BW_USERFREE(this, TT_BUFFER) ;
#endif
}
