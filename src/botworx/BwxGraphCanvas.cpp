#include "stdafx.h"

#include <bwbotworx/BwxGraphCtrl.h>
#include <bwbotworx/BwxGraphCanvas.h>


/*
 * Window implementations
 */
IMPLEMENT_DYNAMIC_CLASS(BwxGraphCanvas, wxShapeCanvas)

BEGIN_EVENT_TABLE(BwxGraphCanvas, wxShapeCanvas)
    EVT_MOUSE_EVENTS(BwxGraphCanvas::OnMouseEvent)
    EVT_PAINT(BwxGraphCanvas::OnPaint)
END_EVENT_TABLE()

// Define a constructor for my canvas
BwxGraphCanvas::BwxGraphCanvas(wxWindow *parent, wxWindowID id, const wxPoint& pos,
    const wxSize& size, long style):
 wxShapeCanvas(parent, id, pos, size, style)
{
	SetBackgroundColour(*wxWHITE);
	SetVirtualSize(wxSize(2048, 2048)) ;
}

BwxGraphCanvas::~BwxGraphCanvas(void)
{
}

void BwxGraphCanvas::OnLeftClick(double x, double y, int WXUNUSED(keys))
{
}

void BwxGraphCanvas::OnRightClick(double WXUNUSED(x), double WXUNUSED(y), int WXUNUSED(keys))
{
}

void BwxGraphCanvas::OnDragLeft(bool WXUNUSED(draw), double WXUNUSED(x), double WXUNUSED(y), int WXUNUSED(keys))
{
}

void BwxGraphCanvas::OnBeginDragLeft(double WXUNUSED(x), double WXUNUSED(y), int WXUNUSED(keys))
{
}

void BwxGraphCanvas::OnEndDragLeft(double WXUNUSED(x), double WXUNUSED(y), int WXUNUSED(keys))
{
}

void BwxGraphCanvas::OnDragRight(bool WXUNUSED(draw), double WXUNUSED(x), double WXUNUSED(y), int WXUNUSED(keys))
{
}

void BwxGraphCanvas::OnBeginDragRight(double WXUNUSED(x), double WXUNUSED(y), int WXUNUSED(keys))
{
}

void BwxGraphCanvas::OnEndDragRight(double WXUNUSED(x), double WXUNUSED(y), int WXUNUSED(keys))
{
}

void BwxGraphCanvas::OnMouseEvent(wxMouseEvent& event)
{
    wxShapeCanvas::OnMouseEvent(event);
}

void BwxGraphCanvas::OnPaint(wxPaintEvent& event)
{
//  if (GetDiagram())
    wxShapeCanvas::OnPaint(event);
}
