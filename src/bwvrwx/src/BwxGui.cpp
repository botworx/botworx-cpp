/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <BwxGui.h>
#include <BwxUser.h>
#include <BwxDeckFrame.h>

BwxGui::BwxGui(BwxUser *pUser) : BwPart(pUser), p_user(pUser) {
}
BwxGui::~BwxGui() {
}
void BwxGui::doCreate(const BwPartInfo& info) {
	BwPart::doCreate(info) ;
	p_controlFrame = new BwxDeckFrame(p_sheet) ;
	p_controlFrame->Show(true);
}
void BwxGui::bind() {
}
void BwxGui::unbind() {
	p_controlFrame->Close() ;
	delete p_controlFrame ;
}
void BwxGui::setSheet(wxFrame* pFrame) {
	p_sheet = pFrame ;
}