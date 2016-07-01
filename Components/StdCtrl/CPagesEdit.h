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
#include "editlistbox.h"

//{{WTLBUILDER_CONTROL_ID_DECLARATION
#define	IDC_PAGES_LIST	1013
//}}WTLBUILDER_CONTROL_ID_DECLARATION

class CPagesEdit:public CDialogImpl<CPagesEdit>
{
	CToolTipCtrl	m_toolTip;
//{{WTLBUILDER_MEMBER_DECLARATION
	CFont	m_formFont;
	CButton	m_ok;
	CButton	m_cancel;
	CEditListBox	m_pagesList;
//}}WTLBUILDER_MEMBER_DECLARATION
	PropertyBase * prop;
public:
	enum { IDD = IDD_NULL };

	BEGIN_MSG_MAP(CPagesEdit)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		COMMAND_ID_HANDLER(IDOK, OnCloseCmd)
		COMMAND_ID_HANDLER(IDCANCEL, OnCloseCmd)
	END_MSG_MAP()

	CPagesEdit(PropertyBase *);	

	LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnCloseCmd(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
};
void PagesEdit(HWND parent,PropertyBase *prop,LPARAM);
//////////////////////////////////////////////////////////////////////////
