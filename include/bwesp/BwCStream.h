#ifndef _BwCStreamIn_H
#define _BwCStreamIn_H

#include "BwCBuffer.h"
//
//BwCStreamIn
//
class BwCStreamIn : public std::istream {
public:
	BwCStreamIn(BwCBuffer *pBuf) : m_pBuf(pBuf), std::istream(pBuf) {
	}
	virtual ~BwCStreamIn() {
	}
	//
	BwCBuffer *m_pBuf ;
};
/////////
inline BwCStreamIn& operator>> (BwCStreamIn& s, const BwMessage& msg) {
    boost::archive::text_iarchive ia(s);
	ia >> msg.data() ;
	return s ;
}
//
//
//
class BwCStreamOut : public std::ostream {
public:
	BwCStreamOut(BwCBuffer *pBuf) : m_pBuf(pBuf), std::ostream(pBuf) {
	}
	virtual ~BwCStreamOut() {
	}
	BwCStreamOut& operator<<(BwCStreamOut& (__cdecl *_Pfn)(BwCStreamOut&))
	{	// manip caller
		return ((*_Pfn)(*this));
	}
	//
	BwCBuffer *m_pBuf ;
};

inline BwCStreamOut& begin(BwCStreamOut& out) {
	return out ;
}

inline BwCStreamOut& end(BwCStreamOut& out) {
	BwCBuffer *pBuf = out.m_pBuf ;
	pBuf->setEot(true) ;
	out.flush() ;
	return out ;
}

inline BwCStreamOut& operator<< (BwCStreamOut& s, const BwMessage& msg) {
    boost::archive::text_oarchive oa(s);
	oa << msg.data() ;
	return s ;
}

#endif //_BwCStreamIn_H
