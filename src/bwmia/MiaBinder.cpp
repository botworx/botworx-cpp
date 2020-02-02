/*Botworx AI - An Artificial Intelligence Framework
Copyright (C) 2004  Kurtis Fields. See BotworxAI_License.txt for details.
*/
#include "stdafx.h"

#include <bwmia/MiaBinder.h>
#include <bwmia/MiaMethod.h>
//
//MiaBinder
//
MiaPrinter& operator<<(MiaPrinter &printer, MiaBinder& data) {
	printer << "[ " ;
	for(int i = 0 ; i < data.m_size ; ++i) {
		MiaBinding& binding = data.m_bindings[i] ;
		printer << "[ " << *binding.getSymbol() ;
		printer << " = " << *binding.getValue() << " ]" ;
	}
	printer << " ]" << endl ;
	return printer ;
}

