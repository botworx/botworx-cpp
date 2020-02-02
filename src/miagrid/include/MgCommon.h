/*Botworx AI - An Artificial Intelligence Framework
Copyright (C) 2004  Kurtis Fields. See BotworxAI_License.txt for details.
*/
#ifndef _MgCommon_H
#define _MgCommon_H

class mgPos {
public:
	mgPos() : x(0), y(0) {}
	mgPos(int xCoord, int yCoord) : x(xCoord), y(yCoord) {}
	int x ;
	int y ;
};

#endif //_MgCommon_H
