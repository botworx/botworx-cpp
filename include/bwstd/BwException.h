/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _BwException_H
#define _BwException_H

class BwException : public std::exception {
public:
	BwException(){}
} ;

class BwGeneralException {
public:
	BwGeneralException(const char* pWhat) : p_what(pWhat) {}
	virtual const char *what( ) const throw( ) { return p_what ; }
	//Data Members
	const char* p_what ;
} ;

#endif //_BwException_H