/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _VrTracer_H
#define _VrTracer_H

class VrModel ;
class VrGroup ;
class VrBody ;

class VrTracer {
public:
	VrTracer() { p_marker = NULL ;	m_isActive = false ; }
	virtual ~VrTracer() ;
	virtual bwString getClassName() { return "VrTracer" ; }
	virtual void init() { m_isActive = true ; validate() ; }
	void invalidate() { validate() ; }
	virtual void validate() ;
	//convenience functions
	VrModel& model() ;
	VrGroup* getGroup() ;
	VrBody* getBody() ;
	//
	bool isActive() { return m_isActive ; }
	void* getMarker() { return p_marker ; }
	//Data Members
	void* p_marker ;
	bool m_isActive ;
} ;

#endif //_VrTracer_H