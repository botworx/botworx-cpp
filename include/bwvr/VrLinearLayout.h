/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _VrLinearLayout_H
#define _VrLinearLayout_H

#include "VrLayout.h"

class VrLinearLayout ;

class VrLinearLayout : public VrLayout {
public:
	VrLinearLayout(VrGroup *pGroup) ;
	virtual void layout() ;
	virtual bwString getClassName() { return "VrLinearLayout" ; }
	void setDirection(char x, char y, char z) {
		m_direction[0] = x ;
		m_direction[1] = y ;
		m_direction[2] = z ;
	}
	//Data Members
};

class VrRowLayout : public VrLinearLayout {
public:
	VrRowLayout(VrGroup *pGroup) : VrLinearLayout(pGroup) {
		m_direction[0] = 1 ;
		m_direction[1] = 0 ;
		m_direction[2] = 0 ;
	}
	virtual bwString getClassName() { return "VrRowLayout" ; }
};

class VrColumnLayout : public VrLinearLayout {
public:
	VrColumnLayout(VrGroup *pGroup) : VrLinearLayout(pGroup) {
		m_direction[0] = 0 ;
		m_direction[1] = 0 ;
		//m_direction[2] = 1 ;
		m_direction[2] = -1 ;
	}
	virtual bwString getClassName() { return "VrColumnLayout" ; }
};

class VrStackLayout : public VrLinearLayout {
public:
	VrStackLayout(VrGroup *pGroup) : VrLinearLayout(pGroup) {
		m_direction[0] = 0 ;
		m_direction[1] = 1 ;
		m_direction[2] = 0 ;
	}
	virtual bwString getClassName() { return "VrStackLayout" ; }
};

#endif //_VrLinearLayout_H
