#ifndef _BwMailBox_H
#define _BwMailBox_H

#include "BwMailSlot.h"

class BwMailer : public BwPart {
public:
	BwMailer(BwPart* pOwner) ;
	~BwMailer() ;
	void addSlot(BwMailSlot* pSlot) ;
	virtual BwMailSlot* findSlot(const bwString& name) ;
	void removeSlot(const bwString& name) ;
	//Data Members
	BwMailSlotMap m_slots ;
	int m_slotHandleCount ;
} ;

enum hMailBox_E {
	MB_PRIMARY = 0
};
typedef hMailBox_E hMailBox ;

class BwMailBox : public BwMailer {
public:
	BwMailBox(BwPart* pOwner) ;
	~BwMailBox() ;
	//Data Members
} ;
//
typedef std::vector<BwMailBox*> BwMailBoxes ;
typedef BwMailBoxes::iterator BwMailBoxIter ;
//
typedef std::pair<BwMailBox*, BwPart*> BwMailBoxMapPair ;
typedef std::vector<BwMailBoxMapPair> BwMailBoxMap ;
typedef BwMailBoxMap::iterator BwMailBoxMapIter ;

#endif //_BwMailBox_H