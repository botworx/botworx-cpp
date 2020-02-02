#ifndef _BwxGraph_H
#define _BwxGraph_H

#include <wx/ogl/ogl.h> // base header of OGL, includes and adjusts wx/deprecated/setup.h

class BwxGraph: public wxDiagram
{
 public:
	BwxGraph() ;
	// Add object to end of object list (if addAfter is NULL)
	// or just after addAfter.
	virtual void AddShape(wxShape *object, wxShape *addAfter = NULL);
	//
	wxShape* GetAddedShape() { return p_addedShape ; }

#if wxUSE_PROLOGIO
  bool OnShapeSave(wxExprDatabase& db, wxShape& shape, wxExpr& expr);
  bool OnShapeLoad(wxExprDatabase& db, wxShape& shape, wxExpr& expr);
#endif
  //Data Members
  wxShape* p_addedShape ;
};
////////
/*
 * A few new shape classes so we have a 1:1 mapping
 * between palette symbol and unique class
 */

class BwxRoundedRectangleShape: public wxRectangleShape
{
  DECLARE_DYNAMIC_CLASS(BwxRoundedRectangleShape)
 private:
 public:
  BwxRoundedRectangleShape(double w = 0.0, double h = 0.0);
};

class BwxDiamondShape: public wxPolygonShape
{
  DECLARE_DYNAMIC_CLASS(BwxDiamondShape)
 private:
 public:
  BwxDiamondShape(double w = 0.0, double h = 0.0);
};

#endif  // _BwxGraph_H
