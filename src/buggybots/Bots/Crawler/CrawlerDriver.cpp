/*BuggyBots - A Botworx VR reference app and AI playground
Copyright (C) 2005  Kurtis Fields. See BuggyBots_License.txt for details.
*/
#include "stdafx.h"

#include <buggybots/bots/crawler/CrawlerBrain.h>
#include <buggybots/bots/crawler/Crawler.h>
#include <buggybots/bots/crawler/CrawlerFactory.h>
#include <buggybots/bots/crawler/CrawlerLeg.h>
#include <buggybots/bots/crawler/CrawlerLegSeg.h>
////////////////////////////////////////////////////
namespace Crawler {
//////////////////////////
void CrawlerDriver::doStep(BwStepper& stepper) {
	BwTask::doStep(stepper) ;
	switch(m_status) {
		case PLAN_START :
		case TASK_START :
			clearDependencies() ;
			brain().moveForward() ;
			setStatus(TASK_BUSY) ;
			break ;
		case TASK_BUSY : 
			if(testDependencies(TASK_SUCCESS))
				setStatus(TASK_SUCCESS) ;
			break ;
		case TASK_SUCCESS :
			setStatus(PLAN_START) ;
			break ;
	}
}
//////////////////////////
}//namespace Crawler
////////////////////////////////////////////////////
