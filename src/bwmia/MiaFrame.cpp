/*Botworx AI - An Artificial Intelligence Framework
Copyright (C) 2004  Kurtis Fields. See BotworxAI_License.txt for details.
*/
#include "stdafx.h"

#include <bwmia/MiaFrame.h>

#include <bwmia/MiaAgent.h>
#include <bwagency/_BwAgent.h>
using namespace _BwAgent ;

MiaFrame::MiaFrame(MiaMind* pParent, AiSymbol* pSymbol) : MiaMind(pParent, pSymbol) {
}

bool MiaFrame::onCreate(const BwPartInfo& info) {
	if(k_core().getIoMode() == MiaCore::IO_MESSAGING) {
		//setIsLogging(true) ;
		setIsEmitting(true) ;
	}
//
#if AI_OPTION_INSTRUMENT
	if(isEmitting()) {
		MiaPrinter printer ;
		BwStringSink printSink(true) ;
		//
		bwHandle parentHandle = bwAnyHandle ;
		if(hasParent())
			parentHandle = getParent()->getHandle() ;

		k_agent().getEventSlot().send(BwFrameAddedEvent(getSymbol()->getString(), getHandle(), parentHandle)) ;
	}
#endif
//
	k_agent().addFrame(this) ;
	return MiaMind::onCreate(info) ;
}
