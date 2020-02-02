#ifndef _BwPoWorker_H
#define _BwPoWorker_H

#include "BwWorker.h"

class BwPostOffice ;

class BwPoWorker : public BwWorker {
public:
	BwPoWorker(BwPart *pOwner) ;
	virtual void doCreate(const BwPartInfo& info) ;
	virtual void work() ;
	//
	void setPo(BwPostOffice* pPo) { p_po = pPo ; }
	BwPostOffice& po() { return *getPo() ; }
	BwPostOffice* getPo() { return p_po ; }
	//Data Members
	BwPostOffice* p_po ;
} ;

#endif //_BwPoWorker_H