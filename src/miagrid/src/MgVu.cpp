/*Botworx AI - An Artificial Intelligence Framework
Copyright (C) 2004  Kurtis Fields. See BotworxAI_License.txt for details.
*/
#include "stdafx.h"

#include "MgVu.h"
#include "MgScenario.h"
#include "MgScene.h"
//
class MgVuRenderer : public wxGridCellStringRenderer
{
public:
    virtual void Draw(wxGrid& grid,
                      wxGridCellAttr& attr,
                      wxDC& dc,
                      const wxRect& rect,
                      int row, int col,
                      bool isSelected)
	{
		wxGridCellStringRenderer::Draw(grid, attr, dc, rect, row, col, isSelected);

		dc.SetPen(*wxGREEN_PEN);
		dc.SetBrush(*wxTRANSPARENT_BRUSH);
		dc.DrawEllipse(rect);
	}

};
//
MgVu::MgVu(MgEntity *pEntity) : BwActor(pEntity), p_entity(pEntity) {
	p_savedRenderer = NULL ;
}
void MgVu::doCreate(const BwPartInfo& info) {
	BwActor::doCreate(info) ;
	m_savedPos = p_entity->getPos() ;
	//create_renderer() ;
	updateScene() ;
}
void MgVu::create_renderer() {
	p_renderer = new MgVuRenderer() ;
	mgPos pos = p_entity->getPos() ;
	p_savedRenderer = MgScene::singleton().get_grid()->GetCellRenderer(pos.x, pos.y);
	MgScene::singleton().get_grid()->SetCellRenderer(pos.x, pos.y, p_renderer);
}
void MgVu::doPostStep(BwStepper& stepper) {
	updateScene() ;
}
void MgVu::updateScene() {
	if(p_entity->hasMoved()) {
		mgPos pos = p_entity->getPos() ;
		//MgScene::singleton().get_grid()->SetCellValue(pos.x, pos.y, wxString("MOUSE")) ;
		MgScene::singleton().get_grid()->SetCellValue(pos.x, pos.y, wxString(p_entity->getName().c_str())) ;
		MgScene::singleton().get_grid()->SetCellValue(m_savedPos.x, m_savedPos.y, wxString("")) ;
		m_savedPos = pos ;
	}
}