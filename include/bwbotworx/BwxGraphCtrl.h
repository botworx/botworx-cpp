#ifndef _BwxGraphCtrl_H
#define _BwxGraphCtrl_H

#include <wx/ogl/ogl.h> // base header of OGL, includes and adjusts wx/deprecated/setup.h
class wxCommandProcessor ;

class BwxGraphCanvas;

class BwxGraph ;
class BwxShapeEvtHandler ;

class BwxGraphCtrl: public wxPanel
{
  DECLARE_DYNAMIC_CLASS(BwxGraphCtrl)
public:
	BwxGraphCtrl(wxWindow *parent = NULL, wxWindowID id = wxID_ANY,
		const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize) ;
	~BwxGraphCtrl(void) {};
	virtual void Clear() {}
	virtual BwxShapeEvtHandler* CreateEvtHandler(wxShapeEvtHandler *prev = NULL, wxShape *shape = NULL, const wxString& lab = wxEmptyString, bwHandle handle = bwAnyHandle) ;

    virtual wxCommandProcessor *GetCommandProcessor() const { return m_commandProcessor; }
    virtual void SetCommandProcessor(wxCommandProcessor *proc) { m_commandProcessor = proc; }

	BwxGraph* GetGraph() { return p_graph ; }
	BwxGraphCanvas *GetCanvas() { return p_canvas ; }
	//void OnDraw(wxDC *dc);
	wxShape *FindSelectedShape(void);
	virtual void OnShapeSelection(wxShape* pShape) { p_shapeSelection = pShape ; }
	wxShape* GetShapeSelection() { return p_shapeSelection ; }
	//Data Members
public:
	BwxGraph* p_graph;
	BwxGraphCanvas *p_canvas;
	wxCommandProcessor* m_commandProcessor ;
	//
	wxShape* p_shapeSelection ;
};

/*
 * All shape event behaviour is routed through this handler, so we don't
 * have to derive from each shape class. We plug this in to each shape.
 */

class BwxShapeEvtHandler: public wxShapeEvtHandler
{
public:
	BwxGraphCtrl* p_ctrl ;
	wxString label;
	bwHandle m_handle ;
	//BwxShapeEvtHandler(BwxGraphCtrl* pCtrl, wxShapeEvtHandler *prev = NULL, wxShape *shape = NULL, const wxString& lab = wxEmptyString)
	BwxShapeEvtHandler(BwxGraphCtrl* pCtrl, wxShapeEvtHandler *prev = NULL, wxShape *shape = NULL, const wxString& lab = wxEmptyString, bwHandle handle = bwAnyHandle)
		:	wxShapeEvtHandler(prev, shape)
	{
		p_ctrl = pCtrl ;
		label = lab;
		m_handle = handle ;
	}
	~BwxShapeEvtHandler(void)
	{
	}
	void OnLeftClick(double x, double y, int keys = 0, int attachment = 0);
	void OnBeginDragRight(double x, double y, int keys = 0, int attachment = 0);
	void OnDragRight(bool draw, double x, double y, int keys = 0, int attachment = 0);
	void OnEndDragRight(double x, double y, int keys = 0, int attachment = 0);
	void OnEndSize(double x, double y);
};

/*
 * Most user interface commands are routed through this, to give us the
 * Undo/Redo mechanism. If you add more commands, such as changing the shape colour,
 * you will need to add members to 'remember' what the user applied (for 'Do') and what the
 * previous state was (for 'Undo').
 * You can have one member for each property to be changed. Assume we also have
 * a pointer member wxShape *shape, which is set to the shape being changed.
 * Let's assume we're changing the shape colour. Our member for this is shapeColour.
 *
 * - In 'Do':
 *   o Set a temporary variable 'temp' to the current colour for 'shape'.
 *   o Change the colour to the new colour.
 *   o Set shapeColour to the _old_ colour, 'temp'.
 * - In 'Undo':
 *   o Set a temporary variable 'temp' to the current colour for 'shape'.
 *   o Change the colour to shapeColour (the old colour).
 *   o Set shapeColour to 'temp'.
 *
 * So, as long as we have a pointer to the shape being changed,
 * we only need one member variable for each property.
 *
 * PROBLEM: when an Add shape command is redone, the 'shape' pointer changes.
 * Assume, as here, that we keep a pointer to the old shape so we reuse it
 * when we recreate.
 */
#include <wx/cmdproc.h>

class BwxGraphCommand: public wxCommand
{
 protected:
  BwxGraphCtrl* p_ctrl ;
  int cmd;
  wxShape *shape; // Pointer to the shape we're acting on
  wxShape *fromShape;
  wxShape *toShape;
  wxClassInfo *shapeInfo;
  double x;
  double y;
  bool selected;
  bool display ;
  bool deleteShape;

  // Storage for property commands
  wxBrush *shapeBrush;
  wxPen *shapePen;
  wxString shapeLabel;
  bwHandle m_handle ;
 public:
  // Multi-purpose constructor for creating, deleting shapes
  BwxGraphCommand(const wxString& name, const wxString& lab, bwHandle handle, int cmd, BwxGraphCtrl *pCtrl, wxClassInfo *shapeInfo = NULL,
     double x = 0.0, double y = 0.0, bool disp = true, bool sel = false, wxShape *theShape = NULL, wxShape *fs = NULL, wxShape *ts = NULL);

  // Property-changing command constructors
  BwxGraphCommand(const wxString& name, int cmd, BwxGraphCtrl *pCtrl, wxBrush *backgroundColour, wxShape *theShape);
  BwxGraphCommand(const wxString& name, int cmd, BwxGraphCtrl *pCtrl, const wxString& lab, wxShape *theShape);

  ~BwxGraphCommand(void);

  bool Do(void);
  bool Undo(void);

  inline void SetShape(wxShape *s) { shape = s; }
  inline wxShape *GetShape(void) { return shape; }
  inline wxShape *GetFromShape(void) { return fromShape; }
  inline wxShape *GetToShape(void) { return toShape; }
  inline wxClassInfo *GetShapeInfo(void) { return shapeInfo; }
  inline bool GetSelected(void) { return selected; }

  void RemoveLines(wxShape *shape);
};

// Menu/undo/redo commands

enum
{
    OGLEDIT_ADD_SHAPE = wxID_HIGHEST,
    OGLEDIT_ADD_LINE,
    OGLEDIT_EDIT_LABEL,
    OGLEDIT_CHANGE_BACKGROUND_COLOUR,
    OGLEDIT_ABOUT = wxID_ABOUT
};

#endif
    // _BwxGraphCtrl_H
