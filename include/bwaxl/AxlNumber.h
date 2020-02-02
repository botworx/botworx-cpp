/*Botworx AI - An Artificial Intelligence Framework
Copyright (C) 2004  Kurtis Fields. See BotworxAI_License.txt for details.
*/
#ifndef _AxlNumber_H
#define _AxlNumber_H

#include <bwai/AiNumber.h>

class AxlNumberKit : public AiNumberKit {
public:
	AxlNumberKit(AiKit* pSuperKit, AiKitInfo *pKitInfo) 
		: AiNumberKit(AXL_KT_NUMBER, pSuperKit, pKitInfo) {}
} ;

#endif //_AxlNumber_H
