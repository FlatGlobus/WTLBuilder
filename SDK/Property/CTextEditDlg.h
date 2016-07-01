// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#pragma once
//////////////////////////////////////////////////////////////////////////
#include "resource.h"
#include "LayoutMgr.h"
//{{WTLBUILDER_INCLUDE_DECLARATION
#include "Panel.h"
#include "ButtonST.h"
//}}WTLBUILDER_INCLUDE_DECLARATION

//{{WTLBUILDER_CONTROL_ID_DECLARATION
#define	IDC_TEXT	1004
#define	IDC_CTEXTEDITDLG_PANEL5	1005
#define	IDC_LOAD	1006
//}}WTLBUILDER_CONTROL_ID_DECLARATION

class CTextEditDlg:public CResizableDialogImpl<CTextEditDlg>
{
	CToolTipCtrl	m_toolTip;
//{{WTLBUILDER_MEMBER_DECLARATION
	CFont	m_formFont;
	CRichEditCtrl	m_text;
	Panel::CPanel	m_panel5;
	CButtonST	m_load;
	CButtonST	m_ok;
	CButtonST	m_cancel;
//}}WTLBUILDER_MEMBER_DECLARATION
	PropertyBase *prop;
	void InitLayout(void);
public:
	virtual void DefineLayout();
	enum { IDD = IDD_NULL };
	static const UINT _controlsToClip[];

	typedef CResizableDialogImpl<CTextEditDlg> thisClass;

	BEGIN_MSG_MAP(CTextEditDlg)
		CHAIN_MSG_MAP(thisClass)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		COMMAND_ID_HANDLER(IDOK, OnCloseCmd)
		COMMAND_ID_HANDLER(IDCANCEL, OnCloseCmd)
		COMMAND_ID_HANDLER(IDC_LOAD, OnLoad)
		REFLECT_NOTIFICATIONS()
	END_MSG_MAP()

	CTextEditDlg(PropertyBase *prop);
	~CTextEditDlg(void);
	LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnCloseCmd(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnLoad(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	static void TextEditDlg(HWND parent, PropertyBase *prop, LPARAM);
};
//////////////////////////////////////////////////////////////////////////
