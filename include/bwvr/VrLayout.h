/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _VrLayout_H
#define _VrLayout_H

#include "VrLay.h"

class VrGroup ;

class VrLayout : public BwPart {
public:
	VrLayout(VrGroup *pGroup) ;
	virtual bool onCreate(const BwPartInfo& info) ;
	virtual void layout() {}
	virtual bwString getClassName() { return "VrLayout" ; }
	virtual void addModel(VrModel *pModel) ;
	void setMax(int max ) {m_max = max ;}
	virtual int getVacancies() { return m_max - m_total ; }

	void setSpacing(const bwSize3& spacing) {
		m_spacing = spacing ;
	}
	/*Data Members*/
	int m_total ;
	int m_max ;
	//bwReal m_spacing ;
	bwSize3 m_spacing ;
	vrDirection m_direction ; //layout direction. example {0, -1, 1}
	VrGroup *p_group ;

protected:
private:
};

#endif //_VrLayout_H
