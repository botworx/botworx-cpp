/////////////////////////////////////////////////////////////////////////////
// Name:        view.h
// Purpose:     View classes
// Author:      Julian Smart
// Modified by:
// Created:     04/01/98
// RCS-ID:      $Id: view.h,v 1.7 2004/05/27 18:07:04 ABX Exp $
// Copyright:   (c) Julian Smart
// Licence:     wxWindows license
/////////////////////////////////////////////////////////////////////////////

#ifndef _BwxScintillaView_H
#define _BwxScintillaView_H

#include <wx/docview.h>
#include <wx/stc/stc.h>

namespace bwxscintilla {

class MyEdit: public wxStyledTextCtrl
{
public:
    wxView *view;
    
    MyEdit(wxView *v, wxFrame *frame, const wxPoint& pos, const wxSize& size, const long style);
};

class BwxScintillaView: public wxView
{
    DECLARE_DYNAMIC_CLASS(BwxScintillaView)
private:
public:
    wxFrame *m_frame;
    MyEdit *m_edit;
    BwxScintillaView(): wxView() { 
		m_frame = (wxFrame *) NULL; 
		m_edit = (MyEdit *) NULL; 
	}
    ~BwxScintillaView(void) {}
    
    bool OnCreate(wxDocument *doc, long flags);
    void OnDraw(wxDC *dc);
    void OnUpdate(wxView *sender, wxObject *hint = (wxObject *) NULL);
    bool OnClose(bool deleteWindow = true);
};

} ; //namespace bwxscintilla
#endif
