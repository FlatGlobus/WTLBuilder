// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#ifndef __IFONTLISTEDIT_H
#define __IFONTLISTEDIT_H
////////////////////////////////////////////////////////////////////////////////////////////
#include "PropertyListEdit.h"

class PROPERTY_API CFontListEdit:public CInplaceListEdit
{
public:

	virtual void ShowProperty(PropertyBase *prop);
	void UpdateProperty(PropertyBase *prop);
	static BOOL CALLBACK EnumFontProc (LPLOGFONT lplf, LPTEXTMETRIC /*lptm*/, DWORD dwType, LPARAM lpData);
	static HWND CreateEdit(HWND Parent,CRect & Rect,PropertyBase * prop,CPoint &,LPARAM);
};
////////////////////////////////////////////////////////////////////////////////////////////
#endif