#include "stdafx.h"

#include <bwbotworx/BwxGraph.h>
#include <bwbotworx/BwxGraphCanvas.h>

BwxGraph::BwxGraph(void) { 
	p_addedShape = NULL ;
}
void BwxGraph::AddShape(wxShape *object, wxShape *addAfter) {
	p_addedShape = object ;
	wxDiagram::AddShape(object, addAfter) ;
}

/*
 * Diagram
 */

#if wxUSE_PROLOGIO

bool BwxGraph::OnShapeSave(wxExprDatabase& db, wxShape& shape, wxExpr& expr)
{
  wxDiagram::OnShapeSave(db, shape, expr);
  BwxShapeEvtHandler *handler = (BwxShapeEvtHandler *)shape.GetEventHandler();
  expr.AddAttributeValueString(_T("label"), handler->label);
  return true;
}

bool BwxGraph::OnShapeLoad(wxExprDatabase& db, wxShape& shape, wxExpr& expr)
{
  wxDiagram::OnShapeLoad(db, shape, expr);
  wxChar *label = NULL;
  expr.AssignAttributeValue(_T("label"), &label);
  BwxShapeEvtHandler *handler = new BwxShapeEvtHandler(&shape, &shape, wxString(label));
  shape.SetEventHandler(handler);

  if (label)
    delete[] label;
  return true;
}

#endif

/*
 * New shapes
 */

IMPLEMENT_DYNAMIC_CLASS(BwxRoundedRectangleShape, wxRectangleShape)

BwxRoundedRectangleShape::BwxRoundedRectangleShape(double w, double h):
 wxRectangleShape(w, h)
{
  // 0.3 of the smaller rectangle dimension
  SetCornerRadius((double) -0.3);
}

IMPLEMENT_DYNAMIC_CLASS(BwxDiamondShape, wxPolygonShape)

BwxDiamondShape::BwxDiamondShape(double w, double h):
  wxPolygonShape()
{
  // wxPolygonShape::SetSize relies on the shape having non-zero
  // size initially.
  if (w == 0.0)
    w = 60.0;
  if (h == 0.0)
    h = 60.0;

  wxList *thePoints = new wxList;
  wxRealPoint *point = new wxRealPoint(0.0, (-h/2.0));
  thePoints->Append((wxObject*) point);

  point = new wxRealPoint((w/2.0), 0.0);
  thePoints->Append((wxObject*) point);

  point = new wxRealPoint(0.0, (h/2.0));
  thePoints->Append((wxObject*) point);

  point = new wxRealPoint((-w/2.0), 0.0);
  thePoints->Append((wxObject*) point);

  Create(thePoints);
}

