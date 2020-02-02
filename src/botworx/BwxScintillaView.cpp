#include "stdafx.h"

#include <bwbotworx/BwxScintillaDoc.h>
#include <bwbotworx/BwxScintillaView.h>
//
#include <bwbotworx/BwxAppFrame.h>
//
namespace bwxscintilla {

IMPLEMENT_DYNAMIC_CLASS(BwxScintillaView, wxView)

bool BwxScintillaView::OnCreate(wxDocument *doc, long WXUNUSED(flags) )
{
    m_frame = wxGetApp().GetAppFrame()->CreateChildFrame(doc, this, false);
    
    int width, height;
    m_frame->GetClientSize(&width, &height);
	m_edit = new MyEdit(this, m_frame, wxPoint(0, 0), wxSize(width, height), wxTE_MULTILINE);

	//Face *face = new Face("MyFace", m_edit, m_frame) ;
    //m_frame->SetTitle(_T("BwxScintillaView"));
    
#ifdef __X__
    // X seems to require a forced resize
    int x, y;
    m_frame->GetSize(&x, &y);
    m_frame->SetSize(wxDefaultCoord, wxDefaultCoord, x, y);
#endif
    
    m_frame->Show(true);
    Activate(true);
    
    return true;
}

// Handled by wxTextWindow
void BwxScintillaView::OnDraw(wxDC *WXUNUSED(dc) )
{
}

void BwxScintillaView::OnUpdate(wxView *WXUNUSED(sender), wxObject *WXUNUSED(hint) )
{
}

bool BwxScintillaView::OnClose(bool deleteWindow)
{
    if (!GetDocument()->Close())
        return false;
    
    Activate(false);
    
    if (deleteWindow)
    {
        delete m_frame;
        return true;
    }
    return true;
}

MyEdit::MyEdit(wxView *v, wxFrame *m_frame, const wxPoint& pos, const wxSize& size, const long style):
    wxStyledTextCtrl(m_frame, wxID_ANY, pos, size, style)
{
    view = v;
}

} ; //end namespace bwxscintilla
