// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#ifndef __COMPONENTLISTEDIT_H
#define __COMPONENTLISTEDIT_H
////////////////////////////////////////////////////////////////////////////////////////////
#include "Component.h"
#include "Command.h"
#include "EventLib.h"

typedef CWinTraits<WS_BORDER|WS_CHILD|WS_VISIBLE|WS_TABSTOP|WS_VSCROLL|LBS_NOTIFY|LBS_HASSTRINGS|LBS_SORT,0> ComponentListEditTraits;
class PROPERTY_API CComponentListEdit :
	public CWindowImpl<CComponentListEdit, CListBox, ComponentListEditTraits>
{
	bool m_fCancel;
	PropertyBase * prop;
    static CString kind;
public:
	CComponentListEdit(PropertyBase * p);
	virtual void OnFinalMessage(HWND /*hWnd*/);

	BEGIN_MSG_MAP(CComponentListEdit)
		MESSAGE_HANDLER(WM_CREATE, OnCreate)
		MESSAGE_HANDLER(WM_KEYDOWN, OnKeyDown)
		MESSAGE_HANDLER(WM_KILLFOCUS, OnKillFocus)
		MESSAGE_HANDLER(WM_GETDLGCODE, OnGetDlgCode)
		MESSAGE_HANDLER(WM_LBUTTONUP, OnLButtonUp)
	END_MSG_MAP()

	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/);
	LRESULT OnKeyDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnKillFocus(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled);
	LRESULT OnLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	void UpdateProperty(void);
	LRESULT OnGetDlgCode(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/);

	static HWND CreateInplaceEdit(HWND Parent,CRect & Rect,PropertyBase * prop,CPoint&,LPARAM);
    static LPCTSTR GetNoneStr();
    static void SetComponentKind(LPCTSTR kind);
};
////////////////////////////////////////////////////////////////////////////////////////////
#endif