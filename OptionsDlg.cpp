// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#include "StdAfx.h"
#include "OptionsDlg.h"
///////////////////////////////////////////////////////////////////////////////
const UINT COptionsDlg::_controlsToClip[] =
{
//{{WTLBUILDER_CTRLTOCLIP
//}}WTLBUILDER_CTRLTOCLIP
	0
};
//////////////////////////////////////////////////////////////////////////
COptionsDlg::COptionsDlg()
{
	_showHandle=FALSE;
}

LRESULT COptionsDlg::OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
//{{WTLBUILDER_MEMBER_CREATION
	m_formFont.CreateFont(8,0,0,0,FW_NORMAL,false,false,false,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH|FF_DONTCARE,_T("MS Sans Serif"));
	SetFont((HFONT)m_formFont);
	ResizeClient(480,375);
	SetWindowText(_T("Options"));

	m_panel.Create(m_hWnd,CRect(0,0,480,340),NULL,WS_CHILD|WS_VISIBLE,0,IDC_OPTIONSDLG_PANEL);
	m_panel.SetFont((HFONT)m_formFont);
	m_panel.SetInnerBorder(BDR_RAISEDINNER);
	m_panel.SetOuterBorder(BDR_SUNKENOUTER);
	m_panel.SetEdgeType(BF_RECT);
	m_panel.SetTextColor(GetSysColor(COLOR_BTNTEXT));
	m_panel.SetBkColor(GetSysColor(COLOR_BTNFACE));
	m_panel.SetHorizTextAlign(DT_CENTER);
	m_panel.SetVertTextAlign(DT_VCENTER);
	m_panel.SetSingleLine(true);
	m_panel.SetCaption(_T(""));

	m_optionsTree.Create(m_panel,CRect(2,2,162,337),NULL,WS_CHILD|WS_VISIBLE,WS_EX_CLIENTEDGE,IDC_OPTIONSDLG_OPTIONSTREE);
	m_optionsTree.SetFont((HFONT)m_formFont);

	m_ok.Create(m_hWnd,CRect(313,346,387,368),_T("OK"),WS_CHILD|WS_VISIBLE|BS_DEFPUSHBUTTON|BS_TEXT|BS_CENTER|BS_VCENTER,0,IDOK);
	m_ok.SetFont((HFONT)m_formFont);

	m_cancel.Create(m_hWnd,CRect(397,346,471,368),_T("Cancel"),WS_CHILD|WS_VISIBLE|BS_TEXT|BS_CENTER|BS_VCENTER,0,IDCANCEL);
	m_cancel.SetFont((HFONT)m_formFont);

	m_pages.Create(m_panel,CRect(162,3,478,336),NULL,WS_CHILD|WS_VISIBLE,0,IDC_OPTIONSDLG_PANELHOST);
	m_pages.SetFont((HFONT)m_formFont);
	m_pages.SetInnerBorder(BDR_RAISEDINNER);
	m_pages.SetOuterBorder(BDR_RAISEDOUTER);
	m_pages.SetEdgeType(BF_RECT);
	m_pages.SetBkColor(GetSysColor(COLOR_BTNFACE));

	m_panel6.Create(m_pages,CRect(0,0,316,333),NULL,WS_CHILD|WS_VISIBLE,0,IDC_COPTIONSDLG_PANEL6);
	m_panel6.SetFont((HFONT)m_formFont);
	m_panel6.SetInnerBorder(0);
	m_panel6.SetOuterBorder(0);
	m_panel6.SetEdgeType(BF_RECT);
	m_panel6.SetTextColor(GetSysColor(COLOR_BTNTEXT));
	m_panel6.SetBkColor(GetSysColor(COLOR_BTNFACE));
	m_panel6.SetHorizTextAlign(DT_CENTER);
	m_panel6.SetVertTextAlign(DT_VCENTER);
	m_panel6.SetSingleLine(true);
	m_panel6.SetCaption(_T(""));
	m_pages.AddPanel(&m_panel6);

//}}WTLBUILDER_MEMBER_CREATION
//{{WTLBUILDER_POST_CREATION
	m_pages.SetCurrent(&m_panel6);
//}}WTLBUILDER_POST_CREATION
	CenterWindow(GetDesktopWindow());
	DefineLayout();
	m_optionsTree.InsertItem(TVIF_TEXT,_T("Item"),0,0,0,0,(LPARAM)&m_panel6,NULL,NULL);
	return TRUE;
}

LRESULT COptionsDlg::OnCloseCmd(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	EndDialog(wID);
//{{WTLBUILDER_MEMBER_DESTRUCTION
//}}WTLBUILDER_MEMBER_DESTRUCTION
	return 0;
}

void COptionsDlg::DefineLayout()
{
//{{WTLBUILDER_ATTACH_CONTROLS
//}}WTLBUILDER_ATTACH_CONTROLS
}

void COptionsDlg::InitLayout()
{
//{{WTLBUILDER_INITLAYOUT
//}}WTLBUILDER_INITLAYOUT
	//SetScrollSize(_minClientSize);
}

LRESULT COptionsDlg::OnSelchangedOptionsTree(int idCtrl, LPNMHDR pnmh, BOOL& bHandled)
{
	if(IDC_OPTIONSDLG_OPTIONSTREE==idCtrl)
	{
		HTREEITEM hCurrent = m_optionsTree.GetSelectedItem();
		if(hCurrent)
		{
			Panel::CPanel *panel=static_cast<Panel::CPanel *>((void*)m_optionsTree.GetItemData(hCurrent));
			if(panel)
				m_pages.SetCurrent(panel);
		}
	}
	return 0;
}

LRESULT COptionsDlg::OnSelchangingOptionsTree(int idCtrl, LPNMHDR pnmh, BOOL& bHandled)
{
	if(IDC_OPTIONSDLG_OPTIONSTREE==idCtrl)
	{
		HTREEITEM hCurrent = m_optionsTree.GetSelectedItem();
		if(hCurrent)
		{
			Panel::CPanel *panel=static_cast<Panel::CPanel *>((void*)m_optionsTree.GetItemData(hCurrent));
			if(panel)
				m_pages.SetCurrent(panel);
		}
	}
	return 0;
}
