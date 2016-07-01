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
//}}WTLBUILDER_INCLUDE_DECLARATION


//{{WTLBUILDER_CONTROL_ID_DECLARATION
#define	IDC_DIALOGIMPL0_PANEL0	1000
#define	IDC_DIALOGIMPL0_PANEL1	1001
#define	IDC_DIALOGIMPL0_PANEL2	1002
#define	IDC_DIALOGIMPL0_BUTTON3	1003
#define	IDC_DIALOGIMPL0_BUTTON5	1005
//}}WTLBUILDER_CONTROL_ID_DECLARATION

class CImageListEditDlg:public CResizableDialogImpl<CImageListEditDlg>
{
	CToolTipCtrl	m_toolTip;
//{{WTLBUILDER_MEMBER_DECLARATION
	CFont	m_formFont;
	Panel::CPanel	m_panel0;
	Panel::CPanel	m_panel1;
	Panel::CPanel	m_panel2;
	CButton	m_button3;
	CButton	m_button5;
//}}WTLBUILDER_MEMBER_DECLARATION
	void InitLayout(void);
public:
	virtual void DefineLayout();
	enum { IDD = IDD_NULL };
	static const UINT _controlsToClip[];

	typedef CResizableDialogImpl<CImageListEditDlg> thisClass;

	BEGIN_MSG_MAP(CImageListEditDlg)
		CHAIN_MSG_MAP(thisClass)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		COMMAND_ID_HANDLER(IDOK, OnCloseCmd)
		COMMAND_ID_HANDLER(IDCANCEL, OnCloseCmd)
		REFLECT_NOTIFICATIONS()
	END_MSG_MAP()

	CImageListEditDlg(void);
	~CImageListEditDlg(void);
	LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnCloseCmd(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
};
//////////////////////////////////////////////////////////////////////////
