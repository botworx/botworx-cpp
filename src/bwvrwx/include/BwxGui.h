/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _BwxGui_H
#define _BwxGui_H

#include <bwkernel/BwPart.h>

class wxFrame ;
class BwxDeckFrame ;
class BwxUser ;

class BwxGui : public BwPart {
public:
    BwxGui(BwxUser *pUser) ;
    virtual ~BwxGui() ;
    virtual void doCreate(const BwPartInfo& info) ;
	virtual void bind() ;
	virtual void unbind() ;
	//
	void setSheet(wxFrame* pFrame) ;
	BwxDeckFrame* getControlFrame() { return p_controlFrame ; }
	//////////////////
	/*Data Members*/
protected:
	BwxUser *p_user ;
	BwxDeckFrame *p_controlFrame ;
	wxFrame *p_sheet ;
};
#endif //_BwxGui_H