/*Botworx AI - An Artificial Intelligence Framework
Copyright (C) 2004  Kurtis Fields. See BotworxAI_License.txt for details.
*/
#include "stdafx.h"

#include <bwai/AiBlob.h>

//
//AiBlobType
//
void AiBlobType::purge() {
	AiBlobType::~AiBlobType() ;
	BW_USERFREE(this, TT_BLOBTYPE) ;
}
//
//AiBlob
//
AiBlob::~AiBlob() {
}
//
//AiBlobKit Meta
//
DEFINE_KITTYPE(AiBlobKit) ;

TYPEINFO_NONE(AiBlobKit) ;
NO_KITINFO(AiBlobKit) ;

KITINFO("AiBlobKit", KT_BLOB, AiBlobKit) ;
