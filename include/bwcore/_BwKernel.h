#ifndef __BwKernel_H
#define __BwKernel_H

#include <bwmessaging/BwMessage.h>

namespace _BwKernel {

enum {
	KERNEL_SHUTDOWN = 1,
	KERNEL_INFO,
	KERNEL_WARNING,
	KERNEL_ERROR
} ;

//Mail
class Event : public BwMessage {
public:
	Event(bwWhat what) : BwMessage(what) {}
} ;

class Warning : public Event {
public:
	Warning(const bwString& desc) : Event(KERNEL_WARNING) {
		m_data->addString("Description", desc) ;
	}
} ;

class Info : public Event {
public:
	Info(const bwString& desc) : Event(KERNEL_INFO) {
		m_data->addString("Description", desc) ;
	}
} ;

}//namespace _BwKernel

#endif //__BwKernel_H