#ifndef _BwxGraphCanvas_H
#define _BwxGraphCanvas_H

#include <wx/ogl/ogl.h>

class BwxGraphCanvas: public wxShapeCanvas
{
 DECLARE_DYNAMIC_CLASS(BwxGraphCanvas)
 protected:
 public:
  BwxGraphCanvas(wxWindow *parent = NULL, wxWindowID id = wxID_ANY,
            const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize,
            long style = wxRETAINED | wxVSCROLL | wxHSCROLL);
  ~BwxGraphCanvas(void);

  void OnMouseEvent(wxMouseEvent& event);
  void OnPaint(wxPaintEvent& event);

  virtual void OnLeftClick(double x, double y, int keys = 0);
  virtual void OnRightClick(double x, double y, int keys = 0);

  virtual void OnDragLeft(bool draw, double x, double y, int keys=0); // Erase if draw false
  virtual void OnBeginDragLeft(double x, double y, int keys=0);
  virtual void OnEndDragLeft(double x, double y, int keys=0);

  virtual void OnDragRight(bool draw, double x, double y, int keys=0); // Erase if draw false
  virtual void OnBeginDragRight(double x, double y, int keys=0);
  virtual void OnEndDragRight(double x, double y, int keys=0);

DECLARE_EVENT_TABLE()
};

#endif
    // _BwxGraphCanvas_H
