// TestChatWx.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include <bwbotworx/BwxContext.h>
#include <bwbotworx/BwxTv.h>
#include <bwbotworx/BwxVid.h>

BwxTv::BwxTv(wxWindow *parent, const BwxContext& context) 
	: wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize), m_context(context) {	
}
//void BwxTv::AddVid(const bwString& path) {
void BwxTv::AddVid(bwHandle handle) {
	wxWindow* pParent = NULL ;
	if(p_vid) {
		if(IsSharedVid())
			return ;
		else
			pParent = p_drawer ;
	}
	else
		pParent = this ;

	//BwxVid* pVid = CreateVid(pParent, m_context, path) ;
	BwxVid* pVid = CreateVid(pParent, m_context, handle) ;
	SetIsSharedVid(pVid->IsShared()) ;
	if(pParent == this) {
		p_vid = pVid ;
		p_sizer->Add( p_vid, 1, wxEXPAND );
		p_sizer->Layout() ;
	}
	//m_vidMap[path] = pVid ;
	m_vidMap[handle] = pVid ;
}
//void BwxTv::ChangeVid(const bwString& name) {
void BwxTv::ChangeVid(bwHandle handle) {
	if(IsSharedVid())
		return ;
	//else
	if(p_vid) {
		p_sizer->Detach(p_vid) ;
		p_vid->Reparent(p_drawer) ;
	}
	//p_vid = m_vidMap[name] ;
	p_vid = m_vidMap[handle] ;
	p_vid->Reparent(this) ;
	p_sizer->Add( p_vid, 1, wxEXPAND );
	p_sizer->Layout() ;
}