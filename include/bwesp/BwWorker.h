#ifndef _BwWorker_H
#define _BwWorker_H

namespace boost {
	class thread ;
}

class BwWorker : public BwPart {
public:
	BwWorker(BwPart* pOwner) ;
	virtual void onEnable(bool sleeping) ;
	virtual void work() = 0 ;
	//
	void setThread(boost::thread* pThread) { p_thread = pThread ; }
	boost::thread* getThread() { return p_thread ; }
	//Data Members
	boost::thread* p_thread ;
} ;

#endif //_BwWorker_H