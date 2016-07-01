// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#include "StdAfx.h"
#include "CCellEditDlg.h"
///////////////////////////////////////////////////////////////////////////////
const UINT CCellEditDlg::_controlsToClip[] =
{
//{{WTLBUILDER_CTRLTOCLIP
//}}WTLBUILDER_CTRLTOCLIP
	0
};

//////////////////////////////////////////////////////////////////////////
CCellEditDlg::CCellEditDlg(PropertyBase *p):prop(p)
//{{WTLBUILDER_CONSTRUCTOR
//}}WTLBUILDER_CONSTRUCTOR
{
}

CCellEditDlg::~CCellEditDlg(void)
{
}

LRESULT CCellEditDlg::OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	m_toolTip.Create(m_hWnd);
//{{WTLBUILDER_MEMBER_CREATION
	m_formFont.CreateFont(-12,0,0,0,FW_NORMAL,false,false,false,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH|FF_DONTCARE,_TEXT("MS Sans Serif"));
	SetFont((HFONT)m_formFont);
	ResizeClient(438,366);
	SetWindowText(_TEXT("Cell Edit"));

	m_panel1.Create(m_hWnd,CRect(6,6,432,329),NULL,WS_CHILD|WS_VISIBLE,0,IDC_CCELLEDITDLG_PANEL1);
	m_panel1.SetFont((HFONT)m_formFont);
	m_panel1.SetInnerBorder(BDR_RAISEDINNER);
	m_panel1.SetOuterBorder(BDR_SUNKENOUTER);
	m_panel1.SetEdgeType(BF_RECT);
	m_panel1.SetTextColor(GetSysColor(COLOR_BTNTEXT));
	m_panel1.SetBkColor(GetSysColor(COLOR_BTNFACE));
	m_panel1.SetHorizTextAlign(DT_CENTER);
	m_panel1.SetVertTextAlign(DT_VCENTER);
	m_panel1.SetSingleLine(true);
	m_panel1.SetCaption(_TEXT(""));

	m_grid.Create(m_panel1,CRect(6,6,337,146),NULL,WS_CHILD|WS_VISIBLE,WS_EX_CLIENTEDGE,IDC_CCELLEDITDLG_GRIDCTRL2);
	m_gridCellFont.CreateFont(-12,0,0,0,FW_NORMAL,false,false,false,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH|FF_DONTCARE,_TEXT("MS Sans Serif"));
	m_grid.SetCellFont((HFONT)m_gridCellFont);
	m_gridHeaderFont.CreateFont(-12,0,0,0,FW_BOLD,false,false,false,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH|FF_DONTCARE,_TEXT("MS Sans Serif"));
	m_grid.SetHeaderFont((HFONT)m_gridHeaderFont);
	m_grid.SetExtendedGridStyle(GS_EX_LINENUMBERS|GS_EX_VGRIDLINES|GS_EX_HGRIDLINES);
	m_grid.SetListener(this);

	m_ok.Create(m_hWnd,CRect(196,336,270,358),_TEXT("&Ok"),WS_CHILD|WS_VISIBLE|BS_DEFPUSHBUTTON|BS_TEXT|BS_CENTER|BS_VCENTER,0,IDOK);
	m_ok.SetFont((HFONT)m_formFont);

	m_cancel.Create(m_hWnd,CRect(277,336,351,358),_TEXT("&Cancel"),WS_CHILD|WS_VISIBLE|BS_TEXT|BS_CENTER|BS_VCENTER,0,IDCANCEL);
	m_cancel.SetFont((HFONT)m_formFont);

	m_apply.Create(m_hWnd,CRect(358,336,432,358),_TEXT("&Apply"),WS_CHILD|WS_VISIBLE|BS_TEXT|BS_CENTER|BS_VCENTER,0,IDAPPLY);
	m_apply.SetFont((HFONT)m_formFont);

	m_groupbox9.Create(m_panel1,CRect(6,180,416,311),_TEXT("Cell"),WS_CHILD|WS_VISIBLE|BS_GROUPBOX|BS_TEXT|BS_LEFT|BS_VCENTER,0,IDC_CCELLEDITDLG_GROUPBOX9);
	m_groupbox9.SetFont((HFONT)m_formFont);

	m_static10.Create(m_groupbox9,CRect(6,24,42,38),_TEXT("Width:"),WS_CHILD|WS_VISIBLE|SS_LEFT,0,IDC_CCELLEDITDLG_STATIC10);
	m_static10.SetFont((HFONT)m_formFont);

	m_edit11.Create(m_groupbox9,CRect(49,20,123,42),_TEXT("40"),WS_CHILD|WS_VISIBLE,WS_EX_CLIENTEDGE,IDC_CCELLEDITDLG_EDIT11);
	m_edit11.SetFont((HFONT)m_formFont);

	m_static12.Create(m_groupbox9,CRect(6,55,34,69),_TEXT("Type:"),WS_CHILD|WS_VISIBLE|SS_LEFT,0,IDC_CCELLEDITDLG_STATIC12);
	m_static12.SetFont((HFONT)m_formFont);

	m_combobox13.Create(m_groupbox9,CRect(49,52,157,126),NULL,WS_CHILD|WS_VISIBLE|CBS_DROPDOWNLIST|CBS_AUTOHSCROLL|CBS_HASSTRINGS,0,IDC_CCELLEDITDLG_COMBOBOX13);
	m_combobox13.SetFont((HFONT)m_formFont);
	m_combobox13.AddString(_TEXT("Text"));
	m_combobox13.AddString(_TEXT("Number"));
	m_combobox13.AddString(_TEXT("Date"));
	m_combobox13.LimitText(0);
	m_combobox13.SetItemHeight(-1,15);
	m_combobox13.SetCurSel(0);
	m_combobox13.SetItemHeight(0,13);
	m_combobox13.SetDroppedWidth(108);
	m_combobox13.SetHorizontalExtent(40);

	m_add.Create(m_panel1,CRect(344,6,418,28),_TEXT("Add"),WS_CHILD|WS_VISIBLE|BS_TEXT|BS_CENTER|BS_VCENTER,0,IDC_ADD);
	m_add.SetFont((HFONT)m_formFont);

	m_button15.Create(m_panel1,CRect(344,36,418,58),_TEXT("Delete"),WS_CHILD|WS_VISIBLE|BS_TEXT|BS_CENTER|BS_VCENTER,0,IDC_DELETE);
	m_button15.SetFont((HFONT)m_formFont);

	m_button16.Create(m_panel1,CRect(344,72,418,94),_TEXT("Up"),WS_CHILD|WS_VISIBLE|BS_TEXT|BS_CENTER|BS_VCENTER,0,IDC_UP);
	m_button16.SetFont((HFONT)m_formFont);

	m_button17.Create(m_panel1,CRect(344,101,418,123),_TEXT("Down"),WS_CHILD|WS_VISIBLE|BS_TEXT|BS_CENTER|BS_VCENTER,0,IDC_DOWN);
	m_button17.SetFont((HFONT)m_formFont);

//}}WTLBUILDER_MEMBER_CREATION
//{{WTLBUILDER_POST_CREATION
//}}WTLBUILDER_POST_CREATION
    CenterWindow(GetDesktopWindow());
	DefineLayout();
    
    
    m_grid.AddColumn(_T("Column"),140,CGridCtrl::EDIT_TEXT);
    //m_grid.SetRedraw(FALSE);
    DecorativeCtrl::CGridCtrlComp * gridCtrl=(DecorativeCtrl::CGridCtrlComp *)prop->Self();
    for(int i = 0; i < gridCtrl->GetColumnCount(); i++)
    {
        long nItem = m_grid.AddRow();
        m_grid.SetItem(nItem,_T("Column"),(LPCTSTR)gridCtrl->GetColumnName(i));
    }
    //SetRedraw(TRUE);
	return TRUE;
}

LRESULT CCellEditDlg::OnCloseCmd(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	EndDialog(wID);
//{{WTLBUILDER_MEMBER_DESTRUCTION
//}}WTLBUILDER_MEMBER_DESTRUCTION
	return 0;
}

void CCellEditDlg::DefineLayout()
{
//{{WTLBUILDER_ATTACH_CONTROLS
//}}WTLBUILDER_ATTACH_CONTROLS
}

void CCellEditDlg::InitLayout()
{
//{{WTLBUILDER_INITLAYOUT
//}}WTLBUILDER_INITLAYOUT
	//SetScrollSize(_minClientSize);
}

LRESULT CCellEditDlg::OnAdd(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
    return 0;
}

LRESULT CCellEditDlg::OnDelete(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
    return 0;
}

void CCellEditDlg::OnRowActivate(UINT uID,long nRow)
{
    DecorativeCtrl::CGridCtrlComp * gridCtrl=(DecorativeCtrl::CGridCtrlComp *)prop->Self();
//    gridCtrl
}

//////////////////////////////////////////////////////////////////////////
void GridCtrlCellEdit(HWND parent,PropertyBase *prop,LPARAM)
{
	if(prop)
	{
		CCellEditDlg Dlg(prop);
		if(Dlg.DoModal(parent)==IDOK)
		{
            SendEvent(evAddUndo,NULL);
		}
	}
}
