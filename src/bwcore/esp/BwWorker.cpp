/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <bwesp/BwWorker.h>
#include <bwcore/config/boost_thread.h>

BwWorker::BwWorker(BwPart* pOwner) : BwPart(pOwner) {
}
struct BwWorkerThreadFn
{
	BwWorkerThreadFn(BwWorker *pWorker) : p_worker(pWorker) { }
	void operator()() {
		p_worker->work() ;
	}
	BwWorker* p_worker ;
} ;
void BwWorker::onEnable(bool sleeping) {
	p_thread = new boost::thread(BwWorkerThreadFn(this)) ;
	return BwPart::onEnable(sleeping) ;
}
