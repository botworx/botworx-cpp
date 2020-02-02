// TestChatWx.cpp : Defines the entry point for the application.
//

#include "stdafx.h"

#include <wx/toolbar.h>

#include <bwbotworx/BwxContext.h>
#include <bwbotworx/BwxStateGraphVid.h>
#include <bwbotworx/BwxStateGraphCtrl.h>
#include <bwbotworx/BwxGraphCanvas.h>

#include <bwwx/resource/icon/xpm/alignl.xpm>
#include <bwwx/resource/icon/xpm/alignr.xpm>
#include <bwwx/resource/icon/xpm/alignt.xpm>
#include <bwwx/resource/icon/xpm/alignb.xpm>
#include <bwwx/resource/icon/xpm/horiz.xpm>
#include <bwwx/resource/icon/xpm/vert.xpm>
#include <bwwx/resource/icon/xpm/copysize.xpm>
#include <bwwx/resource/icon/xpm/linearrow.xpm>
#include <bwwx/resource/icon/xpm/newpoint.xpm>
#include <bwwx/resource/icon/xpm/cutpoint.xpm>
#include <bwwx/resource/icon/xpm/straight.xpm>

#define ID_WINDOW_POINT_SIZE_COMBOBOX     301
#define ID_WINDOW_ZOOM_COMBOBOX           302

#define GRAPH_TOOLBAR_ALIGNL            500
#define GRAPH_TOOLBAR_ALIGNR            501
#define GRAPH_TOOLBAR_ALIGNB            502
#define GRAPH_TOOLBAR_ALIGNT            503
#define GRAPH_TOOLBAR_ALIGN_HORIZ       504
#define GRAPH_TOOLBAR_ALIGN_VERT        505
#define GRAPH_TOOLBAR_COPY_SIZE         506
#define GRAPH_TOOLBAR_LINE_ARROW        507
#define GRAPH_TOOLBAR_NEW_POINT         508
#define GRAPH_TOOLBAR_CUT_POINT         509
#define GRAPH_TOOLBAR_STRAIGHTEN        510

BEGIN_EVENT_TABLE(BwxStateGraphVid, BwxVid)
EVT_COMBOBOX(ID_WINDOW_ZOOM_COMBOBOX, BwxStateGraphVid::OnZoomSel)
END_EVENT_TABLE()

BwxStateGraphVid::BwxStateGraphVid(wxWindow *parent, const BwxContext& context) : BwxVid(parent, context) {
	p_sizer = new wxBoxSizer(wxVERTICAL) ;
	SetAutoLayout( true );
	SetSizer( p_sizer );
	m_stateGraphCtrl = new BwxStateGraphCtrl(this, context) ;
	CreateGraphToolBar() ;
	p_sizer->Add(m_graphToolBar,0, wxEXPAND) ;
	p_sizer->Add(m_stateGraphCtrl,1, wxEXPAND) ;
	p_sizer->Fit(this) ;
}
void BwxStateGraphVid::Clear() {
	m_stateGraphCtrl->Clear() ;
}
void BwxStateGraphVid::CreateGraphToolBar()
{
    // Create the actual toolbar
    m_graphToolBar = new wxToolBar(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTB_HORIZONTAL|wxNO_BORDER|wxTB_FLAT);

    wxBitmap* bitmaps[11];

    bitmaps[0] = new wxBitmap( alignl_xpm );
    bitmaps[1] = new wxBitmap( alignr_xpm );
    bitmaps[2] = new wxBitmap( alignt_xpm );
    bitmaps[3] = new wxBitmap( alignb_xpm );
    bitmaps[4] = new wxBitmap( horiz_xpm );
    bitmaps[5] = new wxBitmap( vert_xpm );
    bitmaps[6] = new wxBitmap( copysize_xpm );
    bitmaps[7] = new wxBitmap( linearrow_xpm );
    bitmaps[8] = new wxBitmap( newpoint_xpm );
    bitmaps[9] = new wxBitmap( cutpoint_xpm );
    bitmaps[10] = new wxBitmap( straight_xpm );

    m_graphToolBar->AddTool(GRAPH_TOOLBAR_ALIGNL, *bitmaps[0], wxNullBitmap, false, wxDefaultCoord, wxDefaultCoord, NULL, _T("Align left"));
    m_graphToolBar->AddTool(GRAPH_TOOLBAR_ALIGNR, *bitmaps[1], wxNullBitmap, false, wxDefaultCoord, wxDefaultCoord, NULL, _T("Align right"));
    m_graphToolBar->AddTool(GRAPH_TOOLBAR_ALIGNT, *bitmaps[2], wxNullBitmap, false, wxDefaultCoord, wxDefaultCoord, NULL, _T("Align top"));
    m_graphToolBar->AddTool(GRAPH_TOOLBAR_ALIGNB, *bitmaps[3], wxNullBitmap, false, wxDefaultCoord, wxDefaultCoord, NULL, _T("Align bottom"));
    m_graphToolBar->AddTool(GRAPH_TOOLBAR_ALIGN_HORIZ, *bitmaps[4], wxNullBitmap, false, wxDefaultCoord, wxDefaultCoord, NULL, _T("Align horizontally"));
    m_graphToolBar->AddTool(GRAPH_TOOLBAR_ALIGN_VERT, *bitmaps[5], wxNullBitmap, false, wxDefaultCoord, wxDefaultCoord, NULL, _T("Align vertically"));
    m_graphToolBar->AddTool(GRAPH_TOOLBAR_COPY_SIZE, *bitmaps[6], wxNullBitmap, false, wxDefaultCoord, wxDefaultCoord, NULL, _T("Copy size"));
    m_graphToolBar->AddSeparator();
    m_graphToolBar->AddTool(GRAPH_TOOLBAR_LINE_ARROW, *bitmaps[7], wxNullBitmap, true, wxDefaultCoord, wxDefaultCoord, NULL, _T("Toggle arrow"));
    m_graphToolBar->AddTool(GRAPH_TOOLBAR_NEW_POINT, *bitmaps[8], wxNullBitmap, false, wxDefaultCoord, wxDefaultCoord, NULL, _T("New line point"));
    m_graphToolBar->AddTool(GRAPH_TOOLBAR_CUT_POINT, *bitmaps[9], wxNullBitmap, false, wxDefaultCoord, wxDefaultCoord, NULL, _T("Cut line point"));
    m_graphToolBar->AddTool(GRAPH_TOOLBAR_STRAIGHTEN, *bitmaps[10], wxNullBitmap, false, wxDefaultCoord, wxDefaultCoord, NULL, _T("Straighten lines"));

    m_graphToolBar->Realize();

    int i;
    for (i = 0; i < 11; ++i)
        delete bitmaps[i];

    // Create a combobox for point size
    int maxPointSize = 40;
    wxString *pointSizes = new wxString[maxPointSize];
    for (i = 1; i <= maxPointSize; ++i)
    {
        pointSizes[i-1].Printf(_T("%d"), i);
    }

    int controlX = 260;
    int pointSizeW = 40;
    int pointSizeH = 18;
    int zoomW = 60;
    int zoomH = 18;
#ifdef __WXMOTIF__
    controlX += 75;
    pointSizeW = 60;
    pointSizeH = 22;
    zoomW = 60;
    zoomH = 22;
#endif

    m_pointSizeComboBox = new wxComboBox(m_graphToolBar, ID_WINDOW_POINT_SIZE_COMBOBOX,
        wxEmptyString, wxPoint(controlX, 1), wxSize(pointSizeW, pointSizeH), maxPointSize, pointSizes);
    delete[] pointSizes;

#ifdef __WXGTK__
    m_graphToolBar->AddControl(m_pointSizeComboBox);
#endif

    m_pointSizeComboBox->SetSelection(10 - 1);

    // Create a combobox for zooming
    int maxZoom = 200;
    int minZoom = 5;
    int increment = 5;
    int noStrings = (maxZoom - minZoom)/5 ;
    wxString *zoomStrings = new wxString[noStrings];
    for (i = 0; i < noStrings; ++i)
    {
        zoomStrings[noStrings - i - 1].Printf(_T("%d%%"), (i*increment + minZoom));
    }

    controlX += pointSizeW + 10;

    m_zoomComboBox = new wxComboBox(m_graphToolBar, ID_WINDOW_ZOOM_COMBOBOX,
        wxEmptyString, wxPoint(controlX, 1), wxSize(zoomW, zoomH), noStrings, zoomStrings);
    delete[] zoomStrings;

#ifdef __WXGTK__
    m_graphToolBar->AddControl(m_zoomComboBox);
#endif

    // i = (zoom - minZoom)/increment
    // index = noStrings - i - 1
    // 100%
    i = (100 - minZoom)/increment;
    m_zoomComboBox->SetSelection(noStrings - i - 1);
}
void BwxStateGraphVid::OnZoomSel(wxCommandEvent& event)
{
    int maxZoom = 200;
    int minZoom = 5;
    int inc = 5;
    int noStrings = (maxZoom - minZoom)/inc ;

    wxComboBox* combo = (wxComboBox*) event.GetEventObject();
    wxASSERT( combo );

    int scale = (int) ((noStrings - combo->GetSelection() - 1)*inc + minZoom);

    //canvas->SetScale((double) (scale/100.0), (double) (scale/100.0));
	m_stateGraphCtrl->GetCanvas()->SetScale((double) (scale/100.0), (double) (scale/100.0));
    m_stateGraphCtrl->GetCanvas()->Refresh();
}
