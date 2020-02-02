#ifndef _AiPrinter_h
#define _AiPrinter_h

#include <bwmessaging/BwPrinter.h>

class AiInt ;
class AiFloat ;

class AiPrinter : public BwPrinter {
public:
	AiPrinter() : BwPrinter() {}
	AiPrinter(std::ostream& out) : BwPrinter(out) {}
	void printString(const AiString *pString) ;
	void printSymbol(const AiSymbol *pSymbol) ;
	void printInt(const AiInt *pCell) ;
	void printFloat(const AiFloat *pCell) ;
	virtual void printCell(const BwCell* pCell) ;
	void printCellLn(const BwCell* pCell) ;
	void printDottedPair(const AiPair* pPair) ;
	void printPair(const AiPair* pPair) ;
	void printList(const AiPair* pPair) ;
} ;

inline AiPrinter& operator<<(AiPrinter &printer, const BwCell& val) { printer.printCell(&val) ; return printer ; }

#endif//_AiPrinter_h
