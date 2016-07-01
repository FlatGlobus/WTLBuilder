// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#pragma once
//////////////////////////////////////////////////////////////////////////
#include "resource.h"

#undef __WTLBUILDER__
//{{WTLBUILDER_INCLUDE_DECLARATION
#include "Panel.h"
#include "EditListBox.h"
//}}WTLBUILDER_INCLUDE_DECLARATION

//{{WTLBUILDER_CONTROL_ID_DECLARATION
#define	IDC_CSTRINGSEDIT_PANEL17	1017
#define	IDC_STRINGS_LIST	1015
#define	IDC_CSTRINGSEDIT_PANEL18	1018
#define	IDC_CSTRINGSEDIT_STATIC19	1019
//}}WTLBUILDER_CONTROL_ID_DECLARATION

class CStringsEdit:public CDialogImpl<CStringsEdit>
{
	CToolTipCtrl	m_toolTip;
//{{WTLBUILDER_MEMBER_DECLARATION
	CFont	m_formFont;
	Panel::CPanel	m_panel17;
	CEditListBox	m_stringsList;
	Panel::CPanel	m_panel18;
	CButton	m_ok;
	CButton	m_cancel;
	CStatic	m_static19;
//}}WTLBUILDER_MEMBER_DECLARATION
	PropertyBase * prop;
public:
	enum { IDD = IDD_NULL };

	BEGIN_MSG_MAP(CStringsEdit)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		COMMAND_ID_HANDLER(IDOK, OnCloseCmd)
		COMMAND_ID_HANDLER(IDCANCEL, OnCloseCmd)
        REFLECT_NOTIFICATIONS_EX()
	END_MSG_MAP()

	CStringsEdit(PropertyBase *);	

	LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnCloseCmd(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
};
void StringsEdit(HWND parent,PropertyBase *prop,LPARAM);
//////////////////////////////////////////////////////////////////////////
