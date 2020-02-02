#ifndef _BwMailCenter_H
#define _BwMailCenter_H

#include "BwMailBox.h"

class BwMailCenter : public BwPart {
public:
	BwMailCenter() ;
	~BwMailCenter() ;
	bwHandle addBox(BwMailBox* pBox, BwPart *pAddressee) ;
	virtual BwMailBox* findBox(bwHandle handle) ;
	BwPart* findAddressee(bwHandle handle) ;
	void removeBox(bwHandle handle) ;
	//Data Members
	BwMailBoxMap m_boxes ;
	bwHandle m_nextHandle ;
} ;

#endif //_BwMailCenter_H