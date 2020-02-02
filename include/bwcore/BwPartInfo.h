/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _BwPartInfo_H
#define _BwPartInfo_H

enum bwPartStyle_E {
	PS_DEFAULT = 0,
	PS_CREATE_ENABLED = 1,
	PS_CREATE_SLEEPING = 2,
	PS_STATIC = 4,
	PS_QUASISTATIC = 8
} ;
typedef unsigned int bwPartStyle ;

class BwPartInfo {
public:
	BwPartInfo(bwPartStyle createStyle = PS_DEFAULT) : m_createStyle(createStyle) {}
	bwPartStyle getCreateStyle() const { return m_createStyle ; }
	//Data Members
	bwPartStyle m_createStyle ;
} ;

#endif //_BwPartInfo_H

