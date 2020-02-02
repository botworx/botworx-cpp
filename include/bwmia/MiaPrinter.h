#ifndef _MiaPrinter_h
#define _MiaPrinter_h

#include <bwaxl/AxlPrinter.h>

class MiaPrinter : public AxlPrinter {
public:
	MiaPrinter() : AxlPrinter() {}
	MiaPrinter(std::ostream& out) : AxlPrinter(out) {}
	virtual void printCell(const BwCell* pCell) ;
} ;
inline MiaPrinter& operator<<(MiaPrinter& printer, const bwString& val) { printer.print(val) ; return printer ; }

#endif//_MiaPrinter_h
