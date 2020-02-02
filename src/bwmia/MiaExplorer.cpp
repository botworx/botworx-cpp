/*Botworx AI - An Artificial Intelligence Framework
Copyright (C) 2004  Kurtis Fields. See BotworxAI_License.txt for details.
*/
#include "stdafx.h"

#include <bwmia/MiaExplorer.h>
#include <bwmia/MiaState.h>
#include <bwmia/MiaAgent.h>
#include <bwmia/MiaStage.h>
//
// MiaExplorer
//
MiaExplorer::MiaExplorer(MiaState* pRoot) : p_root(pRoot) {
}
MiaExplorer::~MiaExplorer() {
}
bool MiaExplorer::doStep() {
	if(p_root->invokeStep(*this))
		return p_root->invokePostStep(*this) ;
	//else
	return false ;
}