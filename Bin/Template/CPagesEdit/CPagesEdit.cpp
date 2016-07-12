#include "StdAfx.h"
#include "Panel.h"
#include "CPagesEdit.h"
//////////////////////////////////////////////////////////////////////////////
const UINT CPagesEdit::_controlsToClip[] =
{
//{{WTLBUILDER_CTRLTOCLIP
//}}WTLBUILDER_CTRLTOCLIP
	0
};
///////////////////////////////////////////////////////////////////////////////
CPagesEdit::CPagesEdit(PropertyBase *p):prop(p)
{
//{{WTLBUILDER_CONSTRUCTOR
//}}WTLBUILDER_CONSTRUCTOR
}

LRESULT CPagesEdit::OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	m_toolTip.Create(m_hWnd);
//{{WTLBUILDER_MEMBER_CREATION
	m_formFont.CreateFont(8,0,0,0,FW_NORMAL,false,false,false,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH|FF_DONTCARE,_TEXT("MS Sans Serif"));
	SetFont((HFONT)m_formFont);
	ResizeClient(369,275);
	SetWindowText(_T("Pages Edit"));

	m_ok.Create(m_hWnd,CRect(211,246,285,268),_TEXT("OK"),WS_CHILD|WS_VISIBLE|BS_DEFPUSHBUTTON|BS_TEXT|BS_CENTER|BS_VCENTER,0,IDOK);
	m_ok.SetFont((HFONT)m_formFont);

	m_panel2.Create(m_hWnd,CRect(0,0,369,240),NULL,WS_CHILD|WS_VISIBLE,0,IDC_CPAGEHOSTEDIT_PANEL2);
	m_panel2.SetFont((HFONT)m_formFont);
	m_panel2.SetInnerBorder(BDR_SUNKENINNER);
	m_panel2.SetOuterBorder(BDR_RAISEDOUTER);
	m_panel2.SetEdgeType(BF_BOTTOM);
	m_panel2.SetTextColor(COLOR_BTNTEXT);
	m_panel2.SetBkColor(COLOR_BTNFACE);
	m_panel2.SetHorizTextAlign(DT_LEFT);
	m_panel2.SetVertTextAlign(DT_TOP);
	m_panel2.SetSingleLine(true);
	m_panel2.SetCaption(_TEXT(""));

	m_pagelist.Create(m_panel2,CRect(3,19,366,205),NULL,WS_CHILD|WS_VISIBLE|WS_VSCROLL|LBS_NOTIFY|LBS_SORT|LBS_NOINTEGRALHEIGHT,WS_EX_CLIENTEDGE,IDC_PAGELIST);
	m_pagelist.SetFont((HFONT)m_formFont);
	m_pagelist.SetItemHeight(0,13);

	m_static5.Create(m_panel2,CRect(3,214,34,230),_TEXT("Name:"),WS_CHILD|WS_VISIBLE|SS_LEFT,0,IDC_CPAGEHOSTEDIT_STATIC5);
	m_static5.SetFont((HFONT)m_formFont);

	m_pagename.Create(m_panel2,CRect(40,212,238,232),_TEXT(""),WS_CHILD|WS_VISIBLE,WS_EX_CLIENTEDGE,IDC_PAGENAME);
	m_pagename.SetFont((HFONT)m_formFont);

	m_add.Create(m_panel2,CRect(269,212,289,232),_TEXT(""),WS_CHILD|WS_VISIBLE|BS_ICON|BS_CENTER|BS_VCENTER,0,IDC_ADD);
	m_add.SetFont((HFONT)m_formFont);
	m_toolTip.AddTool((HWND)m_add,_TEXT("Add new page"));
	m_addIcon=AtlLoadIcon(IDI_PLUS);
	m_add.SetIcon(m_addIcon);

	m_remove.Create(m_panel2,CRect(294,212,314,232),_TEXT(""),WS_CHILD|WS_VISIBLE|BS_ICON|BS_CENTER|BS_VCENTER,0,IDC_REMOVE);
	m_remove.SetFont((HFONT)m_formFont);
	m_toolTip.AddTool((HWND)m_remove,_TEXT("Remove page"));
	m_removeIcon=AtlLoadIcon(IDI_MINUS);
	m_remove.SetIcon(m_removeIcon);

	m_up.Create(m_panel2,CRect(319,212,339,232),_TEXT(""),WS_CHILD|WS_VISIBLE|BS_ICON|BS_CENTER|BS_VCENTER,0,IDC_UP);
	m_up.SetFont((HFONT)m_formFont);
	m_toolTip.AddTool((HWND)m_up,_TEXT("Move up"));
	m_upIcon=AtlLoadIcon(IDI_ARROWU);
	m_up.SetIcon(m_upIcon);

	m_down.Create(m_panel2,CRect(344,212,364,232),_TEXT(""),WS_CHILD|WS_VISIBLE|BS_ICON|BS_CENTER|BS_VCENTER,0,IDC_DOWN);
	m_down.SetFont((HFONT)m_formFont);
	m_toolTip.AddTool((HWND)m_down,_TEXT("Move down"));
	m_downIcon=AtlLoadIcon(IDI_ARROWD);
	m_down.SetIcon(m_downIcon);

	m_cancel.Create(m_hWnd,CRect(290,246,364,268),_TEXT("Cancel"),WS_CHILD|WS_VISIBLE|BS_TEXT|BS_CENTER|BS_VCENTER,0,IDCANCEL);
	m_cancel.SetFont((HFONT)m_formFont);

	m_static12.Create(m_panel2,CRect(3,2,34,16),_TEXT("Pages"),WS_CHILD|WS_VISIBLE|SS_LEFT,0,IDC_CPAGESEDIT_STATIC12);
	m_static12.SetFont((HFONT)m_formFont);

	m_update.Create(m_panel2,CRect(244,212,264,232),_TEXT("m_button13"),WS_CHILD|WS_VISIBLE|BS_ICON|BS_CENTER|BS_VCENTER,0,IDC_UPDATE);
	m_update.SetFont((HFONT)m_formFont);
	m_toolTip.AddTool((HWND)m_update,_TEXT("Update"));
	m_updateIcon=AtlLoadIcon(IDI_UPDATE);
	m_update.SetIcon(m_updateIcon);

//}}WTLBUILDER_MEMBER_CREATION
//{{WTLBUILDER_POST_CREATION
//}}WTLBUILDER_POST_CREATION
	CenterWindow(GetDesktopWindow());

	DecorativeCtrl::CPanelHost * panelHost=(DecorativeCtrl::CPanelHost *)prop->Self();
	for(long i=0;i < panelHost->GetCount();i++)
	{
		int idx=m_pagelist.AddString(((DecorativeCtrl::CPanel*)panelHost->GetAt(i))->get_Name());
		m_pagelist.SetItemDataPtr(idx,panelHost->GetAt(i));
	}
	m_pagelist.SetCurSel(0);
	m_down.EnableWindow(m_pagelist.GetCount() > 1);
	m_up.EnableWindow(m_pagelist.GetCount() > 1);
	m_remove.EnableWindow(m_pagelist.GetCount() > 1);

	CString str;
	m_pagelist.GetText(0,str);
	m_pagename.SetWindowText(str);

	return TRUE;
}

LRESULT CPagesEdit::OnCloseCmd(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	if(wID==IDOK)
	{
		DecorativeCtrl::CPanelHost * panelHost=(DecorativeCtrl::CPanelHost *)prop->Self();

		panelHost->Reset();

		for(int idx=0; idx < m_pagelist.GetCount();idx++)
		{
			CString str;
			DecorativeCtrl::CPanel* Item=NULL;
			m_pagelist.GetText(idx,str);
			Item=(DecorativeCtrl::CPanel*)m_pagelist.GetItemDataPtr(idx);
			panelHost->AddPanel(str,Item);
		}
        SendEvent(evAddUndo,NULL);
	}

	EndDialog(wID);
//{{WTLBUILDER_MEMBER_DESTRUCTION
	if(m_addIcon!=NULL)
		::DeleteObject(m_addIcon);
	if(m_removeIcon!=NULL)
		::DeleteObject(m_removeIcon);
	if(m_upIcon!=NULL)
		::DeleteObject(m_upIcon);
	if(m_downIcon!=NULL)
		::DeleteObject(m_downIcon);
	if(m_updateIcon!=NULL)
		::DeleteObject(m_updateIcon);
//}}WTLBUILDER_MEMBER_DESTRUCTION
	return 0;
}

LRESULT CPagesEdit::OnRemove(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	if(m_pagelist.GetCount() > 1)
	{
		int idx=m_pagelist.GetCurSel();
		if(idx!=LB_ERR)
		{
			m_pagelist.DeleteString(idx);
			int count=m_pagelist.GetCount();
			if(count >=1)
			{
				if(idx >= count)
					idx=count-1;
				m_pagelist.SetCurSel(idx);
				BOOL bHandled;
				OnSelChange(0,0,0,bHandled);
			}
		}
	}

	m_down.EnableWindow(m_pagelist.GetCount() > 1);
	m_up.EnableWindow(m_pagelist.GetCount() > 1);
	m_remove.EnableWindow(m_pagelist.GetCount() > 1);

	return 0;
}

LRESULT CPagesEdit::OnAdd(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	if(m_pagename.GetWindowTextLength())
	{
		DecorativeCtrl::CPanelHost * panelHost=(DecorativeCtrl::CPanelHost *)prop->Self();
		CString pageName;
		int len=m_pagename.LineLength(0);
		m_pagename.GetLine(0,pageName.GetBuffer(len),len);
		pageName.ReleaseBuffer(len);
		if(m_pagelist.FindStringExact(0,pageName)==LB_ERR)
		{
			int idx=m_pagelist.GetCurSel();
			if(idx==LB_ERR)
				idx=m_pagelist.GetCount();
			else
				idx+=1;
			idx=m_pagelist.InsertString(idx,pageName);
			m_pagelist.SetItemDataPtr(idx,NULL);
			m_pagelist.SetCurSel(idx);
		}
	}

	m_down.EnableWindow(m_pagelist.GetCount() > 1);
	m_up.EnableWindow(m_pagelist.GetCount() > 1);
	m_remove.EnableWindow(m_pagelist.GetCount() > 1);

	return 0;
}

LRESULT CPagesEdit::OnUp(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	int idx=m_pagelist.GetCurSel();
	if(idx!=LB_ERR && idx!=0)
	{
		CString str;
		DecorativeCtrl::CPanel* Item=NULL;
		m_pagelist.GetText(idx,str);
		Item=(DecorativeCtrl::CPanel*)m_pagelist.GetItemDataPtr(idx);
		m_pagelist.DeleteString(idx);
		idx-=1;
		idx=m_pagelist.InsertString(idx,str);
		m_pagelist.SetItemDataPtr(idx,Item);
		m_pagelist.SetCurSel(idx);
	}
	return 0;
}

LRESULT CPagesEdit::OnDown(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	int idx=m_pagelist.GetCurSel();
	if(idx!=LB_ERR && idx<m_pagelist.GetCount()-1)
	{
		CString str;
		DecorativeCtrl::CPanel* Item=NULL;
		m_pagelist.GetText(idx,str);
		Item=(DecorativeCtrl::CPanel*)m_pagelist.GetItemDataPtr(idx);
		m_pagelist.DeleteString(idx);
		idx+=1;
		idx=m_pagelist.InsertString(idx,str);
		m_pagelist.SetItemDataPtr(idx,Item);
		m_pagelist.SetCurSel(idx);
	}
	return 0;
}

LRESULT CPagesEdit::OnUpdate(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	int idx=m_pagelist.GetCurSel();
	if(idx!=LB_ERR)
	{
		CString pageName;
		int len=m_pagename.LineLength(0);
		if(len!=0)
		{
			m_pagename.GetLine(0,pageName.GetBuffer(len),len);
			pageName.ReleaseBuffer(len);
			if(m_pagelist.FindStringExact(0,pageName)==LB_ERR)
			{
				DecorativeCtrl::CPanel* Item=NULL;
				Item=(DecorativeCtrl::CPanel*)m_pagelist.GetItemDataPtr(idx);
				m_pagelist.DeleteString(idx);
				if(Item)
					Item->set_Name(pageName);
				idx=m_pagelist.InsertString(idx,pageName);
				m_pagelist.SetItemDataPtr(idx,Item);
				m_pagelist.SetCurSel(idx);
			}
		}
	}
	return 0;
}

LRESULT CPagesEdit::OnSelChange(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	int idx=m_pagelist.GetCurSel();
	if(idx!=LB_ERR)
	{
		CString str;
		m_pagelist.GetText(idx,str);
		m_pagename.SetWindowText(str);
	}

	return 0;
}

LRESULT CPagesEdit::OnEditChange(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	m_update.EnableWindow(m_pagelist.GetCurSel()!=LB_ERR && m_pagename.LineLength(0)!=0);

	CString pageName;
	int len=m_pagename.LineLength(0);
	m_pagename.GetLine(0,pageName.GetBuffer(len),len);
	pageName.ReleaseBuffer(len);

	if(m_pagelist.FindStringExact(0,pageName)==LB_ERR)
		m_add.EnableWindow(m_pagelist.GetCurSel()!=LB_ERR && m_pagename.LineLength(0)!=0);
	else
		m_add.EnableWindow(FALSE);

	return 0;
}

void PagesEdit(HWND parent,PropertyBase *prop)
{
	if(prop)
	{
		CPagesEdit Dlg(prop);
		Dlg.DoModal(parent);
	}
}
