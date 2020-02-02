#include "stdafx.h"

#include <wx/colordlg.h>

#include <bwbotworx/BwxGraphCtrl.h>
#include <bwbotworx/BwxGraphCanvas.h>
#include <bwbotworx/BwxGraph.h>

IMPLEMENT_DYNAMIC_CLASS(BwxGraphCtrl, wxPanel)

BwxGraphCtrl::BwxGraphCtrl(wxWindow *parent, wxWindowID id, const wxPoint& pos, const wxSize& size) 
: wxPanel(parent, id, pos, size) {
	p_graph = new BwxGraph() ;
	p_shapeSelection = NULL ;
	m_commandProcessor = new wxCommandProcessor ; 
	//int width, height;
	//GetClientSize(&width, &height);

	// Non-retained canvas
	//p_canvas = new BwxGraphCanvas(this, wxID_ANY, wxPoint(0, 0), wxSize(width, height), 0);
	p_canvas = new BwxGraphCanvas(this);
	p_canvas->SetCursor(wxCursor(wxCURSOR_HAND));

	// Give it scrollbars
	//p_canvas->SetScrollbars(20, 20, 50, 50);

	p_canvas->SetDiagram(p_graph);
	p_graph->SetCanvas(p_canvas);

	wxBoxSizer *sizerTop = new wxBoxSizer(wxVERTICAL);
	sizerTop->Add(p_canvas, 1, wxEXPAND | wxALL, 5);

	SetSizer(sizerTop);
    sizerTop->SetSizeHints(this);
    sizerTop->Fit(this);

}
BwxShapeEvtHandler* BwxGraphCtrl::CreateEvtHandler(wxShapeEvtHandler *prev, wxShape *shape, const wxString& lab, bwHandle handle) {
	return new BwxShapeEvtHandler(this, prev, shape, lab, handle) ;
}

//f6:fixme:put this in the canvas???

// Sneakily gets used for default print/preview
// as well as drawing on the screen.
/*void BwxGraphCtrl::OnDraw(wxDC *dc)
{

  // You might use THIS code if you were scaling graphics of known size to fit on the page.
  int w, h;

  // We need to adjust for the graphic size, a formula will be added
  float maxX = 900;
  float maxY = 700;
  // A better way of find the maxium values would be to search through
  // the linked list

  // Let's have at least 10 device units margin
  float marginX = 10;
  float marginY = 10;

  // Add the margin to the graphic size
  maxX += (2 * marginX);
  maxY += (2 * marginY);

  // Get the size of the DC in pixels
  dc->GetSize (&w, &h);

  // Calculate a suitable scaling factor
  float scaleX = (float) (w / maxX);
  float scaleY = (float) (h / maxY);

  // Use x or y scaling factor, whichever fits on the DC
  float actualScale = wxMin (scaleX, scaleY);

  float posX, posY;
  // Calculate the position on the DC for centring the graphic
  #if 0
     // center the drawing
      posX = (float) ((w - (200 * actualScale)) / 2.0);
      posY = (float) ((h - (200 * actualScale)) / 2.0);
  #else
     // Use defined presets
      posX = 10;
      posY = 35;
  #endif


  // Set the scale and origin
  dc->SetUserScale (actualScale, actualScale);
  dc->SetDeviceOrigin ((long) posX, (long) posY);

  // This part was added to preform the print preview and printing functions

  dc->BeginDrawing(); // Allows optimization of drawing code under MS Windows.
  if (p_graph->GetShapeList())
  {
    // wxCursor *old_cursor = NULL;
    wxObjectList::compatibility_iterator current = p_graph->GetShapeList()->GetFirst();

    while (current) // Loop through the entire list of shapes
    {
        wxShape *object = (wxShape *)current->GetData();
        if (!object->GetParent())
        {
            object->Draw(* dc); // Draw the shape onto our printing dc
        }
        current = current->GetNext();  // Procede to the next shape in the list
    }
  }
  dc->EndDrawing(); // Allows optimization of drawing code under MS Windows.
}*/

/*void BwxGraphCtrl::OnUpdate(wxView *WXUNUSED(sender), wxObject *WXUNUSED(hint))
{
  if (canvas)
    canvas->Refresh();
}*/

wxShape *BwxGraphCtrl::FindSelectedShape(void)
{
  wxObjectList::compatibility_iterator node = p_graph->GetShapeList()->GetFirst();
  while (node)
  {
    wxShape *eachShape = (wxShape *)node->GetData();
    if ((eachShape->GetParent() == NULL) && eachShape->Selected())
    {
      return eachShape;
    }
    else node = node->GetNext();
  }
  return NULL;
}
//////////////////
BwxGraphCommand::BwxGraphCommand(const wxString& name, const wxString& lab, bwHandle handle, int command, BwxGraphCtrl *pCtrl, wxClassInfo *info,
		double xx, double yy, bool disp, bool sel, wxShape *theShape, wxShape *fs, wxShape *ts)
               :wxCommand(true, name)
{
    p_ctrl = pCtrl ;
    cmd = command;
    shape = theShape;
    fromShape = fs;
    toShape = ts;
    shapeInfo = info;
	shapeLabel = lab;
	m_handle = handle ;
    shapeBrush = NULL;
    shapePen = NULL;
    x = xx;
    y = yy;
	display = disp ;
    selected = sel;
    deleteShape = false;
}

BwxGraphCommand::BwxGraphCommand(const wxString& name, int command, BwxGraphCtrl *pCtrl, wxBrush *backgroundColour, wxShape *theShape)
               :wxCommand(true, name)
{
	p_ctrl = pCtrl ;
    cmd = command;
    shape = theShape;
    fromShape = NULL;
    toShape = NULL;
    shapeInfo = NULL;
    x = 0.0;
    y = 0.0;
	display = false ;
    selected = false;
    deleteShape = false;
    shapeBrush = backgroundColour;
    shapePen = NULL;
}

BwxGraphCommand::BwxGraphCommand(const wxString& name, int command, BwxGraphCtrl *pCtrl, const wxString& lab, wxShape *theShape)
               :wxCommand(true, name)
{
	p_ctrl = pCtrl ;
    cmd = command;
    shape = theShape;
    fromShape = NULL;
    toShape = NULL;
    shapeInfo = NULL;
    x = 0.0;
    y = 0.0;
	display = false ;
    selected = false;
    deleteShape = false;
    shapeBrush = NULL;
    shapePen = NULL;
    shapeLabel = lab;
}

BwxGraphCommand::~BwxGraphCommand(void)
{
  if (shape && deleteShape)
  {
    shape->SetCanvas(NULL);
    delete shape;
  }
}

bool BwxGraphCommand::Do(void)
{
  switch (cmd)
  {
    case wxID_CUT:
    {
      if (shape)
      {
        deleteShape = true;

        shape->Select(false);

        // Generate commands to explicitly remove each connected line.
        RemoveLines(shape);

		p_ctrl->GetGraph()->RemoveShape(shape);
        if (shape->IsKindOf(CLASSINFO(wxLineShape)))
        {
          wxLineShape *lineShape = (wxLineShape *)shape;
          fromShape = lineShape->GetFrom();
          toShape = lineShape->GetTo();
        }
        shape->Unlink();

        //doc->Modify(true);
        //doc->UpdateAllViews();
      }

      break;
    }
    case OGLEDIT_ADD_SHAPE:
    {
      wxShape *theShape;
      if (shape)
        theShape = shape; // Saved from undoing the shape
      else
      {
        theShape = (wxShape *)shapeInfo->CreateObject();
        theShape->AssignNewIds();
        //theShape->SetEventHandler(new BwxShapeEvtHandler(theShape, theShape, wxEmptyString));
		theShape->SetEventHandler(p_ctrl->CreateEvtHandler(theShape, theShape, wxEmptyString, m_handle));
        theShape->SetCentreResize(false);
        theShape->SetPen(wxBLACK_PEN);
        theShape->SetBrush(wxCYAN_BRUSH);
        theShape->SetSize(60, 60);
		theShape->SetFont(g_oglNormalFont) ;
      }
      p_ctrl->GetGraph()->AddShape(theShape);
      //theShape->Show(true);
	  theShape->Show(display);

      wxClientDC dc(theShape->GetCanvas());
      theShape->GetCanvas()->PrepareDC(dc);

	if(shapeLabel != "") {
		BwxShapeEvtHandler *myHandler = (BwxShapeEvtHandler *)theShape->GetEventHandler();
		myHandler->label = shapeLabel;
		//if(display) {
			theShape->FormatText(dc, myHandler->label);
			//theShape->Draw(dc);
		//}
	}
      //theShape->Move(dc, x, y);
	  theShape->Move(dc, x, y, display);


      shape = theShape;
      deleteShape = false;

      //doc->Modify(true);
      //doc->UpdateAllViews();
      break;
    }
    case OGLEDIT_ADD_LINE:
    {
      wxShape *theShape;
	  wxLineShape *lineShape = NULL ;
      if (shape)
        theShape = shape; // Saved from undoing the line
      else
      {
        theShape = (wxShape *)shapeInfo->CreateObject();
        theShape->AssignNewIds();
        //theShape->SetEventHandler(new BwxShapeEvtHandler(theShape, theShape, wxEmptyString));
		theShape->SetEventHandler(p_ctrl->CreateEvtHandler(theShape, theShape, wxEmptyString, m_handle));
        theShape->SetPen(wxBLACK_PEN);
        theShape->SetBrush(wxRED_BRUSH);

        lineShape = (wxLineShape *)theShape;

        // Yes, you can have more than 2 control points, in which case
        // it becomes a multi-segment line.
        lineShape->MakeLineControlPoints(2);
        lineShape->AddArrow(ARROW_ARROW, ARROW_POSITION_END, 10.0, 0.0, _T("Normal arrowhead"));
      }

      p_ctrl->GetGraph()->AddShape(theShape);

      fromShape->AddLine((wxLineShape *)theShape, toShape);

      wxClientDC dc(theShape->GetCanvas());
      theShape->GetCanvas()->PrepareDC(dc);

	  if(shapeLabel != "") {
		BwxShapeEvtHandler *myHandler = (BwxShapeEvtHandler *)lineShape->GetEventHandler();
		myHandler->label = shapeLabel;
		//if(display) {
			lineShape->FormatText(dc, myHandler->label);
		//	lineShape->Draw(dc);
		//}

		//theShape->Show(true);
		//theShape->Show(display);

	}

      // It won't get drawn properly unless you move both
      // connected images
      fromShape->Move(dc, fromShape->GetX(), fromShape->GetY(), display);
      toShape->Move(dc, toShape->GetX(), toShape->GetY(), display);

      shape = theShape;
      deleteShape = false;

      //doc->Modify(true);
      //doc->UpdateAllViews();
      break;
    }
    case OGLEDIT_CHANGE_BACKGROUND_COLOUR:
    {
      if (shape)
      {
        wxClientDC dc(shape->GetCanvas());
        shape->GetCanvas()->PrepareDC(dc);

        wxBrush *oldBrush = shape->GetBrush();
        shape->SetBrush(shapeBrush);
        shapeBrush = oldBrush;
        shape->Draw(dc);

        //doc->Modify(true);
        //doc->UpdateAllViews();
      }

      break;
    }
    case OGLEDIT_EDIT_LABEL:
    {
      if (shape)
      {
        BwxShapeEvtHandler *myHandler = (BwxShapeEvtHandler *)shape->GetEventHandler();
        wxString oldLabel(myHandler->label);
        myHandler->label = shapeLabel;
        shapeLabel = oldLabel;

        wxClientDC dc(shape->GetCanvas());
        shape->GetCanvas()->PrepareDC(dc);

        shape->FormatText(dc, /* (char*) (const char*) */ myHandler->label);
        shape->Draw(dc);

        //doc->Modify(true);
        //doc->UpdateAllViews();
      }

      break;
    }
  }
  return true;
}

bool BwxGraphCommand::Undo(void)
{
  switch (cmd)
  {
    case wxID_CUT:
    {
      if (shape)
      {
        p_ctrl->GetGraph()->AddShape(shape);
        //shape->Show(true);
		shape->Show(display);

        if (shape->IsKindOf(CLASSINFO(wxLineShape)))
        {
          wxLineShape *lineShape = (wxLineShape *)shape;

          fromShape->AddLine(lineShape, toShape);
        }
        if (selected)
          shape->Select(true);

        deleteShape = false;
      }
      //doc->Modify(true);
      //doc->UpdateAllViews();
      break;
    }
    case OGLEDIT_ADD_SHAPE:
    case OGLEDIT_ADD_LINE:
    {
      if (shape)
      {
        wxClientDC dc(shape->GetCanvas());
        shape->GetCanvas()->PrepareDC(dc);

        shape->Select(false, &dc);
        p_ctrl->GetGraph()->RemoveShape(shape);
        shape->Unlink();
        deleteShape = true;
      }
      //doc->Modify(true);
      //doc->UpdateAllViews();
      break;
    }
    case OGLEDIT_CHANGE_BACKGROUND_COLOUR:
    {
      if (shape)
      {
        wxClientDC dc(shape->GetCanvas());
        shape->GetCanvas()->PrepareDC(dc);

        wxBrush *oldBrush = shape->GetBrush();
        shape->SetBrush(shapeBrush);
        shapeBrush = oldBrush;
        shape->Draw(dc);

        //doc->Modify(true);
        //doc->UpdateAllViews();
      }
      break;
    }
    case OGLEDIT_EDIT_LABEL:
    {
      if (shape)
      {
        BwxShapeEvtHandler *myHandler = (BwxShapeEvtHandler *)shape->GetEventHandler();
        wxString oldLabel(myHandler->label);
        myHandler->label = shapeLabel;
        shapeLabel = oldLabel;

        wxClientDC dc(shape->GetCanvas());
        shape->GetCanvas()->PrepareDC(dc);

        shape->FormatText(dc, /* (char*) (const char*) */ myHandler->label);
        shape->Draw(dc);

        //doc->Modify(true);
        //doc->UpdateAllViews();
      }

      break;
    }
  }
  return true;
}

// Remove each individual line connected to a shape by sending a command.
void BwxGraphCommand::RemoveLines(wxShape *shape)
{
  wxObjectList::compatibility_iterator node = shape->GetLines().GetFirst();
  while (node)
  {
    wxLineShape *line = (wxLineShape *)node->GetData();
    p_ctrl->GetCommandProcessor()->Submit(new BwxGraphCommand(_T("Cut"), _T(""), bwAnyHandle, wxID_CUT, p_ctrl, NULL, 0.0, 0.0, line->Selected(), line));

    node = shape->GetLines().GetFirst();
  }
}

/*
 * BwxShapeEvtHandler: an event handler class for all shapes
 */

void BwxShapeEvtHandler::OnLeftClick(double WXUNUSED(x), double WXUNUSED(y), int keys, int WXUNUSED(attachment))
{
  wxClientDC dc(GetShape()->GetCanvas());
  GetShape()->GetCanvas()->PrepareDC(dc);

  if (keys == 0)
  {
    // Selection is a mind the library knows about
    if (GetShape()->Selected())
    {
      GetShape()->Select(false, &dc);
      GetShape()->GetCanvas()->Redraw(dc); // Redraw because bits of objects will be are missing
    }
    else
    {
      // Ensure no other shape is selected, to simplify Undo/Redo code
      bool redraw = false;
      wxObjectList::compatibility_iterator node = GetShape()->GetCanvas()->GetDiagram()->GetShapeList()->GetFirst();
      while (node)
      {
        wxShape *eachShape = (wxShape *)node->GetData();
        if (eachShape->GetParent() == NULL)
        {
          if (eachShape->Selected())
          {
            eachShape->Select(false, &dc);
            redraw = true;
          }
        }
        node = node->GetNext();
      }
      GetShape()->Select(true, &dc);
      if (redraw)
        GetShape()->GetCanvas()->Redraw(dc);
	  p_ctrl->OnShapeSelection(GetShape()) ;
    }
  }
  else if (keys & KEY_CTRL)
  {
    // Do something for CONTROL
  }
  else
  {
/*#if wxUSE_STATUSBAR
    wxGetApp().frame->SetStatusText(label);
#endif // wxUSE_STATUSBAR*/
  }
}

/*
 * Implement connection of two shapes by right-dragging between them.
 */

void BwxShapeEvtHandler::OnBeginDragRight(double x, double y, int WXUNUSED(keys), int attachment)
{
  // Force attachment to be zero for now. Eventually we can deal with
  // the actual attachment point, e.g. a rectangle side if attachment mode is on.
  attachment = 0;

  wxClientDC dc(GetShape()->GetCanvas());
  GetShape()->GetCanvas()->PrepareDC(dc);

  wxPen dottedPen(*wxBLACK, 1, wxDOT);
  dc.SetLogicalFunction(OGLRBLF);
  dc.SetPen(dottedPen);
  double xp, yp;
  GetShape()->GetAttachmentPosition(attachment, &xp, &yp);
  dc.DrawLine((long) xp, (long) yp, (long) x, (long) y);
  GetShape()->GetCanvas()->CaptureMouse();
}

void BwxShapeEvtHandler::OnDragRight(bool WXUNUSED(draw), double x, double y, int WXUNUSED(keys), int attachment)
{
  // Force attachment to be zero for now
  attachment = 0;

  wxClientDC dc(GetShape()->GetCanvas());
  GetShape()->GetCanvas()->PrepareDC(dc);

  wxPen dottedPen(*wxBLACK, 1, wxDOT);
  dc.SetLogicalFunction(OGLRBLF);
  dc.SetPen(dottedPen);
  double xp, yp;
  GetShape()->GetAttachmentPosition(attachment, &xp, &yp);
  dc.DrawLine((long) xp, (long) yp, (long) x, (long) y);
}

void BwxShapeEvtHandler::OnEndDragRight(double x, double y, int WXUNUSED(keys), int WXUNUSED(attachment))
{
  GetShape()->GetCanvas()->ReleaseMouse();
  BwxGraphCanvas *canvas = (BwxGraphCanvas *)GetShape()->GetCanvas();
  BwxGraph *graph = (BwxGraph*)canvas->GetDiagram() ;

  // Check if we're on an object
  int new_attachment;
  wxShape *otherShape = canvas->FindFirstSensitiveShape(x, y, &new_attachment, OP_DRAG_RIGHT);

  if (otherShape && !otherShape->IsKindOf(CLASSINFO(wxLineShape)))
  {
    p_ctrl->GetCommandProcessor()->Submit(
      new BwxGraphCommand(_T("wxLineShape"), _T(""), bwAnyHandle, OGLEDIT_ADD_LINE, p_ctrl, CLASSINFO(wxLineShape),
      0.0, 0.0, true, true, NULL, GetShape(), otherShape));
  }
}

void BwxShapeEvtHandler::OnEndSize(double WXUNUSED(x), double WXUNUSED(y))
{
  wxClientDC dc(GetShape()->GetCanvas());
  GetShape()->GetCanvas()->PrepareDC(dc);

  //f6:fixme:bombing on control points not having font ...???
  GetShape()->FormatText(dc, /* (char*) (const char*) */ label);

}
