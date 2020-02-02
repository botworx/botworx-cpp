#include "stdafx.h"

// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif
#include "wx/txtstrm.h"
#ifdef __WXMAC__
#include "wx/filename.h"
#endif

#if !wxUSE_DOC_VIEW_ARCHITECTURE
#error You must set wxUSE_DOC_VIEW_ARCHITECTURE to 1 in setup.h!
#endif

#include <bwbotworx/BwxScintillaDoc.h>
#include <bwbotworx/BwxScintillaView.h>

namespace bwxscintilla {

//IMPLEMENT_DYNAMIC_CLASS(BwxScintillaDoc, wxDocument)
IMPLEMENT_DYNAMIC_CLASS(BwxScintillaDoc, BwxDocument)

// Since text windows have their own method for saving to/loading from files,
// we override OnSave/OpenDocument instead of Save/LoadObject
bool BwxScintillaDoc::OnSaveDocument(const wxString& filename)
{
    BwxScintillaView *view = (BwxScintillaView *)GetFirstView();

    if (!view->m_edit->SaveFile(filename))
        return false;
    Modify(false);
	SetDocumentSaved() ;
#ifdef __WXMAC__
    wxFileName fn(filename) ;
    fn.MacSetDefaultTypeAndCreator() ;
#endif
    return true;
}

bool BwxScintillaDoc::OnOpenDocument(const wxString& filename)
{
    BwxScintillaView *view = (BwxScintillaView *)GetFirstView();
    if (!view->m_edit->LoadFile(filename))
        return false;

    SetFilename(filename, true);
    Modify(false);
    UpdateAllViews();
    return true;
}

bool BwxScintillaDoc::IsModified(void) const
{
    BwxScintillaView *view = (BwxScintillaView *)GetFirstView();
    if (view)
    {
		return (wxDocument::IsModified() || view->m_edit->IsModified());
		return false ;
    }
    else
        return wxDocument::IsModified();
}

void BwxScintillaDoc::Modify(bool mod)
{
    BwxScintillaView *view = (BwxScintillaView *)GetFirstView();

    wxDocument::Modify(mod);

    if (!mod && view && view->m_edit)
        view->m_edit->SetSavePoint(); //goofy way to clear modified flag
}
} ; //namespace bwxscintilla
