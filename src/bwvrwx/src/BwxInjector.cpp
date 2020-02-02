#include "stdafx.h"

#include "BwxInjector.h"

BEGIN_EVENT_TABLE(BwxInjector, wxEvtHandler)
	EVT_LEFT_DOWN(BwxInjector::mousePressed)
	EVT_LEFT_UP(BwxInjector::mouseReleased)
	EVT_MIDDLE_DOWN(BwxInjector::mousePressed)
	EVT_MIDDLE_UP(BwxInjector::mouseReleased)
	EVT_RIGHT_DOWN(BwxInjector::mousePressed)
	EVT_RIGHT_UP(BwxInjector::mouseReleased)
	//
	EVT_MOTION(BwxInjector::mouseMoved)
	//
	EVT_KEY_DOWN(BwxInjector::keyPressed)
	EVT_KEY_UP(BwxInjector::keyReleased)
END_EVENT_TABLE()

	/*
	    EVT_LEFT_DOWN(func) \
    EVT_LEFT_UP(func) \
    EVT_MIDDLE_DOWN(func) \
    EVT_MIDDLE_UP(func) \
    EVT_RIGHT_DOWN(func) \
    EVT_RIGHT_UP(func) \
    EVT_MOTION(func) \
    EVT_LEFT_DCLICK(func) \
    EVT_MIDDLE_DCLICK(func) \
    EVT_RIGHT_DCLICK(func) \
    EVT_LEAVE_WINDOW(func) \
    EVT_ENTER_WINDOW(func) \
    EVT_MOUSEWHEEL(func)

	*/
