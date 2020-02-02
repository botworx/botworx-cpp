/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _VrMatrixLayout_H
#define _VrMatrixLayout_H

#include <bwvr/VrLinearLayout.h>

class VrGridLayout ;

class VrMatrixLayout : public VrStackLayout {
public:
	VrMatrixLayout(VrGroup *pGroup) ;
	virtual bwString getClassName() { return "VrMatrixLayout" ; }
	virtual void addModel(VrModel *pModel) ;

	void setSpacing(const bwSize3& spacing) {
		m_colSpacing = spacing[0] ;
		m_rowSpacing = spacing[2] ;
		m_gridSpacing = spacing[1];
	}
	void setMaximums(int rowMax, int colMax) {
		m_max = rowMax ;
		m_colMax = colMax ;
	}
	void beginRow() ;
	void endRow() ;
	void beginGrid() ;
	void endGrid() ;

	/*Data Members*/
	VrGroup *p_grid ;
	VrGridLayout *p_gridLayout ;
	bwReal m_colMax ;
	bwReal m_colSpacing ;
	bwReal m_rowMax ;
	bwReal m_rowSpacing ;
	bwReal m_gridMax ;
	bwReal m_gridSpacing ;
};

#endif //_VrMatrixLayout_H
