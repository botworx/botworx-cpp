#include "stdafx.h"

#include <bwmessaging/BwPrinter.h>

#include <bwcore/_BwPart.h>
using namespace _BwPart ;

void BwMailSlotSink::flush() {
	if(isDisabled())
		return ;
	if(m_buffer == "")
		return ;
	p_slot->send(BwTextOutput(m_buffer)) ;
	m_buffer = "" ;
}
//////////
void BwCharVectorSink::puts(const char *s) { 
	for(size_t size = strlen(s) ; size != 0 ; size--) {
		vector().push_back(*s++) ;
	}
}
//////////
BwPrinter::BwPrinter() : p_sink(nullptr), p_chain(nullptr) {
}
BwPrinter::BwPrinter(std::ostream& out) : m_streamSink(true), p_chain(nullptr) { 
	m_streamSink.setStream(out) ;
	p_sink = &m_streamSink ;
}
BwPrinter::BwPrinter(BwSink* pSink) : p_sink(pSink), p_chain(nullptr) {}
BwPrinter::~BwPrinter() {
	if(p_sink != nullptr)
		if(!p_sink->isInternal())
			delete p_sink ;
}
void BwPrinter::pushSink(BwSink* pSink) { 
	BwSink* pPrev = p_sink ;
	p_sink = pSink ;
	pSink->setPrevious(pPrev) ;
}
BwSink* BwPrinter::popSink() { 
	BwSink* pCurrent = p_sink ;
	p_sink = pCurrent->getPrevious() ;
	return pCurrent ; 
}
//
BwPrinter& operator<<(BwPrinter &printer, long val) { 
	char buffer[64] ;
	// _ltoa(val, buffer, 10) ;
	snprintf(buffer, 64, "%l", val);
	printer.sink() << buffer ;
	return printer ; 
}
BwPrinter& operator<<(BwPrinter &printer, int val) { 
	char buffer[64] ;
	//_ltoa(val, buffer, 10) ;
	snprintf(buffer, 64, "%i", val);
	printer.sink() << buffer ;
	return printer ; 
}
BwPrinter& operator<<(BwPrinter &printer, double val) {
	char buffer[64] ;
	//_gcvt(val, 6, buffer);
	snprintf(buffer, 64, "%d", val);
	printer.sink() << buffer ;
	return printer ; 
}
BwPrinter& operator<<(BwPrinter &printer, float val) {
	char buffer[64] ;
	//_gcvt(val, 6, buffer);
	snprintf(buffer, 64, "%f", val);
	printer.sink() << buffer ;
	return printer ; 
}