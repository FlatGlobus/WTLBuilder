// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.
#include "StdAfx.h"
#include "AboutDlg.h"
//////////////////////////////////////////////////////////////////////////
CAboutDlg::CAboutDlg(void)
//{{WTLBUILDER_CONSTRUCTOR
//}}WTLBUILDER_CONSTRUCTOR
{
}

CAboutDlg::~CAboutDlg(void)
{
}

LRESULT CAboutDlg::OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	m_toolTip.Create(m_hWnd);
//{{WTLBUILDER_MEMBER_CREATION
	m_formFont.CreateFont(-12,0,0,0,FW_NORMAL,false,false,false,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH|FF_DONTCARE,_T("MS Sans Serif"));
	SetFont((HFONT)m_formFont);
	ModifyStyle(GetStyle(),WS_POPUP|WS_VISIBLE|WS_CLIPSIBLINGS|WS_CLIPCHILDREN|WS_SYSMENU);
	ResizeClient(456,103);
	HICON hIcon = (HICON)::LoadImage(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDR_MAINFRAME),
	   IMAGE_ICON, ::GetSystemMetrics(SM_CXICON), ::GetSystemMetrics(SM_CYICON), LR_DEFAULTCOLOR);
	SetIcon(hIcon, TRUE);
	HICON hIconSmall = (HICON)::LoadImage(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDR_MAINFRAME),
	   IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), LR_DEFAULTCOLOR);
	SetIcon(hIconSmall, TRUE);

	m_button2.Create(m_hWnd,CRect(356,73,439,97),_T("&OK"),WS_CHILD|WS_VISIBLE|BS_TEXT|BS_CENTER|BS_VCENTER,0,IDOK);
	m_button2.SetFont((HFONT)m_formFont);

	m_picture5.Create(m_hWnd,CRect(10,10,210,66),NULL,WS_CHILD|WS_VISIBLE|WS_TABSTOP|SS_LEFT|SS_RIGHT|SS_BLACKRECT|SS_WHITERECT|SS_GRAYFRAME|SS_USERITEM|SS_LEFTNOWORDWRAP|SS_BITMAP|SS_CENTERIMAGE,0,IDC_CABOUTDLG_PICTURE5);
	m_picture5Bitmap.LoadBitmap(IDB_LOGO);
	m_picture5.SetBitmap(m_picture5Bitmap);

	m_static8.Create(m_hWnd,CRect(218,18,442,33),_T("Copyright © FlatGlobus (wtlbuilder@gmail.com)"),WS_CHILD|WS_VISIBLE|WS_TABSTOP|SS_LEFT,0,IDC_CABOUTDLG_STATIC8);
	m_static8.SetFont((HFONT)m_formFont);

	m_static9.Create(m_hWnd,CRect(10,78,82,92),_T("Version 0.0"),WS_CHILD|WS_VISIBLE|WS_TABSTOP|SS_LEFT,0,IDC_CABOUTDLG_STATIC9);
	m_static9Font.CreateFont(-12,0,0,0,FW_BOLD,false,false,false,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH|FF_DONTCARE,_T("MS Sans Serif"));
	m_static9.SetFont((HFONT)m_static9Font);

	m_panel10.Create(m_hWnd,CRect(86,85,345,87),NULL,WS_CHILD|WS_VISIBLE|WS_TABSTOP,WS_EX_CONTROLPARENT,IDC_CABOUTDLG_PANEL10);
	m_panel10.SetFont((HFONT)m_formFont);
	m_panel10.SetInnerBorder(BDR_RAISEDINNER);
	m_panel10.SetOuterBorder(BDR_SUNKENOUTER);
	m_panel10.SetEdgeType(BF_TOP);
	m_panel10.SetBkColor(GetSysColor(COLOR_BTNFACE));
	m_panel10.SetTextColor(GetSysColor(COLOR_BTNTEXT));
	m_panel10.SetHorizTextAlign(DT_CENTER);
	m_panel10.SetVertTextAlign(DT_VCENTER);
	m_panel10.SetSingleLine(true);

//}}WTLBUILDER_MEMBER_CREATION
//{{WTLBUILDER_POST_CREATION
//}}WTLBUILDER_POST_CREATION
    CenterWindow(GetDesktopWindow());
	return TRUE;
}

LRESULT CAboutDlg::OnCloseCmd(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	EndDialog(wID);
//{{WTLBUILDER_MEMBER_DESTRUCTION
//}}WTLBUILDER_MEMBER_DESTRUCTION
	return 0;
}

