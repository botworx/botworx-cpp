/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <bwvr/VrNodeKit.h>
#include <bwvr/VrNode.h>

VrNodeKit::VrNodeKit(BwPart *pPart) : BwKit(pPart) {
}
//
void VrDefaultNodeKit::collide(VrNode *pCollider) {
	p_root->collide(pCollider) ;
}