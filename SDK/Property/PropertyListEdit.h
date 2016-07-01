// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#ifndef __PROPERTYLISTEDIT_H
#define __PROPERTYLISTEDIT_H
////////////////////////////////////////////////////////////////////////////////////////////
#include "InplaceEdit.h"

typedef CWinTraits<WS_BORDER|WS_CHILD|WS_VISIBLE|WS_TABSTOP|WS_VSCROLL|LBS_NOTIFY,0> CInplaceListEditTraits;
class PROPERTY_API CInplaceListEdit : 
	public CInplaceEditBase<CInplaceListEdit, CListBox, CInplaceListEditTraits>
{
public:
	typedef CInplaceEditBase<CInplaceListEdit, CListBox, CInplaceListEditTraits> baseClass;
	BEGIN_MSG_MAP(CInplaceListEdit)
		CHAIN_MSG_MAP(baseClass)
		MESSAGE_HANDLER(WM_LBUTTONUP, OnLButtonUp)
		REFLECT_NOTIFICATIONS_EX()
	END_MSG_MAP()

	virtual void ShowProperty(PropertyBase *prop);
	void UpdateProperty(PropertyBase *prop);
	LRESULT OnLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	static HWND CreateEdit(HWND Parent,CRect & Rect,PropertyBase * prop,CPoint &,LPARAM);
};
////////////////////////////////////////////////////////////////////////////////////////////
#endif