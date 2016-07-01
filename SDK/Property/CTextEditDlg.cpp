// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#include "StdAfx.h"
#include "CTextEditDlg.h"
#include <cfile.h>
///////////////////////////////////////////////////////////////////////////////
const UINT CTextEditDlg::_controlsToClip[] =
{
//{{WTLBUILDER_CTRLTOCLIP
//}}WTLBUILDER_CTRLTOCLIP
	0
};

//////////////////////////////////////////////////////////////////////////
CTextEditDlg::CTextEditDlg(PropertyBase *p):CResizableDialogImpl<CTextEditDlg>(false),prop(p)
//{{WTLBUILDER_CONSTRUCTOR
//}}WTLBUILDER_CONSTRUCTOR
{
}

CTextEditDlg::~CTextEditDlg(void)
{
}

LRESULT CTextEditDlg::OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	m_toolTip.Create(m_hWnd);
//{{WTLBUILDER_MEMBER_CREATION
	m_formFont.CreateFont(-12,0,0,0,FW_NORMAL,false,false,false,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH|FF_DONTCARE,_TEXT("MS Sans Serif"));
	SetFont((HFONT)m_formFont);
	ResizeClient(622,443);

	m_text.Create(m_hWnd,CRect(0,0,622,400),_TEXT(""),WS_CHILD|WS_VISIBLE|WS_VSCROLL|WS_HSCROLL|WS_TABSTOP|ES_MULTILINE,WS_EX_CLIENTEDGE,IDC_TEXT);
	m_text.SetFont((HFONT)m_formFont);

	m_panel5.Create(m_hWnd,CRect(0,400,622,443),NULL,WS_CHILD|WS_VISIBLE|WS_TABSTOP,WS_EX_CONTROLPARENT,IDC_CTEXTEDITDLG_PANEL5);
	m_panel5.SetFont((HFONT)m_formFont);
	m_panel5.SetInnerBorder(0);
	m_panel5.SetOuterBorder(0);
	m_panel5.SetEdgeType(BF_RECT);
	m_panel5.SetTextColor(GetSysColor(COLOR_BTNTEXT));
	m_panel5.SetBkColor(GetSysColor(COLOR_BTNFACE));
	m_panel5.SetHorizTextAlign(DT_CENTER);
	m_panel5.SetVertTextAlign(DT_VCENTER);
	m_panel5.SetSingleLine(true);
	m_panel5.SetCaption(_TEXT(""));

	m_load.Create(m_panel5,CRect(351,10,425,32),_TEXT("&Load..."),WS_CHILD|WS_VISIBLE|WS_TABSTOP|BS_PUSHBUTTON,0,IDC_LOAD);
	m_load.SetFont((HFONT)m_formFont);
	m_load.SetFlat(false);
	m_load.SetAlign(CButtonST::ST_ALIGN_HORIZ);
	m_load.SetColor(CButtonST::BTNST_COLOR_FG_IN,GetSysColor(COLOR_WINDOWTEXT));
	m_load.SetColor(CButtonST::BTNST_COLOR_FG_OUT,GetSysColor(COLOR_WINDOWTEXT));
	m_load.SetColor(CButtonST::BTNST_COLOR_BK_IN,GetSysColor(COLOR_BTNFACE));
	m_load.SetColor(CButtonST::BTNST_COLOR_BK_OUT,GetSysColor(COLOR_BTNFACE));

	m_ok.Create(m_panel5,CRect(454,10,528,32),_TEXT("&OK"),WS_CHILD|WS_VISIBLE|WS_TABSTOP|BS_PUSHBUTTON,0,IDOK);
	m_ok.SetFont((HFONT)m_formFont);
	m_ok.SetFlat(false);
	m_ok.SetAlign(CButtonST::ST_ALIGN_HORIZ);
	m_ok.SetColor(CButtonST::BTNST_COLOR_FG_IN,GetSysColor(COLOR_WINDOWTEXT));
	m_ok.SetColor(CButtonST::BTNST_COLOR_FG_OUT,GetSysColor(COLOR_WINDOWTEXT));
	m_ok.SetColor(CButtonST::BTNST_COLOR_BK_IN,GetSysColor(COLOR_BTNFACE));
	m_ok.SetColor(CButtonST::BTNST_COLOR_BK_OUT,GetSysColor(COLOR_BTNFACE));

	m_cancel.Create(m_panel5,CRect(538,10,612,32),_TEXT("&Cancel"),WS_CHILD|WS_VISIBLE|WS_TABSTOP|BS_PUSHBUTTON,0,IDCANCEL);
	m_cancel.SetFont((HFONT)m_formFont);
	m_cancel.SetFlat(false);
	m_cancel.SetAlign(CButtonST::ST_ALIGN_HORIZ);
	m_cancel.SetColor(CButtonST::BTNST_COLOR_FG_IN,GetSysColor(COLOR_WINDOWTEXT));
	m_cancel.SetColor(CButtonST::BTNST_COLOR_FG_OUT,GetSysColor(COLOR_WINDOWTEXT));
	m_cancel.SetColor(CButtonST::BTNST_COLOR_BK_IN,GetSysColor(COLOR_BTNFACE));
	m_cancel.SetColor(CButtonST::BTNST_COLOR_BK_OUT,GetSysColor(COLOR_BTNFACE));

//}}WTLBUILDER_MEMBER_CREATION

//{{WTLBUILDER_POST_CREATION
//}}WTLBUILDER_POST_CREATION

//{{WTLBUILDER_TABSTOP
//}}WTLBUILDER_TABSTOP
	CString str = *(CString *)prop->GetValue(true);
	m_text.SetWindowText(str);
	CenterWindow();
	DefineLayout();
	return TRUE;
}

LRESULT CTextEditDlg::OnCloseCmd(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	if(wID ==IDOK)
	{
		CString str;
		m_text.GetWindowText(str);
		prop->SetValue(&str, true);
	}
	EndDialog(wID);
//{{WTLBUILDER_MEMBER_DESTRUCTION
//}}WTLBUILDER_MEMBER_DESTRUCTION
	return 0;
}

void CTextEditDlg::DefineLayout()
{
//{{WTLBUILDER_ATTACH_CONTROLS
//}}WTLBUILDER_ATTACH_CONTROLS
}

void CTextEditDlg::InitLayout()
{
//{{WTLBUILDER_INITLAYOUT
//}}WTLBUILDER_INITLAYOUT
	//SetScrollSize(_minClientSize);
}

LRESULT CTextEditDlg::OnLoad(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	static _TCHAR Filter[] = _T("Text Files (*.txt)\0*.txt\0All Files (*.*)\0*.*\0");
	CFileDialog filedlg(TRUE,_T("*.txt"),NULL,OFN_HIDEREADONLY|OFN_PATHMUSTEXIST|OFN_FILEMUSTEXIST|OFN_EXPLORER,Filter);
	if(filedlg.DoModal(::GetDesktopWindow())==IDOK)
	{
		CString str = LoadString(filedlg.m_szFileName);
		m_text.SetWindowText(str);
	}
	return 0;
}

void CTextEditDlg::TextEditDlg(HWND parent, PropertyBase *prop, LPARAM)
{
	if(prop)
	{
		CTextEditDlg Dlg(prop);
		Dlg.DoModal(::GetDesktopWindow());
	}
}