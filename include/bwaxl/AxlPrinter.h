#ifndef _AxlPrinter_h
#define _AxlPrinter_h

#include <bwai/AiPrinter.h>

class AxlXn ;

class AxlPrinter : public AiPrinter {
public:
	AxlPrinter() : AiPrinter() {}
	AxlPrinter(std::ostream& out) : AiPrinter(out) {}
	virtual void printCell(const BwCell* pCell) ;
	void printXn(AxlXn *pXn) ;
} ;


#endif//_AxlPrinter_h
