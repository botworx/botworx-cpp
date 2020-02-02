/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _VrGridLayout_H
#define _VrGridLayout_H

#include <bwvr/VrLinearLayout.h>

class VrGridLayout : public VrColumnLayout {
public:
	VrGridLayout(VrGroup *pGroup) ;
	virtual bwString getClassName() { return "VrGridLayout" ; }
	virtual void addModel(VrModel *pModel) ;

	void setSpacing(const bwSize3& spacing) {
		VrLayout::setSpacing(spacing) ; //TODO:?
		//m_colSpacing = colSpacing ;
		m_colSpacing = spacing[1] ;
	}
	void setMaximums(int rowMax, int colMax) {
		m_max = rowMax ;
		m_colMax = colMax ;
	}
	void beginRow() ;
	void endRow() ;

	/*Data Members*/
	VrGroup *p_row ;
	VrRowLayout *p_rowLayout ;
	bwReal m_colMax ;
	bwReal m_colSpacing ;

private:
};

#endif //_VrGridLayout_H

