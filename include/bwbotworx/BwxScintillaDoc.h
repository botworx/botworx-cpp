/////////////////////////////////////////////////////////////////////////////
// Name:        doc.h
// Purpose:     Document classes
// Author:      Julian Smart
// Modified by:
// Created:     04/01/98
// RCS-ID:      $Id: doc.h,v 1.9 2004/10/06 20:31:59 ABX Exp $
// Copyright:   (c) Julian Smart
// Licence:     wxWindows license
/////////////////////////////////////////////////////////////////////////////

#ifndef _BwxScintillaDoc_H
#define _BwxScintillaDoc_H

/*#include "wx/docview.h"
#include "wx/cmdproc.h"*/
#include "BwxDocument.h"

namespace bwxscintilla {

//class BwxScintillaDoc: public wxDocument
class BwxScintillaDoc: public BwxDocument
{
    DECLARE_DYNAMIC_CLASS(BwxScintillaDoc)
private:
public:
/*
wxSTD ostream& SaveObject(wxSTD ostream& stream);
wxSTD istream& LoadObject(wxSTD istream& stream);
    */
    virtual bool OnSaveDocument(const wxString& filename);
    virtual bool OnOpenDocument(const wxString& filename);
    virtual bool IsModified(void) const;
    virtual void Modify(bool mod);

    BwxScintillaDoc(void) {}
    ~BwxScintillaDoc(void) {}
};

}; //namespace bwxscintilla

#endif
