// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#include "StdAfx.h"
#include "ImageListEditDlg.h"
///////////////////////////////////////////////////////////////////////////////
const UINT CImageListEditDlg::_controlsToClip[] =
{
//{{WTLBUILDER_CTRLTOCLIP
//}}WTLBUILDER_CTRLTOCLIP
	0
};

//////////////////////////////////////////////////////////////////////////
CImageListEditDlg::CImageListEditDlg(void)
//{{WTLBUILDER_CONSTRUCTOR
//}}WTLBUILDER_CONSTRUCTOR
{
}

CImageListEditDlg::~CImageListEditDlg(void)
{
}

LRESULT CImageListEditDlg::OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	m_toolTip.Create(m_hWnd);
//{{WTLBUILDER_MEMBER_CREATION
	m_formFont.CreateFont(-12,0,0,0,FW_NORMAL,false,false,false,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH|FF_DONTCARE,_TEXT("MS Sans Serif"));
	SetFont((HFONT)m_formFont);
	ResizeClient(504,350);

	m_panel0.Create(m_hWnd,CRect(0,0,504,40),NULL,WS_CHILD|WS_VISIBLE|WS_TABSTOP,WS_EX_CONTROLPARENT,IDC_DIALOGIMPL0_PANEL0);
	m_panel0.SetFont((HFONT)m_formFont);
	m_panel0.SetInnerBorder(BDR_RAISEDINNER);
	m_panel0.SetOuterBorder(BDR_RAISEDOUTER);
	m_panel0.SetEdgeType(BF_RECT);
	m_panel0.SetTextColor(GetSysColor(COLOR_BTNTEXT));
	m_panel0.SetBkColor(GetSysColor(COLOR_BTNFACE));
	m_panel0.SetHorizTextAlign(DT_CENTER);
	m_panel0.SetVertTextAlign(DT_VCENTER);
	m_panel0.SetSingleLine(true);
	m_panel0.SetCaption(_TEXT(""));

	m_panel1.Create(m_hWnd,CRect(0,40,504,308),NULL,WS_CHILD|WS_VISIBLE|WS_TABSTOP,WS_EX_CONTROLPARENT,IDC_DIALOGIMPL0_PANEL1);
	m_panel1.SetFont((HFONT)m_formFont);
	m_panel1.SetInnerBorder(BDR_RAISEDINNER);
	m_panel1.SetOuterBorder(BDR_RAISEDOUTER);
	m_panel1.SetEdgeType(BF_RECT);
	m_panel1.SetTextColor(GetSysColor(COLOR_BTNTEXT));
	m_panel1.SetBkColor(GetSysColor(COLOR_BTNFACE));
	m_panel1.SetHorizTextAlign(DT_CENTER);
	m_panel1.SetVertTextAlign(DT_VCENTER);
	m_panel1.SetSingleLine(true);
	m_panel1.SetCaption(_TEXT(""));

	m_panel2.Create(m_hWnd,CRect(0,310,504,350),NULL,WS_CHILD|WS_VISIBLE|WS_TABSTOP,WS_EX_CONTROLPARENT,IDC_DIALOGIMPL0_PANEL2);
	m_panel2.SetFont((HFONT)m_formFont);
	m_panel2.SetInnerBorder(BDR_RAISEDINNER);
	m_panel2.SetOuterBorder(BDR_RAISEDOUTER);
	m_panel2.SetEdgeType(BF_RECT);
	m_panel2.SetTextColor(GetSysColor(COLOR_BTNTEXT));
	m_panel2.SetBkColor(GetSysColor(COLOR_BTNFACE));
	m_panel2.SetHorizTextAlign(DT_CENTER);
	m_panel2.SetVertTextAlign(DT_VCENTER);
	m_panel2.SetSingleLine(true);
	m_panel2.SetCaption(_TEXT(""));

	m_button3.Create(m_panel2,CRect(330,9,404,31),_TEXT("&Ok"),WS_CHILD|WS_VISIBLE|WS_TABSTOP|BS_DEFPUSHBUTTON|BS_TEXT|BS_CENTER|BS_VCENTER,0,IDC_DIALOGIMPL0_BUTTON3);
	m_button3.SetFont((HFONT)m_formFont);

	m_button5.Create(m_panel2,CRect(408,9,482,31),_TEXT("&Cancel"),WS_CHILD|WS_VISIBLE|WS_TABSTOP|BS_TEXT|BS_CENTER|BS_VCENTER,0,IDC_DIALOGIMPL0_BUTTON5);
	m_button5.SetFont((HFONT)m_formFont);

//}}WTLBUILDER_MEMBER_CREATION

//{{WTLBUILDER_POST_CREATION
//}}WTLBUILDER_POST_CREATION

//{{WTLBUILDER_TABSTOP
//}}WTLBUILDER_TABSTOP
	CenterWindow();
	DefineLayout();
	return TRUE;
}

LRESULT CImageListEditDlg::OnCloseCmd(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	EndDialog(wID);
//{{WTLBUILDER_MEMBER_DESTRUCTION
//}}WTLBUILDER_MEMBER_DESTRUCTION
	return 0;
}

void CImageListEditDlg::DefineLayout()
{
//{{WTLBUILDER_ATTACH_CONTROLS
//}}WTLBUILDER_ATTACH_CONTROLS
}

void CImageListEditDlg::InitLayout()
{
//{{WTLBUILDER_INITLAYOUT
//}}WTLBUILDER_INITLAYOUT
	//SetScrollSize(_minClientSize);
}
