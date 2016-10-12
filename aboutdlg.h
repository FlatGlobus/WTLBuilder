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
#define	IDC_CABOUTDLG_PICTURE5	1005
#define	IDC_CABOUTDLG_STATIC8	1008
#define	IDC_CABOUTDLG_STATIC9	1009
#define	IDC_CABOUTDLG_PANEL10	1010
//}}WTLBUILDER_CONTROL_ID_DECLARATION

class CAboutDlg:public CDialogImpl<CAboutDlg>
{
	CToolTipCtrl	m_toolTip;
//{{WTLBUILDER_MEMBER_DECLARATION
	CFont	m_formFont;
	CButton	m_button2;
	CStatic	m_picture5;
	CBitmap	m_picture5Bitmap;
	CStatic	m_static8;
	CStatic	m_static9;
	CFont	m_static9Font;
	Panel::CPanel	m_panel10;
//}}WTLBUILDER_MEMBER_DECLARATION
public:
	enum { IDD = IDD_NULL };

	typedef CDialogImpl<CAboutDlg> thisClass;

	BEGIN_MSG_MAP(CAboutDlg)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		COMMAND_ID_HANDLER(IDOK, OnCloseCmd)
		COMMAND_ID_HANDLER(IDCANCEL, OnCloseCmd)
		REFLECT_NOTIFICATIONS_EX()
	END_MSG_MAP()

	CAboutDlg(void);
	~CAboutDlg(void);
	LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnCloseCmd(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
};
//////////////////////////////////////////////////////////////////////////
