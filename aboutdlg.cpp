// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.
#include "StdAfx.h"
#include "AboutDlg.h"
#include "version.h"
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
    ResizeClient(521,123);
    HICON hIcon = (HICON)::LoadImage(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDR_MAINFRAME),
       IMAGE_ICON, ::GetSystemMetrics(SM_CXICON), ::GetSystemMetrics(SM_CYICON), LR_DEFAULTCOLOR);
    SetIcon(hIcon, TRUE);
    HICON hIconSmall = (HICON)::LoadImage(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDR_MAINFRAME),
       IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), LR_DEFAULTCOLOR);
    SetIcon(hIconSmall, TRUE);

    m_button2.Create(m_hWnd,CRect(209,91,292,115),_T("&OK"),WS_CHILD|WS_VISIBLE|WS_TABSTOP|BS_TEXT|BS_CENTER|BS_VCENTER,0,IDOK);
    m_button2.SetFont((HFONT)m_formFont);

    m_picture5.Create(m_hWnd,CRect(10,10,210,66),NULL,WS_CHILD|WS_VISIBLE|SS_LEFT|SS_RIGHT|SS_BLACKRECT|SS_WHITERECT|SS_GRAYFRAME|SS_USERITEM|SS_LEFTNOWORDWRAP|SS_BITMAP|SS_CENTERIMAGE,0,IDC_CABOUTDLG_PICTURE5);
    m_picture5Bitmap.LoadBitmap(IDB_LOGO);
    m_picture5.SetBitmap(m_picture5Bitmap);

    m_static8.Create(m_hWnd,CRect(218,10,507,25),_T("Copyright 2007 - 2018 © FlatGlobus (wtlbuilder@gmail.com)"),WS_CHILD|WS_VISIBLE|SS_LEFT,0,IDC_CABOUTDLG_STATIC8);
    m_static8.SetFont((HFONT)m_formFont);

    m_static9.Create(m_hWnd,CRect(218,52,261,66),_T("Version"),WS_CHILD|WS_VISIBLE|SS_LEFT,0,IDC_CABOUTDLG_STATIC9);
    m_static9Font.CreateFont(-12,0,0,0,FW_BOLD,false,false,false,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH|FF_DONTCARE,_T("MS Sans Serif"));
    m_static9.SetFont((HFONT)m_static9Font);

    m_version.Create(m_hWnd,CRect(276,52,496,66),_T(""),WS_CHILD|WS_VISIBLE|WS_CLIPSIBLINGS|WS_CLIPCHILDREN|SS_LEFT,0,IDC_CABOUTDLG_STATIC11);
    m_version.SetFont((HFONT)m_formFont);

    m_hyperlink12.Create(m_hWnd,CRect(372,84,438,96),NULL,WS_CHILD|WS_VISIBLE|WS_CLIPSIBLINGS|WS_CLIPCHILDREN,0,IDC_CABOUTDLG_HYPERLINK12);
    m_hyperlink12.SetLabel(_T(""));
    m_hyperlink12.SetHyperLink(_T("wtlbuilder@gmail.com"));
    m_hyperlink12.m_bPaintLabel=true;
    m_hyperlink12.m_clrLink=RGB(0x00,0x00,0xFF);
    m_hyperlink12.m_clrVisited=RGB(0x80,0x00,0x80);

//}}WTLBUILDER_MEMBER_CREATION
//{{WTLBUILDER_POST_CREATION
//}}WTLBUILDER_POST_CREATION
    m_version.SetWindowText(VERSION);
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

