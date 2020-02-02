// TestChatWx.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include <bwbotworx/BwxContext.h>
#include <bwbotworx/BwxVid.h>

//BwxVid::BwxVid(wxWindow *parent, const BwxContext& context, const bwString& name) : wxPanel(parent) {
BwxVid::BwxVid(wxWindow *parent, const BwxContext& context, bwHandle handle) : wxPanel(parent) {
	m_isShared = false ;
}
void BwxVid::FillListBox(wxListBox* pListBox, const bwString& text) {
	pListBox->Clear() ;
	char buffer[256] ;
	const char* read = text.c_str() ;
	char* write = buffer ;
	while(*read != 0) {
		if(*read == '\n') {
			read++ ;
			*write = 0 ;
			pListBox->Append(wxString(buffer)) ;
			write = buffer ;
			*buffer = 0 ;
			continue ;
		}
		*write++ = *read++ ;
	}
}
