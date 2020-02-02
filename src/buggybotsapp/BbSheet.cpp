/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include "BbSheet.h"
#include <bwvr/VrScene.h>
#include <bwvrcegui/VrCeguiGuiController.h>
/////////////////////////////////////////
BbSheet::BbSheet(VrCeguiGui *pGui) : VrCeguiWindow(pGui) {
	m_layoutFileName = "BbGui.xml" ;
}